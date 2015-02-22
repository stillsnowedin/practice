#ifndef __tuts__Human__
#define __tuts__Human__

#include "Actor.h"

class Human : public Actor {
public:
    Human();
    virtual ~Human();
    
    virtual void update(float deltaTime) override;
    
    void invertDirection();
    
private:
    int m_frames = 0;
};

#endif /* defined(__tuts__Human__) */
