#ifndef __tuts__Map__
#define __tuts__Map__

#include "SpriteBatch.h"
#include "GLSLProgram.h"
#include <string>
#include <vector>
#include <iostream>

class Map {
public:
    Map(const std::string& filename);
    ~Map();
    
    void draw(SpriteBatch& spriteBatch);
    bool isTileCollidable(glm::vec2 tileLoc);
    glm::vec2 collisionOffset(glm::vec2 tileLoc, glm::vec2 actorLoc, const float ACTOR_WIDTH, const float ACTOR_HEIGHT);
    glm::vec2 getRandomTile();
    
    glm::vec2 getPlayerLoc() const { return m_playerLoc; };
    const std::vector<glm::vec2>& getZombieLocs() const { return m_zombieLocs; }
    int getNumHumans() const { return m_numHumans; };
    
private:
    const float TILE_WIDTH = 32;
    const float TILE_HEIGHT = 32;
    std::vector<std::string> m_mapData;
    int m_numHumans;
    //SpriteBatch m_spriteBatch;
    glm::vec2 m_playerLoc;
    std::vector<glm::vec2> m_zombieLocs;
    
    char getTileType(glm::vec2 loc);
    glm::vec2 getTileLoc(glm::vec2 loc);
    
};

#endif /* defined(__tuts__Map__) */
