#include "Texture.h"

using namespace Ekul;

Texture::Texture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mClip = {0, 0, 0, 0};
}

Texture::~Texture()
{
    // Just dealocate stuff
    free();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, TextureManager* textureManager, std::string path, SDL_Color keyColor, bool colorKeyFlag)
{
    // Load new SDL_Texture
    mTexture = textureManager->loadImageFromFile(renderer, path, keyColor, colorKeyFlag);

    // Keep track of width and height:
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);

    // Return
    if (mTexture != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool Texture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor) 
{
    // If there was anything in this texture before, we need to get rid of it to load this new text texture
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == NULL) 
    {
        printf("Unable to render text to surface! Error: %s\n", TTF_GetError());
    } 
    else 
    {
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (mTexture == NULL) 
        {
            printf("Unable to convert text Surface to texture! Error: %s\n", SDL_GetError());
        }
        else
        {
            // Update image dimensions:
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // Free the surface - we won't need it anymore
        SDL_FreeSurface(textSurface);
    }

    // Return success flag
    return mTexture != NULL;
}
#endif

void Texture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture
    /*
        This takes rgb, and will change the rgb values of each pixel in the texture 
        based on the ratio of the given rgb values and 255.

        Example:
            If you gave (mTexture, 128, 255, 255), 
            128 is about half way to 255, so the red value for each pixel in the texture would be halved.
            The g and b values are both 255, thus they remain the same.
    */
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // printf("Rendering at: (%d, %d), w:%d, h:%d\n", x, y, mWidth, mHeight);

    // The portion of the screen/renderer that this texture will take up
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // Clip to render
    SDL_Rect* tempClip = NULL;

    // So if we are rendering only a clip of the texture, then we need to change renderQuad to match the clip's dimensions
    if (mClip.w != 0 && mClip.h != 0)
    {
        // renderQuad.w = mClip.w;
        // renderQuad.h = mClip.h;
        tempClip = &mClip;
    }

    // Put it to the screen!
    if (SDL_RenderCopyEx(renderer, mTexture, tempClip, &renderQuad, angle, center, flip) != 0)
    {
        printf("Texture.cpp Line %d | Failed to copy texture to renderer. SDL_Error: %s\n", __LINE__, SDL_GetError());
    }
}

SDL_Rect Texture::getClip()
{
    return mClip;
}

void Texture::setClip(SDL_Rect clip)
{
    mClip = clip;
}

int Texture::getWidth()
{
    return mWidth;
}

void Texture::setWidth(int width)
{
    mHeight = mHeight * ((float)width/(float)mWidth);
    mWidth = width;
}

void Texture::forceSetWidth(int width)
{
    mWidth = width;
}

int Texture::getHeight()
{
    return mHeight;
}

void Texture::setHeight(int height)
{
    mWidth = mWidth * ((float)height/(float)mHeight);
    mHeight = height;
}

void Texture::forceSetHeight(int height)
{
    mHeight = height;
}