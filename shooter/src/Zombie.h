#ifndef __shooter__Zombie__
#define __shooter__Zombie__

#include "Entity.h"

class Zombie : public Entity {
public:
    Zombie(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation);
    ~Zombie();
    
};

#endif /* defined(__shooter__Zombie__) */
