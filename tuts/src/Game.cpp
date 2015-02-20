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
        delete m_maps[i];
    }
    for (int i=0; i < m_humans.size(); i++) {
        delete m_humans[i];
    }
    for (int i = 0; i < m_zombies.size(); i++) {
        delete m_zombies[i];
    }
}

void Game::init() {
    setupWindow();
    setupShaders();
    setupMap();
    setupActors();
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
}

void Game::setupActors() {
    //player
    m_player = new Player();
    m_player->init(5.0f, m_maps[m_currentMap]->getPlayerLoc());
    m_humans.push_back(m_player);
    m_player->addWeapon(new Weapon("Pistol", 10, 1, 0.0f, 20, 20.0f));
    m_player->addWeapon(new Weapon("Shotgun", 30, 20, 0.4f, 5, 20.0f));
    m_player->addWeapon(new Weapon("AR", 2, 1, 0.1f, 20, 10.0f));
    
    //zombies
    std::vector<glm::vec2> zombieLocs = m_maps[m_currentMap]->getZombieLocs();
    for (int z=0; z<zombieLocs.size(); z++) {
        m_zombies.push_back(new Zombie());
        m_zombies.back()->init(1.0f, zombieLocs[z]);
    }
    
    //humans
    int numHumans = m_maps[m_currentMap]->getNumHumans();
    for (int h=0; h<numHumans; h++) {
        m_humans.push_back(new Human());
        m_humans.back()->init(0.5f, m_maps[m_currentMap]->getRandomTile());
    }
}

void Game::run() {
    while (m_gameState != GameState::EXIT) {
        m_fpsLimiter.begin();
        
        processInput();
        m_time += 0.01f;
        
        //update player
        m_player->getCommands(m_inputManager);
        //fire weapon
        glm::vec2 mouseLoc = m_camera.convertScreenToWorld(m_inputManager.getMouseLoc());
        //std::cout << mouseLoc.x << ", " << mouseLoc.y << std::endl;
        glm::vec2 projectileDirection = glm::normalize(mouseLoc - m_player->getPosition() + glm::vec2(m_player->getWidth()/2, m_player->getHeight()/2));
        m_player->getCurrentWeapon()->update(m_inputManager.isKeyPressed(SDL_BUTTON_LEFT),
                                             m_player->getPosition() + glm::vec2(m_player->getWidth()/2, m_player->getHeight()/2),
                                             projectileDirection,
                                             m_projectiles);
        //update camera
        m_camera.update();
        
        //update other actors
        for (int h=0; h<m_humans.size(); h++) {
            m_humans[h]->update();
        }
        for (int z=0; z<m_zombies.size(); z++) {
            m_zombies[z]->update();
        }
        for (int p=0; p<m_projectiles.size(); p++) {
            m_projectiles[p].update();
        }
        
        checkCollision();
        
        draw();
        
        float fps = m_fpsLimiter.end();
        
        //print the FPS
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 1000) {
            std::cout << fps << std::endl;
            frameCounter = 0;
        }
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
    
    //update camera
    m_camera.setPosition(m_player->getPosition());
}

