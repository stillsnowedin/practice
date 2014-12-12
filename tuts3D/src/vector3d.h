#ifndef __tuts3D__vector3d__
#define __tuts3D__vector3d__

#include <iostream>
#include <cmath>

class vector3d {
public:
    float x, y, z;
    
    vector3d();
    vector3d(float a, float b);
    vector3d(float a, float b, float c);
    
    float dotProduct(const vector3d& vec2);
    vector3d crossProduct(const vector3d& vec2);
    float length();
    void normalize();
    
    void change(float a, float b, float c);
    void change(vector3d& vec2);
    void change(vector3d vec2);
    void changeX(float a);
    void changeY(float b);
    void changeZ(float c);
    
    vector3d operator+(const vector3d& vec2);
    vector3d operator-(const vector3d& vec2);
    vector3d operator*(float num);
    vector3d operator/(float num);
    
    vector3d& operator+=(const vector3d& vec2);
    vector3d& operator-=(const vector3d& vec2);
    vector3d& operator*=(float num);
    vector3d& operator/=(float num);
    
    bool operator==(const vector3d vec2);
    bool operator!=(const vector3d vec2);
    
    friend std::ostream& operator<<(std::ostream& out, vector3d& vec);
    
};

#endif /* defined(__tuts3D__vector3d__) */
