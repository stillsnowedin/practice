#include "Camera2D.h"

Camera2D::Camera2D() :
    m_position(0.0f, 0.0f),
    m_orthoMatrix(1.0f),
    m_cameraMatrix(1.0f),
    m_scale(1.0f),
    m_needUpdate(true),
    m_screenWidth(500),
    m_screenHeight(500) {

}

Camera2D::~Camera2D() {

}

void Camera2D::init(int screenWidth, int screenHeight) {
    m_screenHeight = screenHeight;
    m_screenWidth = screenWidth;
    m_orthoMatrix = glm::ortho(0.0f, (float)m_screenWidth, 0.0f, (float)m_screenHeight);
}

void Camera2D::update() {
    if (m_needUpdate) {
        glm::vec3 translate(-m_position.x + m_screenWidth/2, -m_position.y + m_screenHeight/2, 0.0f);
        m_cameraMatrix = glm::translate(m_orthoMatrix, translate);
        glm::vec3 scale(m_scale, m_scale, 0.0f);
        m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
        m_needUpdate = false;
    }
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenLoc) {
    //invert y direction
    screenLoc.y = m_screenHeight - screenLoc.y;
    //center the screen on 0,0
    screenLoc -= glm::vec2(m_screenWidth/2, m_screenHeight/2);
    //scale the loc
    screenLoc /= m_scale;
    //translate with camera position
    screenLoc += m_position;
    return screenLoc;
}

/*
 * return true if sprite is in range of camera
 */
bool Camera2D::isInView(const glm::vec2& spriteLoc, const glm::vec2& spriteSize) {
    glm::vec2 scaledScreenSize = glm::vec2(m_screenWidth, m_screenHeight) / m_scale;
    glm::vec2 cameraCenter = m_position;
    glm::vec2 spriteCenter = spriteLoc + glm::vec2(spriteSize.x / 2.0f, spriteSize.y / 2.0f);
    glm::vec2 distance = spriteCenter - cameraCenter;
    
    const float MIN_X_DISTANCE = spriteSize.x / 2.0f + scaledScreenSize.x / 2.0f;
    const float MIN_Y_DISTANCE = spriteSize.y / 2.0f + scaledScreenSize.y / 2.0f;
    
    if (abs(distance.x) < MIN_X_DISTANCE && abs(distance.y) < MIN_Y_DISTANCE)
        return true;
    else
        return false;
}