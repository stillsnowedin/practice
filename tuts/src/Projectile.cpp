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

void Projectile::update(float deltaTime) {
    m_position += m_direction * m_speed * deltaTime;
}

bool Projectile::isColliding(glm::vec2 actorLoc) {
    glm::vec2 corners[4];
    corners[0] = glm::vec2(actorLoc.x, actorLoc.y);
    corners[1] = glm::vec2(actorLoc.x + ACTOR_WIDTH, actorLoc.y);
    corners[2] = glm::vec2(actorLoc.x, actorLoc.y + ACTOR_HEIGHT);
    corners[3] = glm::vec2(actorLoc.x + ACTOR_WIDTH, actorLoc.y + ACTOR_HEIGHT);
    
    for (int i=0; i < 4; i++) {
        if (corners[i].x >= m_position.x && (corners[i].x <= (m_position.x + PROJECTILE_WIDTH)) &&
            corners[i].y >= m_position.y && (corners[i].y <= m_position.y + PROJECTILE_HEIGHT)) {
            return true;
        }
    }
    
    return false;
}

void Projectile::draw(SpriteBatch& spriteBatch, const std::string& texturePath) {
    glm::vec4 destRect(m_position.x, m_position.y, PROJECTILE_WIDTH, PROJECTILE_HEIGHT);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    ColorRGBA8 color(255, 255, 255, 255);
    spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture(texturePath).id, m_position.y, color);
}