#ifndef __tuts__Game__
#define __tuts__Game__

#include <iostream>
#include <vector>
#include <SDL2/SDL_events.h>
#include <CoreFoundation/CoreFoundation.h>
#include <OpenGL/gl3.h>
#include "GLTexture.h"
#include "ImageLoader.h"
#include "GLSLProgram.h"
#include "Window.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Timing.h"
#include "Map.h"
#include "Player.h"
#include "Zombie.h"
#include "Projectile.h"

enum class GameState { IDLE, PLAY, EXIT };

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
    GLSLProgram m_colorProgram;
    float m_time;
    int m_uniformID;
    float m_maxFPS;
    Camera2D m_camera;
    SpriteBatch m_spriteBatch;
    InputManager m_inputManager;
    FPSLimiter m_fpsLimiter;
    std::vector<Map*> m_maps;
    std::vector<Human*> m_humans;
    std::vector<Zombie*> m_zombies;
    std::vector<Projectile> m_projectiles;
    Player* m_player;
    int m_currentMap;
    int m_numZombies;
    int m_numHumans;
    int m_zombiesKilled;
    int m_humansKilled;
    
    void setupWindow();
    void setupShaders();
    void setupMap();
    void setupActors();
    void run();
    void processInput();
    void checkCollision();
    void checkVictory();
    void draw();
    
};
#endif /* defined(__tuts__Game__) */
