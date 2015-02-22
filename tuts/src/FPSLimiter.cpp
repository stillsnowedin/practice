#include "FPSLimiter.h"
#include <SDL2/SDL.h>
#include <iostream>

FPSLimiter::FPSLimiter() {

}

void FPSLimiter::init(float maxFPS) {
    setMaxFPS(maxFPS);
}

void FPSLimiter::begin() {
    m_startTicks = SDL_GetTicks();
}

float FPSLimiter::end() {
    calculateFPS();
    
    //limit FPS
    float frameTicks = SDL_GetTicks() - m_startTicks;
    if (1000.0f / m_maxFPS > frameTicks) {
        SDL_Delay(1000.0f / m_maxFPS - frameTicks);
    }
    
    return m_fps;
}

void FPSLimiter::setMaxFPS(float maxFPS) {
    m_maxFPS = maxFPS;
}

void FPSLimiter::calculateFPS() {
    static const int NUM_SAMPLES = 100;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;
    
    static float previousTicks = SDL_GetTicks();
    float currentTicks = SDL_GetTicks();
    
    float frameTime = currentTicks - previousTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = frameTime;
    previousTicks = currentTicks;
    
    int count;
    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    } else {
        count = NUM_SAMPLES;
    }
    
    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;
    
    if (frameTimeAverage > 0) {
        m_fps = 1000.0f / frameTimeAverage;
    } else {
        m_fps = m_maxFPS;
    }
}

float FPSLimiter::getTimeStep() {
    const float MS_PER_SECOND = 1000;
    const float DESIRED_FRAMETIME = MS_PER_SECOND / m_maxFPS;
    
    static float previousTicks = SDL_GetTicks();
    float currentTicks = SDL_GetTicks();
    float frameTime = currentTicks - previousTicks;
    previousTicks = currentTicks;
    float totalDeltaTime = frameTime / DESIRED_FRAMETIME;
    
    return totalDeltaTime;
}