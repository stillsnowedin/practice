#include "InputManager.h"

InputManager::InputManager() : m_mouseLoc(0.0f) {

}

InputManager::~InputManager() {

}

void InputManager::pressKey(unsigned int keyID) {
    m_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
    m_keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
    auto it = m_keyMap.find(keyID);
    if (it != m_keyMap.end())
        return it->second;
    else
        return false;
}

void InputManager::setMouseLoc(float x, float y) {
    m_mouseLoc.x = x;
    m_mouseLoc.y = y;
}

