#include "Player.h"
#include <SDL2/SDL.h>
#include <iostream>

Player::Player() : m_currentWeapon(-1) {
    
}

Player::~Player() {
    
}

void Player::update() {
    //regen health
}

void Player::getCommands(InputManager inputManager) {
    if (inputManager.isKeyDown(SDLK_w))
        m_position.y += m_speed;
    else if (inputManager.isKeyDown(SDLK_s))
        m_position.y -= m_speed;
    
    if (inputManager.isKeyDown(SDLK_a))
        m_position.x -= m_speed;
    else if (inputManager.isKeyDown(SDLK_d))
        m_position.x += m_speed;
    
    if (inputManager.isKeyDown(SDLK_1)) {
        m_currentWeapon = 0;
    } else if (inputManager.isKeyDown(SDLK_2)) {
        m_currentWeapon = 1;
    } else if (inputManager.isKeyDown(SDLK_3)) {
        m_currentWeapon = 2;
    }
}

void Player::addWeapon(Weapon* weapon) {
    m_weapons.push_back(weapon);
    if (m_currentWeapon == -1)
        m_currentWeapon = 0;
}

