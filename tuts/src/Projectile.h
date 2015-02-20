#ifndef __tuts__Projectile__
#define __tuts__Projectile__

#include "Actor.h"

class Projectile : public Actor {
public:
    Projectile(glm::vec2 position, glm::vec2 direction, float damage, float speed);
    virtual ~Projectile();
    
    virtual void update();
    
    void draw(SpriteBatch& spriteBatch, const std::string& texturePath);
    void setDamage(float damage) { m_damage = damage; };
    float getDamage() const { return m_damage; };
    
private:
    const float PROJECTILE_WIDTH = 20;
    const float PROJECTILE_HEIGHT = 20;
    float m_damage;
};

#endif /* defined(__tuts__Projectile__) */
