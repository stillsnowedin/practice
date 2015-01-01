#ifndef __tuts3D__functions__
#define __tuts3D__functions__

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <cmath>
#include "objLoader.h"

//camera
void moveCamera(float, float);
void moveCameraUp(float, float);
void lockCamera();
void updateCamera();
void control(float,float,bool);
void moveTo(coordinate c);
coordinate cameraPosition();

//textures
unsigned int loadTexture(const char* filename);

//skybox
void initSkybox();
void killSkybox();
void drawSkybox(float size);
void drawCube(float size);

//collision
bool raySphere(float xc, float yc, float zc, float xd, float yd, float zd, float xs, float ys, float zs, float r, float* dist = NULL, coordinate* point = NULL);
bool rayPlane(float xn, float yn, float zn, float xd, float yd, float zd, float xs, float ys, float zs, coordinate p1, coordinate p2, coordinate p3, coordinate p4, float* dist = NULL, coordinate* point = NULL);
bool sphereSphere(coordinate& c1, float r1, coordinate c2, float r2);
bool spherePlane(coordinate& sp, float r, coordinate vn, coordinate p1, coordinate p2, coordinate p3, coordinate p4);
float triangleArea(coordinate p1, coordinate p2, coordinate p3);
float pointDistance(coordinate p1, coordinate p2);

#endif /* defined(__tuts3D__functions__) */
