#ifndef __tuts__Player__
#define __tuts__Player__

#include "Human.h"
#include "InputManager.h"

class Player : public Human {
public:
    Player();
    virtual ~Player();
    
    virtual void update();
    
    void getCommands(InputManager inputManager);
    void checkCollision();
    
private:
    
    
};

#endif /* defined(__tuts__Player__) */
