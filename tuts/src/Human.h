#ifndef __tuts__Human__
#define __tuts__Human__

#include "Actor.h"

class Human : public Actor {
public:
    Human();
    virtual ~Human();
    
    virtual void update();
};

#endif /* defined(__tuts__Human__) */
