#include "SpriteBatch.h"
#include <iostream>

SpriteBatch::SpriteBatch() : m_vbo(0), m_vao(0) {
    
}

SpriteBatch::~SpriteBatch() {
    
}

void SpriteBatch::init(GLSLProgram& shaderProgram) {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    
    GLuint attribLoc1 = shaderProgram.getAttribLocation("vertexPosition");
    GLuint attribLoc2 = shaderProgram.getAttribLocation("vertexColor");
    GLuint attribLoc3 = shaderProgram.getAttribLocation("vertexUV");
    
    glEnableVertexAttribArray(attribLoc1);
    glEnableVertexAttribArray(attribLoc2);
    glEnableVertexAttribArray(attribLoc3);
    
    glVertexAttribPointer(attribLoc1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(attribLoc2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(attribLoc3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    
    glDisableVertexAttribArray(attribLoc1);
    glDisableVertexAttribArray(attribLoc2);
    glDisableVertexAttribArray(attribLoc3);
}

void SpriteBatch::begin(GlyphSortType sortType) {
    m_sortType = sortType;
    m_renderBatches.clear();
    m_glyphs.clear();
}

void SpriteBatch::end() {
    m_glyphPointers.resize(m_glyphs.size());
    for (int i=0; i<m_glyphs.size(); i++) {
        m_glyphPointers[i] = &m_glyphs[i];
    }
    sortGlyphs();
    createRenderBatches();
}

void SpriteBatch::sortGlyphs() {
    switch (m_sortType) {
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareFrontToBack);
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareBackToFront);
            break;
        case GlyphSortType::TEXTURE:
            std::stable_sort(m_glyphPointers.begin(), m_glyphPointers.end(), compareTexture);
            break;
        case GlyphSortType::NONE:
            break;
    }
}

void SpriteBatch::createRenderBatches() {
    if (m_glyphs.empty()) {
        return;
    }
    
    std::vector<Vertex> vertices;
    vertices.resize(m_glyphs.size() * 6);
    
    int cv = 0; //current vertex
    int offset = 0;
    m_renderBatches.emplace_back(offset, 6, m_glyphPointers[0]->texture);
    vertices[cv++] = m_glyphPointers[0]->topLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomLeft;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->bottomRight;
    vertices[cv++] = m_glyphPointers[0]->topRight;
    vertices[cv++] = m_glyphPointers[0]->topLeft;
    offset += 6;
    
    for (int cg = 1; cg < m_glyphs.size(); cg++) {
        if (m_glyphPointers[cg]->texture != m_glyphPointers[cg-1]->texture) {
            m_renderBatches.emplace_back(offset, 6, m_glyphPointers[cg]->texture);
            
        } else {
            m_renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = m_glyphPointers[cg]->topLeft;
        vertices[cv++] = m_glyphPointers[cg]->bottomLeft;
        vertices[cv++] = m_glyphPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphPointers[cg]->bottomRight;
        vertices[cv++] = m_glyphPointers[cg]->topRight;
        vertices[cv++] = m_glyphPointers[cg]->topLeft;
        offset += 6;
    }
    
    //glBindVertexArray(m_vao);
    //glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    //orphan the buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
    //upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteBatch::renderBatch() {
    glBindVertexArray(m_vao);
    for (int i = 0; i < m_renderBatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
        glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
    }
    glBindVertexArray(0);
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, ColorRGBA8 color) {
    m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b) {
    return (a->depth < b->depth);
}

bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b) {
    return (a->depth > b->depth);
}

bool SpriteBatch::compareTexture(Glyph *a, Glyph *b) {
    return (a->texture < b->texture);
}