#ifndef __tuts__Weapon__
#define __tuts__Weapon__

#include <string>
#include <vector>
#include "Projectile.h"
#include "AudioEngine.h"

class Weapon {
public:
    Weapon(std::string name, int fireRate, int burst, float spread, float projectileDamage, float projectileSpeed, SoundEffect fireSound);
    ~Weapon();
    
    void update(bool isMouseDown, const glm::vec2 position, glm::vec2 direction, std::vector<Projectile>& projectiles);
    
    std::string getName() { return m_name; };
    
private:
    std::string m_name;
    int m_fireRate;
    int m_burst;
    float m_spread;
    float m_projectileDamage;
    float m_projectileSpeed;
    int m_frames = 0;
    SoundEffect m_fireSound;
};

#endif /* defined(__tuts__Weapon__) */
