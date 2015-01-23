#ifndef __tuts__Game__
#define __tuts__Game__

#include <iostream>
#include <vector>
#include <SDL2/SDL_events.h>
#include <CoreFoundation/CoreFoundation.h>
#include "Sprite.h"
#include "GLTexture.h"
#include "ImageLoader.h"
#include "GLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Timing.h"

enum class GameState { PLAY, EXIT };

class Game {
public:
    Game();
    ~Game();
    void init();
    
private:
    Window m_window;
    int m_screenWidth;
    int m_screenHeight;
    GameState m_gameState;
    //std::vector<Sprite*> m_sprites;
    GLSLProgram m_colorProgram;
    float m_time;
    int m_uniformID;
    float m_maxFPS;
    Camera2D m_camera;
    SpriteBatch m_spriteBatch;
    InputManager m_inputManager;
    FPSLimiter m_fpsLimiter;
    
    
    void setupWindow();
    void setupShaders();
    //void setupDisplayObjects();
    void run();
    void processInput();
    void draw();
};
#endif /* defined(__tuts__Game__) */
