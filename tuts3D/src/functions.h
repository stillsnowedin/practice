#ifndef __tuts3D__functions__
#define __tuts3D__functions__

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <cmath>

void drawCube(float size);
void drawSkybox(float size);
void initSkybox();
void killSkybox();
void lockCamera();
void moveCamera(float, float);
void moveCameraUp(float, float);
void control(float,float,bool);
void updateCamera();
unsigned int loadTexture(const char* filename);

#endif /* defined(__tuts3D__functions__) */
