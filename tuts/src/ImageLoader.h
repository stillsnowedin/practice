#ifndef __tuts__ImageLoader__
#define __tuts__ImageLoader__

#include "GLTexture.h"
#include "PicoPNG.h"
#include "IOManager.h"
#include "Errors.h"
#include <string>

class ImageLoader {
public:
    static GLTexture loadPNG(std::string filePath);
    
};

#endif /* defined(__tuts__ImageLoader__) */
