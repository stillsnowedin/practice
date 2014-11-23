#ifndef __tuts__Game__
#define __tuts__Game__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <GLUT/GLUT.h>
#include "Sprite.h"
#include "GLTexture.h"
#include "ImageLoader.h"
#include "Errors.h"
#include "GLSLProgram.h"
#include "CoreFoundation/CoreFoundation.h"

enum class GameState { PLAY, EXIT };

class Game {
public:
    Game();
    ~Game();
    void init();
    
private:
    SDL_Window* _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;
    Sprite _sprite;
    GLTexture _texture;
    GLSLProgram _colorProgram;
    float _time;
    int _uniformID;
    
    void setupWindow();
    void setupShaders();
    void setupDisplayObjects();
    void run();
    void processInput();
    void draw();
    
};
#endif /* defined(__tuts__Game__) */
