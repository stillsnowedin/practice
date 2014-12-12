#ifndef __tuts3D__collisionSphere__
#define __tuts3D__collisionSphere__

#include "vector3d.h"

class collisionSphere {
public:
    float r;
    vector3d center;
    
    collisionSphere();
    collisionSphere(const vector3d& vec, float rad);
    
};

#endif /* defined(__tuts3D__collisionSphere__) */
