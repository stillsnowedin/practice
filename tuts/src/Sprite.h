#ifndef __tuts__Sprite__
#define __tuts__Sprite__

//ignore gl.h and gl3.h overlap
#ifdef __APPLE__
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#endif

#include <OpenGL/gl3.h>
#include "Vertex.h"
#include "GLTexture.h"
#include "ResourceManager.h"
#include <cstddef>
#include <iostream>
#include <string>

class Sprite {
public:
    Sprite();
    ~Sprite();
    void init(float x, float y, float width, float height, std::string texturePath);
    void draw();
    
private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboID;
    GLuint _vaoID;
    GLTexture _texture;
    
};
#endif /* defined(__tuts__Sprite__) */
