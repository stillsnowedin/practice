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
    
    void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needUpdate = true; }
    void setScale(float newScale) { _scale = newScale; _needUpdate = true; }
    
    glm::vec2 getPosition() { return _position; }
    float getScale() { return _scale; }
    glm::mat4 getCameraMatrix() { return _cameraMatrix; }
    
private:
    int _screenWidth, _screenHeight;
    bool _needUpdate;
    float _scale;
    glm::vec2 _position;
    glm::mat4 _orthoMatrix;
    glm::mat4 _cameraMatrix;
    
};

#endif /* defined(__tuts__Camera2D__) */
