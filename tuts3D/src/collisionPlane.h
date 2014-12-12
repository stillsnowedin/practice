#ifndef __tuts3D__collisionPlane__
#define __tuts3D__collisionPlane__

#include "vector3d.h"

class collisionPlane {
public:
    vector3d p[4];
    vector3d normal;
    
    collisionPlane(float n1, float n2, float n3,
                   float p1a, float p1b, float p1c,
                   float p2a, float p2b, float p2c,
                   float p3a, float p3b, float p3c,
                   float p4a, float p4b, float p4c);
    
};
#endif /* defined(__tuts3D__collisionPlane__) */
