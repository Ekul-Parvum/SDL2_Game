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
    constexpr int SCREEN_WIDTH = 640; 
    constexpr int SCREEN_HEIGHT = 480;

    inline Ekul::Window gWindow;

    inline SDL_Renderer* gRenderer = NULL;

    namespace FilePaths {
        // File paths to the images I care about:
        inline std::string derpySmilePath =                    "media/Pictures/DerpySmile_x32scale.png";
        // std::string smilingStarsPath =                  "media/Pictures/SmilingStars_x32scale.bmp";
        // std::string expressionlessSpriteMap =           "media/Pictures/ExpressionlessSpriteMap.png";
        // std::string expressionlessSpriteMap_x32scale =  "media/Pictures/ExpressionlessSpriteMap_x32scale.png";
        // std::string soundPrompt =                       "media/Pictures/soundPrompt.png";
        // std::string dotBMP =                            "media/Pictures/dot.bmp";
        // std::string bgBackground =                      "media/Pictures/bg.png";
    }
}

#endif