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
objLoader obj;
bool mouseIn = false;
unsigned int model;
coordinate sphereCenter(0.0, 0.0, 0.0);
coordinate rayStart(0.0, 0.0, -5.0);
coordinate p1(-5.0, 5.0, -5.0);
coordinate p2(5.0, 5.0, -5.0);
coordinate p3(5.0, -5.0, -5.0);
coordinate p4(-5.0, -5.0, -5.0);

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
    
    model = obj.loadObject("assets/sphere.obj");
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
    
    //glTranslatef(0.0, 0.0, -5.0);
    //glRotatef(angle, 1.0, 1.0, 1.0);
    
    /*if (raySphere(sphereCenter.x, sphereCenter.y, sphereCenter.z, 0.0, 0.0, 1.0, rayStart.x, rayStart.y, rayStart.z, 1.0)) {
        glColor3f(1.0, 0.0, 0.0);
    } else {
        glColor3f(0.0, 0.0, 0.0);
    }*/
    
    if (rayPlane(0.0, 0.0, 1.0, 0.0, 0.0, -1.0, rayStart.x, rayStart.y, rayStart.z, p1, p2, p3, p4))
        glColor3f(1.0, 0.0, 0.0);
    else {
        glColor3f(0.0, 0.0, 0.0);
    }
    
    //draw ray
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glVertex3f(rayStart.x, rayStart.y, rayStart.z);
    glVertex3f(rayStart.x, rayStart.y, rayStart.z+100);
    glEnd();
    //draw plane
    glBegin(GL_QUADS);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p4.x, p4.y, p4.z);
    glEnd();
    glEnable(GL_LIGHTING);
    
    glCallList(model);
    glColor3f(1.0, 1.0, 1.0);
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
    bool b[4] = {0, 0, 0, 0};
    
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
                        case SDLK_UP:
                            b[0] = 1;
                            break;
                        case SDLK_RIGHT:
                            b[1] = 1;
                            break;
                        case SDLK_DOWN:
                            b[2] = 1;
                            break;
                        case SDLK_LEFT:
                            b[3] = 1;
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            b[0] = 0;
                            break;
                        case SDLK_RIGHT:
                            b[1] = 0;
                            break;
                        case SDLK_DOWN:
                            b[2] = 0;
                            break;
                        case SDLK_LEFT:
                            b[3] = 0;
                            break;
                    }
                    break;
            }
        }
        
        if (b[0])
            rayStart.y += 0.3;
        if (b[1])
            rayStart.x += 0.3;
        if (b[2])
            rayStart.y -= 0.3;
        if (b[3])
            rayStart.x -= 0.3;
        
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
