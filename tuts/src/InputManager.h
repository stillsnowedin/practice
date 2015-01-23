#ifndef __tuts__InputManager__
#define __tuts__InputManager__

#include <unordered_map>
#include <glm/glm.hpp>

class InputManager {
public:
    InputManager();
    ~InputManager();
    
    void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);
    bool isKeyPressed(unsigned int keyID);
    void setMouseLoc(float x, float y);
    glm::vec2 getMouseLoc() const { return m_mouseLoc; };
    
private:
    std::unordered_map<unsigned int, bool> m_keyMap;
    glm::vec2 m_mouseLoc;
    
};

#endif /* defined(__tuts__InputManager__) */
