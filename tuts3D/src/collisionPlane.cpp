#include "collisionPlane.h"

collisionPlane::collisionPlane(float n1, float n2, float n3,
                               float p1a, float p1b, float p1c,
                               float p2a, float p2b, float p2c,
                               float p3a, float p3b, float p3c,
                               float p4a, float p4b, float p4c) {
    normal.change(n1, n2, n3);
    p[0].change(p1a, p1b, p1c);
    p[1].change(p2a, p2b, p2c);
    p[2].change(p3a, p3b, p3c);
    p[3].change(p4a, p4b, p4c);
}