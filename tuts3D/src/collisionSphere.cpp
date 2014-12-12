#include "collisionSphere.h"

collisionSphere::collisionSphere() {
    r = 0;
}

collisionSphere::collisionSphere(const vector3d& vec, float rad) {
    center.change(vec);
    r = rad;
}