#include "Projectile.h"
#include "ResourceManager.h"

Projectile::Projectile(glm::vec2 position, glm::vec2 direction, float damage, float speed) {
    m_position = position;
    m_direction = direction;
    m_damage = damage;
    m_speed = speed;
}

Projectile::~Projectile() {

}

void Projectile::update() {
    m_position += m_direction * m_speed;
}

void Projectile::draw(SpriteBatch& spriteBatch, const std::string& texturePath) {
    glm::vec4 destRect(m_position.x, m_position.y, PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture(texturePath).id, 0.0f, color);
}