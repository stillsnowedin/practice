#ifndef __tuts__Player__
#define __tuts__Player__

#include "Human.h"
#include "InputManager.h"
#include "Weapon.h"

class Player : public Human {
public:
    Player();
    virtual ~Player();
    
    virtual void update(float deltaTime) override;
    
    void getCommands(InputManager inputManager, float deltaTime);
    void checkCollision();
    void addWeapon(Weapon* weapon);
    Weapon* getCurrentWeapon() { return m_weapons[m_currentWeapon]; };
    
private:
    std::vector<Weapon*> m_weapons;
    int m_currentWeapon;
};

#endif /* defined(__tuts__Player__) */
