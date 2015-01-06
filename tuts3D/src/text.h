#ifndef __tuts3D__text__
#define __tuts3D__text__

#include <cstring>
#include <vector>
#include "objLoader.h"

class text {
public:
    text(float, float, std::vector<unsigned int>&);
    void drawText(coordinate pos, coordinate rot, const char* tex);
    
private:
    float width, height;
    std::vector<unsigned int> characters;
    
};

#endif /* defined(__tuts3D__text__) */
