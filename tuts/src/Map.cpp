#include "Map.h"
#include "Errors.h"
#include "ResourceManager.h"
#include <fstream>
#include <math.h>
#include <ctime>
#include <random>

Map::Map(const std::string& filename) {
    std::ifstream fin;
    fin.open(filename);
    
    if (fin.fail()) {
        fatalError("Failed to open " + filename);
    }
    
    std::string line;
    fin >> line >> m_numHumans;
    std::getline(fin, line);
    
    while (std::getline(fin, line)) {
        m_mapData.push_back(line);
    }
}

Map::~Map() {
    
}

void Map::draw(SpriteBatch& spriteBatch) {
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    for (int row=0; row < m_mapData.size(); row++) {
        for (int col=0; col < m_mapData[row].size(); col++) {
            char tile = m_mapData[row][col];
            glm::vec4 destRect(col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
            
            switch (tile) {
                case 'B':
                case 'R':
                    spriteBatch.draw(destRect,
                                       uvRect,
                                       ResourceManager::getTexture("images/fantasy_tileset/PNG/fantasy-tileset2-03-03.png").id,
                                       0.0f,
                                       color);
                    break;
                case 'G':
                    spriteBatch.draw(destRect,
                                       uvRect,
                                       ResourceManager::getTexture("images/fantasy_tileset/PNG/fantasy-tileset2-02-03.png").id,
                                       0.0f,
                                       color);
                    break;
                case 'L':
                    spriteBatch.draw(destRect,
                                       uvRect,
                                       ResourceManager::getTexture("images/fantasy_tileset/PNG/fantasy-tileset2-15-01.png").id,
                                       0.0f,
                                       color);
                    break;
                case '@':
                    m_mapData[row][col] = '.';
                    m_playerLoc.x = col * TILE_WIDTH;
                    m_playerLoc.y = row * TILE_HEIGHT;
                    spriteBatch.draw(destRect,
                                     uvRect,
                                     ResourceManager::getTexture("images/fantasy_tileset/PNG/fantasy-tileset2-05-01.png").id,
                                     0.0f,
                                     color);
                    break;
                case 'Z':
                    m_mapData[row][col] = '.';
                    m_zombieLocs.emplace_back(col * TILE_WIDTH, row * TILE_HEIGHT);
                    spriteBatch.draw(destRect,
                                     uvRect,
                                     ResourceManager::getTexture("images/fantasy_tileset/PNG/fantasy-tileset2-06-01.png").id,
                                     0.0f,
                                     color);
                    break;
                case '.':
                    spriteBatch.draw(destRect,
                                       uvRect,
                                       ResourceManager::getTexture("images/fantasy_tileset/PNG/fantasy-tileset2-08-02.png").id,
                                       0.0f,
                                       color);
                    break;
                default:
                    //std::printf("Unexpected symbol %c at (%d, %d)\n", tile, col, row);
                    break;
            }
        }
    }
}

bool Map::isTileCollidable(glm::vec2 tileLoc) {
    if (getTileType(tileLoc) == '.')
        return false;
    else
        return true;
}

char Map::getTileType(glm::vec2 loc) {
    int tileCol = floorf(loc.x / TILE_WIDTH);
    int tileRow = floorf(loc.y / TILE_HEIGHT);
    
    //std::cout << "got tile [" << tileRow << "][" << tileCol << "]" << std::endl;
    if (tileRow > 0 && tileRow <= m_mapData.size() && tileCol > 0 && tileCol <= m_mapData[0].size())
        return m_mapData[tileRow][tileCol];
    else
        return '?';
}

glm::vec2 Map::getTileLoc(glm::vec2 loc) {
    float x = loc.x - std::fmod(loc.x, TILE_WIDTH);
    float y = loc.y - std::fmod(loc.y, TILE_HEIGHT);
    
    return glm::vec2(x,y);
}

/*
 * find out how much an actor is overlapping a collideable tile
 * return the new position for the actor
 */
glm::vec2 Map::collisionOffset(glm::vec2 tileLoc, glm::vec2 actorLoc, const float ACTOR_WIDTH, const float ACTOR_HEIGHT) {
    glm::vec2 tileCenter = getTileLoc(tileLoc) + glm::vec2(TILE_WIDTH / 2.0f, TILE_HEIGHT / 2.0f);
    glm::vec2 actorCenter = actorLoc + glm::vec2(ACTOR_WIDTH / 2.0f, ACTOR_HEIGHT / 2.0f);
    glm::vec2 distance = actorCenter - tileCenter;
    
//    std::cout << "Actor center: (" << actorCenter.x << ", " << actorCenter.y << ")" << std::endl;
//    std::cout << "Tile center: (" << tileCenter.x << ", " << tileCenter.y << ")" << std::endl;
//    std::cout << "distance: (" << distance.x << ", " << distance.y << ")" << std::endl;
    
    const float MIN_X_DISTANCE = ACTOR_WIDTH / 2.0f + TILE_WIDTH / 2.0f;
    const float MIN_Y_DISTANCE = ACTOR_HEIGHT / 2.0f + TILE_HEIGHT / 2.0f;
    
    float dx = MIN_X_DISTANCE - abs(distance.x);
    float dy = MIN_Y_DISTANCE - abs(distance.y);
    //std::cout << "dx: " << dx << " dy: " << dy << std::endl;
    
    glm::vec2 newPosition = actorLoc;
    if (dx > 0 || dy > 0) {
        if (std::max(dx, 0.0f) < std::max(dy, 0.0f)) {
            if (distance.x < 0)
                newPosition.x -= dx;
            else
                newPosition.x += dx;
        } else {
            if (distance.y < 0)
                newPosition.y -= dy;
            else
                newPosition.y += dy;
        }
    }
    
    //std::cout << "[Map] setting position (" << newPosition.x << ", " << newPosition.y << ")" << std::endl;
    return newPosition;
}

glm::vec2 Map::getRandomTile() {
    static std::mt19937 mt((int)time(nullptr));
    //std::cout << "map size: " << m_mapData.size() << " " << m_mapData[0].size() << std::endl;
    static std::uniform_int_distribution<int> randX(1, (int)m_mapData[0].size() - 2);
    static std::uniform_int_distribution<int> randY(1, (int)m_mapData.size() - 2);
    
    while (true) {
        glm::vec2 tile(randX(mt) * TILE_WIDTH, randY(mt) * TILE_HEIGHT);
        //std::cout << "trying tile... " << tile.x << ", " << tile.y << std::endl;
        if (getTileType(tile) == '.') {
            //std::cout << "found tile!" << std::endl;
            return tile;
        }
    }
}