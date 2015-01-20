#ifndef __shooter__Map__
#define __shooter__Map__

#include "Entity.h"

class Map : public Entity {
public:
    irr::scene::IMeshSceneNode *node;
    irr::scene::ITriangleSelector *selector;
    Map(World *world, const std::string &path, irr::core::vector3df position, irr::core::vector3df rotation);
    ~Map();
    
private:
    void loadMap(const std::string &pkgPath, const std::string &bspPath);
};

#endif /* defined(__shooter__Map__) */
