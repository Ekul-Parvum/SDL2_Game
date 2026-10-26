#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// My stuff
#include "Texture.h"

namespace Ekul {
    class GameObject 
    {
        public:
            GameObject();

            SDL_Rect* getPhysicsObject();

            Ekul::Texture getTexture();

        private:
            Ekul::Texture mTexture;

            SDL_Rect mPhysicsObject;
    };
}

#endif