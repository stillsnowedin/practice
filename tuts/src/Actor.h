#ifndef __tuts__Actor__
#define __tuts__Actor__

#include <glm/glm.hpp>
#include "GLTexture.h"
#include "SpriteBatch.h"
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>

class Zombie;
class Human;

class Actor {
public:
    Actor();
    virtual ~Actor();
    
    virtual void update() = 0;
    virtual void attack(Actor* target) = 0;
    
    void init(float speed, glm::vec2 position);
    void draw(SpriteBatch& spriteBatch, const std::string& texturePath);
    bool isColliding(glm::vec2 actorLoc);
    glm::vec2 collisionOffset(glm::vec2 actorLoc);
    
    void die() { m_isDead = true; };
    void setPosition(glm::vec2 position) { m_position = position; };
    glm::vec2 getPosition() const { return m_position; };
    const float getWidth() const { return ACTOR_WIDTH; };
    const float getHeight() const { return ACTOR_HEIGHT; };
    bool isDead() { return m_isDead; };
    
private:
    const float ACTOR_WIDTH = 32;
    const float ACTOR_HEIGHT = 32;
    bool m_isDead = false;
    //GLTexture m_texture;
    
protected:
    glm::vec2 m_position;
    float m_speed;
    int m_health;
    glm::vec2 m_direction;
    
};

#endif /* defined(__tuts__Actor__) */
