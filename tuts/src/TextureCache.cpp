#include "TextureCache.h"

TextureCache::TextureCache() {

}

TextureCache::~TextureCache() {

}

GLTexture TextureCache::getTexture(std::string key) {
    std::map<std::string, GLTexture>::iterator mit = _textureMap.find(key);
    
    if (mit == _textureMap.end()) {
        GLTexture newTexture = ImageLoader::loadPNG(key);
        std::pair<std::string, GLTexture> newPair(key, newTexture);
        _textureMap.insert(newPair);
        
        std::cout << "Loaded new texture " << key << "!\n";
        return newTexture;
    } else {
        std::cout << "Loaded cached texture " << key << "!\n";
        return mit->second;
    }
}