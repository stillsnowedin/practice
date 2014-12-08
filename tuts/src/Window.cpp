//
//  Window.cpp
//  tuts
//
//  Created by Kathryn on 12/7/14.
//  Copyright (c) 2014 stillsnowedin. All rights reserved.
//

#include "Window.h"

Window::Window() {
    
}

Window::~Window() {
    
}

int Window::create(std::string name, int width, int height, unsigned int currentFlags) {
    Uint32 flags = SDL_WINDOW_OPENGL;
    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }
    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }
    
    //_windowWidth = width;
    //_windowHeight = height;
    _sdlWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (_sdlWindow == nullptr) {
        fatalError("SDL Window could not be created!");
    }
    
    SDL_GLContext context = SDL_GL_CreateContext(_sdlWindow);
    if (context == nullptr) {
        fatalError("SDL Context could not be created!");
    }
    
    //OpenGL version
    printf("*** OpenGL Version: %s ***\n", glGetString(GL_VERSION));
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    //VSYNC
    SDL_GL_SetSwapInterval(0);
    
    return 0;
}
void Window::swapBuffer() {
    SDL_GL_SwapWindow(_sdlWindow);
}