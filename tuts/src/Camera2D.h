#ifndef __tuts__Camera2D__
#define __tuts__Camera2D__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
public:
    Camera2D();
    ~Camera2D();
    
    void init(int screenWidth, int screenHeight);
    void update();
    glm::vec2 convertScreenToWorld(glm::vec2 screenLoc);
    bool isInView(const glm::vec2& spriteLoc, const glm::vec2& spriteSize);
    
    void setPosition(const glm::vec2& newPosition) { m_position = newPosition; m_needUpdate = true; }
    void setScale(float newScale) { m_scale = newScale; m_needUpdate = true; }
    
    glm::vec2 getPosition() { return m_position; }
    float getScale() { return m_scale; }
    glm::mat4 getCameraMatrix() { return m_cameraMatrix; }
    
private:
    int m_screenWidth, m_screenHeight;
    bool m_needUpdate;
    float m_scale;
    glm::vec2 m_position;
    glm::mat4 m_orthoMatrix;
    glm::mat4 m_cameraMatrix;
    
};

#endif /* defined(__tuts__Camera2D__) */
