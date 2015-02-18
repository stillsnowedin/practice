#include "Player.h"
#include <SDL2/SDL.h>
#include <iostream>

Player::Player() {
    
}

Player::~Player() {
    
}

void Player::update() {
    //regen health
}

void Player::attack(Actor* target) {
    
}

void Player::getCommands(InputManager inputManager) {
    if (inputManager.isKeyPressed(SDLK_w))
        m_position.y += m_speed;
    else if (inputManager.isKeyPressed(SDLK_s))
        m_position.y -= m_speed;
    
    if (inputManager.isKeyPressed(SDLK_a))
        m_position.x -= m_speed;
    else if (inputManager.isKeyPressed(SDLK_d))
        m_position.x += m_speed;
}

