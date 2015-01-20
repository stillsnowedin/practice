#ifndef __shooter__Item__
#define __shooter__Item__

#include "Entity.h"

class Item : public Entity {
public:
    Item(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation);
    ~Item();
    void loadModel(const std::string &meshPath, const std::string &texturePath);
};

#endif /* defined(__shooter__Item__) */
