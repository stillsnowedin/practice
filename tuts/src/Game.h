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
#include "FPSLimiter.h"
#include "Map.h"
#include "Player.h"
#include "Zombie.h"
#include "Projectile.h"
#include "SpriteFont.h"
#include "AudioEngine.h"

enum class GameState { IDLE, PLAY, EXIT };

class Game {
public:
    Game();
    ~Game();
    void init();
    
private:
    Window m_window;
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;
    const float MAX_FPS = 60.0f;
    GameState m_gameState;
    GLSLProgram m_colorProgram;
    float m_time;
    int m_uniformID;
    Camera2D m_camera;
    Camera2D m_hudCamera;
    SpriteBatch m_spriteBatch;
    InputManager m_inputManager;
    FPSLimiter m_fpsLimiter;
    SpriteFont* m_spriteFont;
    AudioEngine* m_audioEngine;
    Music m_music;
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
    void setupFont();
    void setupAudio();
    void setupMap();
    void setupActors();
    void run();
    void processInput();
    void checkCollision();
    void checkVictory();
    void draw();
    
};
#endif /* defined(__tuts__Game__) */
