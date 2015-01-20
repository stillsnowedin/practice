#ifndef __shooter__Player__
#define __shooter__Player__

#include "Entity.h"
#include "Item.h"

class Player : public Entity {
public:
    Player(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation);
    ~Player();
    
private:
    irr::scene::ICameraSceneNode *camera;
    Item *gun;
    void setupCamera();
    void setupMap();
    void parseConfig(const std::string &path);
    
};

#endif /* defined(__shooter__Player__) */
