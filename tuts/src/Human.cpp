#include "Human.h"

Human::Human() {

}

Human::~Human() {

}

void Human::update() {
    m_position += m_direction * m_speed;
    
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