#ifndef __tuts__SpriteBatch__
#define __tuts__SpriteBatch__

#include <OpenGL/gl3.h>
#include <GLUT/GLUT.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include "GLSLProgram.h"

enum class GlyphSortType { NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

struct Glyph {
    Glyph();
    Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint t, float d, ColorRGBA8 color) : texture(t), depth(d) {
        topLeft.color = color;
        topLeft.setPosition(destRect.x, destRect.y + destRect.w);
        topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
        
        bottomLeft.color = color;
        bottomLeft.setPosition(destRect.x, destRect.y);
        bottomLeft.setUV(uvRect.x, uvRect.y);
        
        topRight.color = color;
        topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
        
        bottomRight.color = color;
        bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
        bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
    };
    
    GLuint texture;
    float depth;
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
};

class RenderBatch {
public:
    RenderBatch(GLuint o, GLuint nv, GLuint t) : offset(o), numVertices(nv), texture(t) {}
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};

class SpriteBatch {
public:
    SpriteBatch();
    ~SpriteBatch();
    
    void init(GLSLProgram& shaderProgram);
    void begin(GlyphSortType sortType = GlyphSortType::FRONT_TO_BACK);
    void end();
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, ColorRGBA8 color);
    void renderBatch();
    
private:
    GLuint m_vbo;
    GLuint m_vao;
    GlyphSortType m_sortType;
    std::vector<Glyph> m_glyphs; //for better memory management
    std::vector<Glyph*> m_glyphPointers; //for sorting faster
    std::vector<RenderBatch> m_renderBatches;
    
    void createRenderBatches();
    void sortGlyphs();
    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);
    
};

#endif /* defined(__tuts__SpriteBatch__) */