void Game::checkCollision() {
    //human collision
    const float HUMAN_WIDTH = m_humans[0]->getWidth();
    const float HUMAN_HEIGHT = m_humans[0]->getHeight();
    
    for (int h=0; h<m_humans.size(); h++) {
        glm::vec2 humanPosition = m_humans[h]->getPosition();
        glm::vec2 corners[4];
        corners[0] = glm::vec2(humanPosition.x, humanPosition.y);
        corners[1] = glm::vec2(humanPosition.x + HUMAN_WIDTH, humanPosition.y);
        corners[2] = glm::vec2(humanPosition.x, humanPosition.y + HUMAN_HEIGHT);
        corners[3] = glm::vec2(humanPosition.x + HUMAN_WIDTH, humanPosition.y + HUMAN_HEIGHT);
        
        //check walls
        for (int i=0; i<4; i++) {
            if (m_maps[m_currentMap]->isTileCollidable(corners[i])) {
                m_humans[h]->setPosition(m_maps[m_currentMap]->collisionOffset(corners[i], humanPosition, HUMAN_WIDTH, HUMAN_HEIGHT));
                m_humans[h]->invertDirection();
                break;
            }
        }
        
        //check other humans
        for (int h2 = h + 1; h2 < m_humans.size(); h2++) {
            for (int i = 0; i<4; i++) {
                if (m_humans[h2]->isColliding(corners[i])) {
                    m_humans[h2]->setPosition(m_humans[h]->collisionOffset(m_humans[h2]->getPosition()));
                    break;
                }
            }
        }
    }
    
    //zombie collision
    const float ZOMBIE_WIDTH = m_zombies[0]->getWidth();
    const float ZOMBIE_HEIGHT = m_zombies[0]->getHeight();
    
    for (int z=0; z<m_zombies.size(); z++) {
        glm::vec2 zombiePosition = m_zombies[z]->getPosition();
        glm::vec2 corners[4];
        corners[0] = glm::vec2(zombiePosition.x, zombiePosition.y);
        corners[1] = glm::vec2(zombiePosition.x + ZOMBIE_WIDTH, zombiePosition.y);
        corners[2] = glm::vec2(zombiePosition.x, zombiePosition.y + ZOMBIE_HEIGHT);
        corners[3] = glm::vec2(zombiePosition.x + ZOMBIE_WIDTH, zombiePosition.y + ZOMBIE_HEIGHT);
        
        //check walls
        for (int i=0; i<4; i++) {
            if (m_maps[m_currentMap]->isTileCollidable(corners[i])) {
                m_zombies[z]->setPosition(m_maps[m_currentMap]->collisionOffset(corners[i], zombiePosition, ZOMBIE_WIDTH, ZOMBIE_HEIGHT));
                break;
            }
        }
        
        //check other zombies
        for (int z2 = z + 1; z2<m_zombies.size(); z2++) {
            if (m_zombies[z]->isColliding(m_zombies[z2]->getPosition())) {
                m_zombies[z2]->setPosition(m_zombies[z]->collisionOffset(m_zombies[z2]->getPosition()));
                break;
            }
        }
        
        //check humans
        glm::vec2 newDirection(0.0f, 0.0f);
        float smallestDistance = 1000.0f;
        for (int h=0; h<m_humans.size(); h++) {
            //check if human is the closest to zombie
            glm::vec2 distVec = m_humans[h]->getPosition() - zombiePosition;
            float distance = glm::length(distVec);
            if (distance < smallestDistance) {
                smallestDistance = distance;
                newDirection = distVec;
            }
            
            //check if zombie is touching human
            if (m_humans[h]->isColliding(zombiePosition)) {
                //special instructions if human is the player
                if (h == 0) {
                    
                } else {
                    //convert human to a zombie
                    m_zombies.push_back(new Zombie);
                    m_zombies.back()->init(1.0f, m_humans[h]->getPosition());
                    delete m_humans[h];
                    m_humans[h] = m_humans.back();
                    m_humans.pop_back();
                    break;
                }
            }
        }
        
        //chase closest human
        m_zombies[z]->setDirection(glm::normalize(newDirection));
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
    
    m_spriteBatch.begin();
    m_maps[m_currentMap]->draw(m_spriteBatch);
    m_player->draw(m_spriteBatch, "images/fantasy_tileset/PNG/fantasy-tileset-02-18.png");
    for (int h=1; h<m_humans.size(); h++) {
        m_humans[h]->draw(m_spriteBatch, "images/fantasy_tileset/PNG/fantasy-tileset-05-18.png");
    }
    for (int z=0; z<m_zombies.size(); z++) {
        m_zombies[z]->draw(m_spriteBatch, "images/fantasy_tileset/PNG/fantasy-tileset-01-22.png");
    }
    for (int p=0; p<m_projectiles.size(); p++) {
        m_projectiles[p].draw(m_spriteBatch, "images/fantasy_tileset/PNG/fantasy-tileset-00-07.png");
    }
    m_spriteBatch.end();
    m_spriteBatch.renderBatch();
    
    m_colorProgram.unuse();
    
    m_window.swapBuffer();
}