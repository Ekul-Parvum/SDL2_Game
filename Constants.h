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
        inline std::string derpySmilePath =                     "media/Pictures/DerpySmile_x32scale.png";
        inline std::string smilingStarsPath =                   "media/Pictures/SmilingStars_x32scale.bmp";
        inline std::string expressionlessSpriteMap =            "media/Pictures/ExpressionlessSpriteMap.png";
        inline std::string expressionlessSpriteMap_x32scale =   "media/Pictures/ExpressionlessSpriteMap_x32scale.png";
        inline std::string soundPrompt =                        "media/Pictures/soundPrompt.png";
        inline std::string dotBMP =                             "media/Pictures/dot.bmp";
        inline std::string bgBackground =                       "media/Pictures/bg.png";
        inline std::string plainColor =                         "media/Pictures/plainColorSheet.png";
    }
}

#endif