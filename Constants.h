#ifndef CONSTANTS_H
#define CONSTANTS_H

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// My Files
#include "./Window.h"

namespace Constants {
    // These are only used when creating the window - it is resizable after.
    const int SCREEN_WIDTH = 640; 
    const int SCREEN_HEIGHT = 480;

    Ekul::Window gWindow;

    SDL_Renderer* gRenderer = NULL;
}

#endif