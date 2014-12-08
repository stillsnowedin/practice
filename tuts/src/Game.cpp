#include "Game.h"

Game::Game() {
    _screenWidth = 640;
    _screenHeight = 480;
    _gameState = GameState::PLAY;
    _time = 0.0f;
    _uniformID = 0;
    _maxFPS = 60.0f;
    
    _camera.init(_screenWidth, _screenHeight);
}

Game::~Game() {
    
}

void Game::init() {
    setupWindow();
    setupShaders();
    _spriteBatch.init();
    //setupDisplayObjects();
    run();
}

void Game::setupWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    _window.create("Tuts Game", _screenWidth, _screenHeight, 0);
}

void Game::setupShaders() {
    _colorProgram.initShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

//void Game::setupDisplayObjects() {
//    _sprites.push_back(new Sprite());
//    _sprites.back()->init(0.0f, 0.0f, _screenWidth/2, _screenWidth/2, "resources/jimmyJump_pack/PNG/AngryCloud.png");
//    
//    _sprites.push_back(new Sprite());
//    _sprites.back()->init(_screenWidth/2, 0.0f, _screenWidth/2, _screenWidth/2, "resources/jimmyJump_pack/PNG/CharacterRight_Standing.png");
//}

void Game::run() {
    while (_gameState != GameState::EXIT) {
        float startTicks = SDL_GetTicks(); //for frame time measuring
        
        processInput();
        _time += 0.01f;
        _camera.update();
        
        draw();
        calculateFPS();
        
        //print the FPS
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10) {
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }
        
        //limit FPS
        float frameTicks = SDL_GetTicks() - startTicks;
        if (1000.0f / _maxFPS > frameTicks) {
            SDL_Delay(1000.0f / _maxFPS - frameTicks);
        }
    }
}

void Game::processInput() {
    SDL_Event input;
    
    const float CAMERA_SPEED = 20.0f;
    const float SCALE_SPEED = 0.1f;
    
    while (SDL_PollEvent(&input)) {
        switch (input.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                //std::cout << input.motion.x << " " << input.motion.y << std::endl;
                break;
            case SDL_KEYDOWN:
                switch (input.key.keysym.sym) {
                    case SDLK_w:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
                        break;
                    case SDLK_s:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
                        break;
                    case SDLK_a:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
                        break;
                    case SDLK_d:
                        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
                        break;
                    case SDLK_q:
                        _camera.setScale(_camera.getScale() + SCALE_SPEED);
                        break;
                    case SDLK_e:
                        _camera.setScale(_camera.getScale() - SCALE_SPEED);
                        break;
                }
        }
    }
}

void Game::draw() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _colorProgram.use();
    glActiveTexture(GL_TEXTURE0);
    
    GLint textureLocation = _colorProgram.getUniformLocation("aSampler");
    glUniform1i(textureLocation, 0);
    
    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);
    
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);
    
//    for (int i = 0; i < _sprites.size(); i++) {
//        _sprites[i]->draw();
//    }
    
    _spriteBatch.begin();
    
    glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture texture = ResourceManager::getTexture("resources/jimmyJump_pack/PNG/AngryCloud.png");
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
    _spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
    
    _spriteBatch.end();
    _spriteBatch.renderBatch();
    _colorProgram.unuse();
    
    _window.swapBuffer();
}

void Game::calculateFPS() {
    static const int NUM_SAMPLES = 100;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;
    
    static float previousTicks = SDL_GetTicks();
    float currentTicks = SDL_GetTicks();
    
    _frameTime = currentTicks - previousTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;
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
        _fps = 1000.0f / frameTimeAverage;
    } else {
        _fps = 60.0f;
    }
}



