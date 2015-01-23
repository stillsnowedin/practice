#include "Bullet.h"
#include "GLTexture.h"
#include "ResourceManager.h"

Bullet::Bullet(float speed, glm::vec2 position, glm::vec2 direction, int duration) {
    m_speed = speed;
    m_position = position;
    m_direction = direction;
    m_duration = duration;
}

Bullet::~Bullet() {

}

void Bullet::draw(SpriteBatch& spriteBatch) {
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture texture = ResourceManager::getTexture("resources/jimmyJump_pack/PNG/Bullet.png");
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    glm::vec4 drawRect = glm::vec4(m_position.x, m_position.y, 30, 30);
    spriteBatch.draw(drawRect, uv, texture.id, 0.0f, color);
}

bool Bullet::update() {
    m_position += m_direction * m_speed;
    m_duration--;
    if (m_duration < 0) {
        return true;
    }
    return false;
}