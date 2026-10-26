#ifndef EKUL_TEXTURE_HPP
#define EKUL_TEXTURE_HPP

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// std
#include <string>

namespace Ekul {
    class Texture {
        public:
        //Initializes variables
        Texture();

        //Deallocates memory
        ~Texture();

        //Loads image at specified path
        bool loadFromFile(SDL_Renderer* renderer, std::string path);

        #if defined(SDL_TTF_MAJOR_VERSION)
        // Loads image from given string
        bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor);
        #endif

        //Deallocates texture
        void free();

        // For changing the color
        void setColor(Uint8 r, Uint8 g, Uint8 b);

        // Set blend mode
        void setBlendMode(SDL_BlendMode blending);

        // Set Alpha
        void setAlpha(Uint8 alpha);

        //Renders texture at given point
        void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        //Gets image dimensions
        int getWidth();
        int getHeight();

        private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
    };
}



#endif