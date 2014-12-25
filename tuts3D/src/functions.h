#ifndef __tuts3D__functions__
#define __tuts3D__functions__

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <cmath>

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

#endif /* defined(__tuts3D__functions__) */
