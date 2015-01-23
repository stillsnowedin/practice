#include "Game.h"

Game::Game() {
    m_screenWidth = 640;
    m_screenHeight = 480;
    m_gameState = GameState::PLAY;
    m_time = 0.0f;
    m_uniformID = 0;
    m_maxFPS = 60.0f;
    
    m_camera.init(m_screenWidth, m_screenHeight);
}

Game::~Game() {
    
}

void Game::init() {
    setupWindow();
    setupShaders();
    m_spriteBatch.init();
    m_fpsLimiter.init(m_maxFPS);
    //setupDisplayObjects();
    run();
}

void Game::setupWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    m_window.create("Tuts Game", m_screenWidth, m_screenHeight, 0);
}

void Game::setupShaders() {
    m_colorProgram.initShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
    m_colorProgram.addAttribute("vertexPosition");
    m_colorProgram.addAttribute("vertexColor");
    m_colorProgram.addAttribute("vertexUV");
    m_colorProgram.linkShaders();
}

//void Game::setupDisplayObjects() {
//    _sprites.push_back(new Sprite());
//    _sprites.back()->init(0.0f, 0.0f, _screenWidth/2, _screenWidth/2, "resources/jimmyJump_pack/PNG/AngryCloud.png");
//    
//    _sprites.push_back(new Sprite());
//    _sprites.back()->init(_screenWidth/2, 0.0f, _screenWidth/2, _screenWidth/2, "resources/jimmyJump_pack/PNG/CharacterRight_Standing.png");
//}

void Game::run() {
    while (m_gameState != GameState::EXIT) {
        m_fpsLimiter.begin();
        
        processInput();
        m_time += 0.01f;
        m_camera.update();
        
        draw();
        
        float fps = m_fpsLimiter.end();
        
        //print the FPS
//        static int frameCounter = 0;
//        frameCounter++;
//        if (frameCounter == 10) {
//            std::cout << fps << std::endl;
//            frameCounter = 0;
//        }
    }
}

void Game::processInput() {
    SDL_Event input;
    
    const float CAMERA_SPEED = 10.0f;
    const float SCALE_SPEED = 0.1f;
    
    //listen for input
    while (SDL_PollEvent(&input)) {
        switch (input.type) {
            case SDL_QUIT:
                m_gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                //std::cout << input.motion.x << " " << input.motion.y << std::endl;
                m_inputManager.setMouseLoc(input.motion.x, input.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_inputManager.pressKey(input.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                m_inputManager.releaseKey(input.button.button);
                break;
            case SDL_KEYDOWN:
                m_inputManager.pressKey(input.key.keysym.sym);
                break;
            case SDL_KEYUP:
                m_inputManager.releaseKey(input.key.keysym.sym);
                break;
        }
    }
    
    //process the input
    if (m_inputManager.isKeyPressed(SDLK_w))
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0, -CAMERA_SPEED));
    if (m_inputManager.isKeyPressed(SDLK_s))
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0, CAMERA_SPEED));
    if (m_inputManager.isKeyPressed(SDLK_a))
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0));
    if (m_inputManager.isKeyPressed(SDLK_d))
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0));
    if (m_inputManager.isKeyPressed(SDLK_q))
        m_camera.setScale(m_camera.getScale() + SCALE_SPEED);
    if (m_inputManager.isKeyPressed(SDLK_e))
        m_camera.setScale(m_camera.getScale() - SCALE_SPEED);
    
    if (m_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
        glm::vec2 mouseLoc = m_camera.convertScreenToWorld(m_inputManager.getMouseLoc());
        std::cout << mouseLoc.x << ", " << mouseLoc.y << std::endl;
    }
}

void Game::draw() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    m_colorProgram.use();
    glActiveTexture(GL_TEXTURE0);
    
    GLint textureLocation = m_colorProgram.getUniformLocation("aSampler");
    glUniform1i(textureLocation, 0);
    
    GLint pLocation = m_colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);
    
//    for (int i = 0; i < _sprites.size(); i++) {
//        _sprites[i]->draw();
//    }
    
    m_spriteBatch.begin();
    
    glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture texture = ResourceManager::getTexture("resources/jimmyJump_pack/PNG/AngryCloud.png");
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
    
    m_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
    //m_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0.0f, color);
    
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    m_colorProgram.unuse();
    
    m_window.swapBuffer();
}