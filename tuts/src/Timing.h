#ifndef __tuts__Timing__
#define __tuts__Timing__

class FPSLimiter {
public:
    FPSLimiter();
    
    void init(float maxFPS);
    void begin();
    float end(); //returns fps
    void setMaxFPS(float maxFPS);
    void calculateFPS();
    
private:
    float m_fps;
    float m_maxFPS;
    unsigned int m_startTicks;
    
};

#endif /* defined(__tuts__Timing__) */
