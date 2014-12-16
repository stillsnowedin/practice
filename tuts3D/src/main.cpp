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
#include "objLoader.h"

float angle = 0.0;
unsigned int model;
objLoader obj;

void init() {
    glClearColor(0.1, 0.1, 0.1, 1.0f);
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
    //glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_FOG);
    //glEnable(GL_BLEND);
    
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
//    glFogi(GL_FOG_MODE, GL_LINEAR);
//    //glFogf(GL_FOG_DENSITY, 0.3);
//    glFogf(GL_FOG_START, 1.0);
//    glFogf(GL_FOG_END, 5.0);
//    float color[] = {0.1, 0.1, 0.1, 1.0};
//    glFogfv(GL_FOG_COLOR, color);
    
    float dif[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    //float amb[] = { 0.2, 0.2, 0.2, 1.0 };
    //glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    
    model = obj.loadObject("assets/test.obj");
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    float pos[] = {-1.0, 1.0, -2.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(angle, 1.0, 1.0, 1.0);
    
    glCallList(model);
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
