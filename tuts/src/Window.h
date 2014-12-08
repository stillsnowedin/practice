//
//  Window.h
//  tuts
//
//  Created by Kathryn on 12/7/14.
//  Copyright (c) 2014 stillsnowedin. All rights reserved.
//

#ifndef __tuts__Window__
#define __tuts__Window__

#include <string>
#include <SDL2/SDL.h>
#include <GLUT/GLUT.h>
#include "Errors.h"

enum WindowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

class Window {
public:
    Window();
    ~Window();
    
    int create(std::string name, int width, int height, unsigned int currentFlags);
    int getWidth() { return _windowWidth; }
    int getHeight() { return _windowHeight; }
    void swapBuffer();
    
private:
    SDL_Window* _sdlWindow;
    int _windowWidth, _windowHeight;
    
};
#endif /* defined(__tuts__Window__) */
