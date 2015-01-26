#include "Game.h"

Game::Game() {
    m_screenWidth = 1024;
    m_screenHeight = 768;
    m_gameState = GameState::IDLE;
    m_time = 0.0f;
    m_uniformID = 0;
    m_maxFPS = 60.0f;
    m_camera.init(m_screenWidth, m_screenHeight);
    m_player = nullptr;
}

Game::~Game() {
    for (int i=0; i < m_maps.size(); i++) {
        std::cout << "deleting map " << i << std::endl;
        delete m_maps[i];
    }
    for (int i=0; i < m_humans.size(); i++) {
        std::cout << "deleting human " << i << std::endl;
        delete m_humans[i];
    }
    for (int i = 0; i < m_zombies.size(); i++) {
        std::cout << "deleting zombie " << i << std::endl;
        delete m_zombies[i];
    }
}

void Game::init() {
    setupWindow();
    setupShaders();
    setupMap();
    m_fpsLimiter.init(m_maxFPS);
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
    
    m_spriteBatch.init(m_colorProgram);
}

void Game::setupMap() {
    m_gameState = GameState::PLAY;
    m_maps.push_back(new Map("maps/map_1.txt"));
    m_currentMap = 0;
    m_maps[m_currentMap]->draw(m_spriteBatch);
    
    m_player = new Player();
    m_player->init(5.0f, m_maps[m_currentMap]->getPlayerLoc());
    m_humans.push_back(m_player);
    
    std::vector<glm::vec2> zombieLocs = m_maps[m_currentMap]->getZombieLocs();
    for (int i=0; i<zombieLocs.size(); i++) {
        m_zombies.push_back(new Zombie());
        m_zombies.back()->init(0.5f, zombieLocs[i]);
    }
}

void Game::run() {
    while (m_gameState != GameState::EXIT) {
        m_fpsLimiter.begin();
        
        processInput();
        m_time += 0.01f;
        
        //update player
        m_player->getCommands(m_inputManager);
        //update camera
        m_camera.update();
        
        //update other actors
        for (int i=0; i<m_humans.size(); i++) {
            m_humans[i]->update();
        }
        for (int i=0; i<m_humans.size(); i++) {
            m_humans[i]->update();
        }
        
        checkCollision();
        
        draw();
        
        float fps = m_fpsLimiter.end();
        
//        //print the FPS
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

    m_camera.setPosition(m_player->getPosition());
    
    if (m_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
        glm::vec2 mouseLoc = m_camera.convertScreenToWorld(m_inputManager.getMouseLoc());
        std::cout << mouseLoc.x << ", " << mouseLoc.y << std::endl;
    }
}

void Game::checkCollision() {
    glm::vec2 playerPosition = m_player->getPosition();
    const float PLAYER_WIDTH = m_player->getWidth();
    const float PLAYER_HEIGHT = m_player->getHeight();
    glm::vec2 corners[4];
    corners[0] = glm::vec2(playerPosition.x, playerPosition.y);
    corners[1] = glm::vec2(playerPosition.x + PLAYER_WIDTH, playerPosition.y);
    corners[2] = glm::vec2(playerPosition.x, playerPosition.y + PLAYER_HEIGHT);
    corners[3] = glm::vec2(playerPosition.x + PLAYER_WIDTH, playerPosition.y + PLAYER_HEIGHT);
    
    //check walls
    for (int i=0; i<4; i++) {
        if (m_maps[m_currentMap]->isTileCollidable(corners[i])) {
            m_player->setPosition(m_maps[m_currentMap]->collisionOffset(corners[i], playerPosition, PLAYER_WIDTH, PLAYER_HEIGHT));
            break;
        }
    }
    
    //check other actors
    
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
    
    m_spriteBatch.begin();
    m_maps[m_currentMap]->draw(m_spriteBatch);
    m_player->draw(m_spriteBatch, "images/fantasy_tileset/PNG/fantasy-tileset-02-18.png");
    for (int h=1; h<m_humans.size(); h++) {
        m_humans[h]->draw(m_spriteBatch, "images/fantasy_tileset/PNG/fantasy-tileset-05-18.png");
    }
    for (int z=1; z<m_zombies.size(); z++) {
        m_zombies[z]->draw(m_spriteBatch, "images/fantasy_tileset/PNG/fantasy-tileset-01-22.png");
    }
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    
    m_colorProgram.unuse();
    
    m_window.swapBuffer();
}