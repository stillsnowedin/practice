//
//  main.cpp
//  tuts3D
//
//  Created by Kathryn on 12/9/14.
//  Copyright (c) 2014 stillsnowedin. All rights reserved.
//

#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

float angle = 0;
//const int triangle = 1;
unsigned int tex;

void drawCube(float size) {
    float difamb[] = { 0.5, 0.0, 0.5, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, difamb);
    
    glBegin(GL_QUADS);
    //front
    glNormal3f(0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, -size/2, size/2);
    glVertex3f(size/2, -size/2, size/2);
    
    //left
    glNormal3f(-1.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(-size/2, -size/2, size/2);
    
    //back
    glNormal3f(0.0, 0.0, -1.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(size/2, size/2, -size/2);
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(size/2, -size/2, -size/2);

    //right
    glNormal3f(1.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(size/2, size/2, -size/2);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(size/2, -size/2, size/2);
    glVertex3f(size/2, -size/2, -size/2);

    //top
    glNormal3f(0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, size/2);
    glVertex3f(-size/2, size/2, -size/2);
    glVertex3f(size/2, size/2, -size/2);

    //bottom
    glNormal3f(0.0, -1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(size/2, -size/2, size/2);
    glVertex3f(-size/2, -size/2, size/2);
    glVertex3f(-size/2, -size/2, -size/2);
    glVertex3f(size/2, -size/2, -size/2);
    glEnd();
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
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_COLOR_MATERIAL);
    
    //float dif[] = { 1.0, 1.0, 1.0, 1.0 };
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    //float amb[] = { 0.2, 0.2, 0.2, 1.0 };
    //glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    
    tex = loadTexture("assets/wall.bmp");
    /*glNewList(triangle, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 2.0, -5.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-2.0, -2.0, -5.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(2.0, -2.0, -5.0);
    glEnd();
    glEndList();
     */
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnableClientState(GL_COLOR_ARRAY);
    glLoadIdentity();
    
    //float pos[] = { -2.0, 2.0, -3.0, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
    //glScalef(1.0, 0.5, 0.5);
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    //glCallList(triangle);
    
    //drawCube(1.0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 2.0);
    glVertex3f(-2.0, 2.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-2.0, -2.0, 0.0);
    glTexCoord2f(2.0, 0.0);
    glVertex3f(2.0, -2.0, 0.0);
    glTexCoord2f(2.0, 2.0);
    glVertex3f(2.0, 2.0, 0.0);
    glEnd();
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
