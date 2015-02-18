#include "Actor.h"
#include "ResourceManager.h"

Actor::Actor() {
    
}

Actor::~Actor() {
    
}

void Actor::init(float speed, glm::vec2 position) {
    m_speed = speed;
    m_position = position;
    
    static std::mt19937 mt((uint)time(nullptr));
    static std::uniform_real_distribution<float> rand(-1.0f, 1.0f);
    m_direction = glm::vec2(rand(mt), rand(mt));
    if (m_direction.length() == 0) m_direction = glm::vec2(1.0f, 0.0f);
    m_direction = glm::normalize(m_direction);
    
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

bool Actor::isColliding(glm::vec2 actorLoc) {
    glm::vec2 corners[4];
    corners[0] = glm::vec2(actorLoc.x, actorLoc.y);
    corners[1] = glm::vec2(actorLoc.x + ACTOR_WIDTH, actorLoc.y);
    corners[2] = glm::vec2(actorLoc.x, actorLoc.y + ACTOR_HEIGHT);
    corners[3] = glm::vec2(actorLoc.x + ACTOR_WIDTH, actorLoc.y + ACTOR_HEIGHT);
    
    for (int i=0; i < 4; i++) {
        if (corners[i].x >= m_position.x && (corners[i].x <= (m_position.x + ACTOR_WIDTH)) &&
            corners[i].y >= m_position.y && (corners[i].y <= m_position.y + ACTOR_HEIGHT)) {
            return true;
        }
    }
    
    return false;
}

/*
 * find out how much an actor is overlapping this one
 * return the new position for the actor
 */
glm::vec2 Actor::collisionOffset(glm::vec2 actorLoc) {
    glm::vec2 myCenter = m_position + glm::vec2(ACTOR_WIDTH / 2.0f, ACTOR_HEIGHT / 2.0f);
    glm::vec2 actorCenter = actorLoc + glm::vec2(ACTOR_WIDTH / 2.0f, ACTOR_HEIGHT / 2.0f);
    glm::vec2 distance = actorCenter - myCenter;
    
    //    std::cout << "Actor center: (" << actorCenter.x << ", " << actorCenter.y << ")" << std::endl;
    //    std::cout << "Tile center: (" << tileCenter.x << ", " << tileCenter.y << ")" << std::endl;
    //    std::cout << "distance: (" << distance.x << ", " << distance.y << ")" << std::endl;
    
    float dx = ACTOR_WIDTH - abs(distance.x);
    float dy = ACTOR_HEIGHT - abs(distance.y);
    //    std::cout << "dx: " << dx << " dy: " << dy << std::endl;
    
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
    
    //    std::cout << "setting position (" << newPosition.x << ", " << newPosition.y << ")" << std::endl;
    return newPosition;
}