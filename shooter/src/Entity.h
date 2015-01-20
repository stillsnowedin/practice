#ifndef __shooter__Entity__
#define __shooter__Entity__

#include <IrrFramework/irrlicht.h>
#include <string>

class World;

class Entity {
protected:
    irr::core::vector3df position;
    irr::core::vector3df rotation;
    std::string path;
    World *world;
    
public:
    Entity(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation);
    virtual ~Entity();
    void update();
    
};
#endif /* defined(__shooter__Entity__) */
