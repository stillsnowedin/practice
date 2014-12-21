//
//  main.cpp
//  tuts3D
//
//  Created by stillsnowedin on 12/9/14.
//

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "objLoader.h"
#include "functions.h"

float resW = 1024.0f;
float resH = 768.0f;
float angle = 0.0;
unsigned int model;
objLoader obj;
bool mouseIn = false;

void init() {
    glClearColor(0.3, 0.3, 0.3, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glm::mat4 projection = glm::perspective(45.0f, resW/resH, 1.0f, 500.0f);
    glLoadMatrixf(glm::value_ptr(projection));
    
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_COLOR_MATERIAL);
    
    float dif[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dif);
    
    model = obj.loadObject("assets/test.obj");
    initSkybox();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    control(0.2, 0.2, mouseIn);
    drawSkybox(50.0);
    updateCamera();
    
    float pos[] = {-1.0, 5.0, 10.0, 1.0};
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
    
    SDL_Window* screen = SDL_CreateWindow("Tuts 3D!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, resW, resH, SDL_WINDOW_OPENGL);
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
                case SDL_MOUSEBUTTONDOWN:
                    mouseIn = true;
                    SDL_SetRelativeMouseMode(SDL_TRUE);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_p:
                            mouseIn = false;
                            SDL_SetRelativeMouseMode(SDL_FALSE);
                            break;
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                    }
                    break;
            }
        }
        
        display();
        SDL_GL_SwapWindow(screen);
        //SDL_WarpMouseInWindow(screen, resW/2, resH/2);
        
        angle += 0.5;
        if (angle > 360)
            angle = 0;
        
        if (1000/30 > SDL_GetTicks() - start) {
            SDL_Delay(1000/30 - (SDL_GetTicks() - start));
        }
    }
    
    SDL_Quit();
    killSkybox();
    
    return 0;
}
