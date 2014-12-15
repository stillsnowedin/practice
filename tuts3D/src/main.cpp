//
//  main.cpp
//  tuts3D
//
//  Created by stillsnowedin on 12/9/14.
//

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

float angle = 0;
unsigned int tex;
unsigned int cube;

int loadObject(const char* filename) {
    std::vector<std::string*> coords;
    std::vector<coordinate*> vertices;
    std::vector<face*> faces;
    std::vector<coordinate*> normals;
    
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Could not open " << filename << std::endl;
        return -1;
    }
    
    char buf[256];
    while (!in.eof()) {
        in.getline(buf, 256);
        coords.push_back(new std::string(buf));
    }
    
    for (int k=0; k<coords.size(); k++) {
        if ((*coords[k])[0] == '#') { //ignore comments
            continue;
        } else if ((*coords[k])[0] == 'v' && (*coords[k])[1] == ' ') { //load vertices
            float tmpx, tmpy, tmpz;
            sscanf(coords[k]->c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
            vertices.push_back(new coordinate(tmpx, tmpy, tmpz));
        } else if ((*coords[k])[0] == 'v' && (*coords[k])[1] == 'n') { //load normals
            float tmpx, tmpy, tmpz;
            sscanf(coords[k]->c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
            normals.push_back(new coordinate(tmpx, tmpy, tmpz));
        } else if ((*coords[k])[0] == 'f') { //load faces
            int a, b, c, d, e;
            if (count(coords[k]->begin(), coords[k]->end(), ' ') == 4) { //quad
                sscanf(coords[k]->c_str(), "f %d//%d %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b, &e, &b);
                faces.push_back(new face(b, a, c, d, e));
            } else { //triangle
                sscanf(coords[k]->c_str(), "f %d//%d %d//%d %d//%d", &a, &b, &c, &b, &d, &b);
                faces.push_back(new face(b, a, c, d));
            }
        }
        
    }
    
    //draw
    int num;
    num = glGenLists(1);
    glNewList(num, GL_COMPILE);
    for (int j = 0; j < faces.size(); j++) {
        if (faces[j]->isQuad) {
            glBegin(GL_QUADS);
            glNormal3f(normals[faces[j]->faceNum-1]->x, normals[faces[j]->faceNum-1]->y, normals[faces[j]->faceNum-1]->z);
            glVertex3f(vertices[faces[j]->faces[0]-1]->x, vertices[faces[j]->faces[0]-1]->y, vertices[faces[j]->faces[0]-1]->z);
            glVertex3f(vertices[faces[j]->faces[1]-1]->x, vertices[faces[j]->faces[1]-1]->y, vertices[faces[j]->faces[1]-1]->z);
            glVertex3f(vertices[faces[j]->faces[2]-1]->x, vertices[faces[j]->faces[2]-1]->y, vertices[faces[j]->faces[2]-1]->z);
            glVertex3f(vertices[faces[j]->faces[3]-1]->x, vertices[faces[j]->faces[3]-1]->y, vertices[faces[j]->faces[3]-1]->z);
            glEnd();
        } else {
            glBegin(GL_TRIANGLES);
            glNormal3f(normals[faces[j]->faceNum-1]->x, normals[faces[j]->faceNum-1]->y, normals[faces[j]->faceNum-1]->z);
            glVertex3f(vertices[faces[j]->faces[0]-1]->x, vertices[faces[j]->faces[0]-1]->y, vertices[faces[j]->faces[0]-1]->z);
            glVertex3f(vertices[faces[j]->faces[1]-1]->x, vertices[faces[j]->faces[1]-1]->y, vertices[faces[j]->faces[1]-1]->z);
            glVertex3f(vertices[faces[j]->faces[2]-1]->x, vertices[faces[j]->faces[2]-1]->y, vertices[faces[j]->faces[2]-1]->z);
            glEnd();
        }
    }
    glEndList();
    
    for (int i=0; i<coords.size(); i++) {
        delete coords[i];
    }
    for (int i=0; i<faces.size(); i++) {
        delete faces[i];
    }
    for (int i=0; i<normals.size(); i++) {
        delete normals[i];
    }
    for (int i=0; i<vertices.size(); i++) {
        delete vertices[i];
    }
    return num;
}

unsigned int loadTexture(const char* filename) {
    SDL_Surface* img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);
    
    return id;
}

void init() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glm::mat4 projection = glm::perspective(45.0, 1024.0/768.0, 1.0, 500.0);
    glLoadMatrixf(glm::value_ptr(projection));
    
    // if you're using the new shader based pipelines
    //GLint projectionUniformLocation = ...;
    //glUniformMatrix4fv(projectionUniformLocation, 1, GL_FALSE, glm::value_ptr(projection));
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    float dif[] = { 0.0, 0.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    //float amb[] = { 0.2, 0.2, 0.2, 1.0 };
    //glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    
    tex = loadTexture("assets/wall.bmp");
    cube = loadObject("assets/test.obj");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glLoadIdentity();
    
    float pos[] = { -1.0, 1.0, -2.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
    //glScalef(1.0, 0.5, 0.5);
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    //glCallList(triangle);
    
    glCallList(cube);
}

int main(int argc, const char * argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    SDL_Window* screen = SDL_CreateWindow("Tuts 3D!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(screen);
    init();
    
    bool running = true;
    Uint32 start;
    SDL_Event event;
    
    while (running) {
        start = SDL_GetTicks();
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        
        display();
        SDL_GL_SwapWindow(screen);
        angle += 0.5;
        if (angle > 360)
            angle = 0;
        
        if (1000/30 > SDL_GetTicks() - start) {
            SDL_Delay(1000/30 - (SDL_GetTicks() - start));
        }
    }
    SDL_Quit();
    
    return 0;
}
