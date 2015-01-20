#ifndef __shooter__World__
#define __shooter__World__

#include <algorithm>
#include <vector>
#include <IrrFramework/irrlicht.h>
#include <map>

class Entity;

class World {
public:
    irr::IrrlichtDevice *device;
    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *smgr;
    
    std::map<std::string, std::vector<Entity*>> entities;
    
    World(const std::string &filePath);
    ~World();
    void run();
    
private:
    void setupEngine();
    
};

#endif /* defined(__shooter__World__) */
