#include "Zombie.h"

Zombie::Zombie() {
    m_health = 50;
}

Zombie::~Zombie() {
    
}

/*
 * AI run on every frame
 */
void Zombie::update() {
    //move around
    m_position += m_direction * m_speed;
}