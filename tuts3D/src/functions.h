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

//textures
unsigned int loadTexture(const char* filename);

//skybox
void initSkybox();
void killSkybox();
void drawSkybox(float size);
void drawCube(float size);

//collision
bool raySphere(float xc, float yc, float zc, float xd, float yd, float zd, float xs, float ys, float zs, float r);
bool rayPlane(float xn, float yn, float zn, float xd, float yd, float zd, float xs, float ys, float zs, coordinate p1, coordinate p2, coordinate p3, coordinate p4);
float triangleArea(coordinate p1, coordinate p2, coordinate p3);

#endif /* defined(__tuts3D__functions__) */
