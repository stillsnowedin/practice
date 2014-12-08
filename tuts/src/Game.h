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

enum class GameState { PLAY, EXIT };

class Game {
public:
    Game();
    ~Game();
    void init();
    
private:
    Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    //std::vector<Sprite*> _sprites;
    GLSLProgram _colorProgram;
    float _time;
    int _uniformID;
    float _fps;
    float _frameTime;
    float _maxFPS;
    Camera2D _camera;
    SpriteBatch _spriteBatch;
    
    void setupWindow();
    void setupShaders();
    //void setupDisplayObjects();
    void run();
    void processInput();
    void draw();
    void calculateFPS();
    
};
#endif /* defined(__tuts__Game__) */
