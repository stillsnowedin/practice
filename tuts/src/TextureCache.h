#ifndef __tuts__TextureCache__
#define __tuts__TextureCache__

#include "GLTexture.h"
#include "ImageLoader.h"
#include <map>

class TextureCache {
public:
    TextureCache();
    ~TextureCache();
    GLTexture getTexture(std::string key);
    
private:
    std::map<std::string, GLTexture> _textureMap;
    
};

#endif /* defined(__tuts__TextureCache__) */
