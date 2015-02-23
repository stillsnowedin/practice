#include "Weapon.h"

Weapon::Weapon(std::string name, int fireRate, int burst, float spread, float projectileDamage, float projectileSpeed, SoundEffect fireSound) :
    m_name(name),
    m_fireRate(fireRate),
    m_burst(burst),
    m_spread(spread),
    m_projectileDamage(projectileDamage),
    m_projectileSpeed(projectileSpeed),
    m_fireSound(fireSound)
{

}

Weapon::~Weapon() {

}

/*
 * if mouse down
 * fire new projectile
 */
void Weapon::update(bool isMouseDown, const glm::vec2 position, glm::vec2 direction, std::vector<Projectile>& projectiles) {
    m_frames++;
    static std::mt19937 mt((uint)time(nullptr));
    std::uniform_real_distribution<float> rand(-m_spread, m_spread);
    
    if ((m_frames >= m_fireRate) && isMouseDown) {
        m_fireSound.play();
        
        for (int i=0; i<m_burst; i++) {
            projectiles.emplace_back(position, glm::rotate(direction, rand(mt)), m_projectileDamage, m_projectileSpeed);
        }
        m_frames = 0;
    }
}