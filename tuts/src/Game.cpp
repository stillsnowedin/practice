#include "Game.h"

Game::Game() {
    _window = nullptr;
    _screenWidth = 640;
    _screenHeight = 480;
    _gameState = GameState::PLAY;
    _time = 0.0f;
    _uniformID = 0;
}

Game::~Game() {
    
}

void Game::init() {
    setupWindow();
    setupShaders();
    setupDisplayObjects();
    run();
}

void Game::setupWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    _window = SDL_CreateWindow("Tuts Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }
    
    SDL_GLContext context = SDL_GL_CreateContext(_window);
    if (context == nullptr) {
        fatalError("SDL Context could not be created!");
    }
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::setupShaders() {
    _colorProgram.initShaders("/Users/Kathryn/Documents/github/practice/tuts/shaders/colorShading.vert", "/Users/Kathryn/Documents/github/practice/tuts/shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

void Game::setupDisplayObjects() {
    _sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
    
    _texture = ImageLoader::loadPNG("/Users/Kathryn/Documents/github/practice/tuts/resources/jimmyJump_pack/PNG/AngryCloud.png");
}

void Game::run() {
    while (_gameState != GameState::EXIT) {
        processInput();
        _time += 0.01f;
        draw();
    }
}

void Game::processInput() {
    SDL_Event input;
    
    while (SDL_PollEvent(&input)) {
        switch (input.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                std::cout << input.motion.x << " " << input.motion.y << std::endl;
                break;
        }
    }
}

void Game::draw() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _colorProgram.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture.id);
    
    GLint textureLocation = _colorProgram.getUniformLocation("aSampler");
    glUniform1i(textureLocation, 0);
    
    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);
    
    _sprite.draw();
    
    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();
    
    SDL_GL_SwapWindow(_window);
}



