#ifndef __tuts3D__functions__
#define __tuts3D__functions__

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>

struct coordinate {
    float x, y, z;
    coordinate(float a, float b, float c) : x(a), y(b), z(c) {};
};

struct face {
    int faceNum;
    bool isQuad;
    int faces[4];
    
    face(int facen, int f1, int f2, int f3) : faceNum(facen) {
        faces[0] = f1;
        faces[1] = f2;
        faces[2] = f3;
        isQuad = false;
    }
    
    face(int facen, int f1, int f2, int f3, int f4) : faceNum(facen) {
        faces[0] = f1;
        faces[1] = f2;
        faces[2] = f3;
        faces[3] = f4;
        isQuad = true;
    }
};

int loadObject(const char* filename);
unsigned int loadTexture(const char* filename);

#endif /* defined(__tuts3D__functions__) */
