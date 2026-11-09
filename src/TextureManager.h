#ifndef EKUL_TEXTURE_MANAGER_H
#define EKUL_TEXTURE_MANAGER_H

// std
#include <vector>
#include <string>

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace Ekul
{
    class TextureManager
    {
        public:
        TextureManager();

        ~TextureManager();

        SDL_Texture* loadImageFromFile(SDL_Renderer* renderer, std::string path, SDL_Color keyColor = {0, 0, 0, 0}, bool colorKeyFlag = false);

        bool deleteTexture(SDL_Texture* texture);

        void free();
        
        private:
        
        std::vector<SDL_Texture*> mTextures;

    };
}


#endif