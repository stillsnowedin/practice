#ifndef __tuts__SpriteBatch__
#define __tuts__SpriteBatch__

#include <OpenGL/gl3.h>
#include <GLUT/GLUT.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"

enum class GlyphSortType { NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

struct Glyph {
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
    
    void init();
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();
    void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, Color& color);
    void renderBatch();
    
private:
    GLuint _vbo;
    GLuint _vao;
    GlyphSortType _sortType;
    std::vector<Glyph*> _glyphs;
    std::vector<RenderBatch> _renderBatches;
    
    void createVertexArray();
    void createRenderBatches();
    void sortGlyphs();
    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);
    
};

#endif /* defined(__tuts__SpriteBatch__) */
