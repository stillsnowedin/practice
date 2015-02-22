#include "Human.h"

Human::Human() {
    m_health = 100;
}

Human::~Human() {

}

/*
 * roam around
 */
void Human::update(float deltaTime) {
    m_position += m_direction * m_speed * deltaTime;
    
    if (m_frames == 50) {
        static std::mt19937 mt((uint)time(nullptr));
        static std::uniform_real_distribution<float> rand(-1.0f, 1.0f);
        m_direction = glm::rotate(m_direction, rand(mt));
        m_frames = 0;
    } else {
        m_frames++;
    }
}

void Human::invertDirection() {
    m_direction *= -1;
}