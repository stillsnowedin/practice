#ifndef __tuts__ResourceManager__
#define __tuts__ResourceManager__

#include "TextureCache.h"
#include <string>

class ResourceManager {
public:
    static GLTexture getTexture(std::string texturePath);
    
private:
    static TextureCache _textureCache;
};

#endif /* defined(__tuts__ResourceManager__) */
