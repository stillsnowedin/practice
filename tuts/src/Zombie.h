#ifndef __tuts__Zombie__
#define __tuts__Zombie__

#include "Actor.h"

class Zombie : public Actor {
public:
    Zombie();
    virtual ~Zombie();
    
    virtual void update();
    
};

#endif /* defined(__tuts__Zombie__) */
