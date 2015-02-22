#ifndef __tuts__Zombie__
#define __tuts__Zombie__

#include "Actor.h"

class Zombie : public Actor {
public:
    Zombie();
    virtual ~Zombie();
    
    virtual void update(float deltaTime) override;
    
};

#endif /* defined(__tuts__Zombie__) */
