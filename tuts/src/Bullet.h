#ifndef __tuts__Bullet__
#define __tuts__Bullet__

#include <glm/glm.hpp>
#include "SpriteBatch.h"

class Bullet {
public:
    Bullet(float speed, glm::vec2 position, glm::vec2 direction, int duration);
    ~Bullet();
    
    void draw(SpriteBatch& spriteBatch);
    bool update();

private:
    float m_speed;
    glm::vec2 m_direction;
    glm::vec2 m_position;
    int m_duration;
    
};

#endif /* defined(__tuts__Bullet__) */
