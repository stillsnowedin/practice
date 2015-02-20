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
    
    void init(float speed, glm::vec2 position);
    void draw(SpriteBatch& spriteBatch, const std::string& texturePath);
    bool isColliding(glm::vec2 actorLoc);
    glm::vec2 collisionOffset(glm::vec2 actorLoc);
    
    void getHit(int damage);
    void die() { m_isDead = true; };
    void setPosition(glm::vec2 position) { m_position = position; };
    glm::vec2 getPosition() const { return m_position; };
    void setDirection(glm::vec2 direction) { m_direction = direction; };
    glm::vec2 getDirection() const { return m_direction; };
    void setSpeed(float speed) { m_speed = speed; };
    float getSpeed() const { return m_speed; };
    const float getWidth() const { return ACTOR_WIDTH; };
    const float getHeight() const { return ACTOR_HEIGHT; };
    bool isDead() { return m_isDead; };
    
private:
    bool m_isDead = false;
    //GLTexture m_texture;
    
protected:
    const float ACTOR_WIDTH = 32;
    const float ACTOR_HEIGHT = 32;
    glm::vec2 m_position;
    float m_speed;
    int m_health;
    glm::vec2 m_direction;
    
};

#endif /* defined(__tuts__Actor__) */
