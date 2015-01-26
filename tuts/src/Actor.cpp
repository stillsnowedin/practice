#include "Actor.h"
#include "ResourceManager.h"

Actor::Actor() {
    
}

Actor::~Actor() {
    
}

void Actor::init(float speed, glm::vec2 position) {
    m_speed = speed;
    m_position = position;
    std::cout << "Actor loc: " << position.x << ", " << position.y << std::endl;
}

void Actor::draw(SpriteBatch& spriteBatch, const std::string& texturePath) {
    glm::vec4 destRect(m_position.x, m_position.y, ACTOR_WIDTH, ACTOR_HEIGHT);
    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    spriteBatch.draw(destRect, uvRect, ResourceManager::getTexture(texturePath).id, 0.0f, color);
}