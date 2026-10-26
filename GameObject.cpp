#include "GameObject.h"

using namespace Ekul;

GameObject::GameObject()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

GameObject::~GameObject()
{
    // Just dealocate stuff
    free();
}

bool GameObject::loadFromFile(SDL_Renderer* renderer, std::string path)
{
    // Get rid of pre-existing texture.
    free();

    // The final texture
    SDL_Texture* newTexture = NULL;

    // Load the image
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("[Line %d] Failed to load image at %s. IMG ERROR: %s\n", __LINE__, path.c_str(), IMG_GetError());
    }
    else
    {
        //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xff, 0xff, 0xff));

        // Make a texture out of the surface
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("[Line %d] Failed to convert image surface to texture at %s. IMG ERROR: %s\n", __LINE__, path.c_str(), IMG_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Free up that surface
        SDL_FreeSurface(loadedSurface);
    }

    mTexture = newTexture;
    return mTexture != NULL;
}

#if defined(SDL_TTF_MAJOR_VERSION)
bool GameObject::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color textColor) 
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

void GameObject::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void GameObject::setColor( Uint8 red, Uint8 green, Uint8 blue )
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

void GameObject::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void GameObject::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void GameObject::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    // The portion of the screen/renderer that this texture will take up
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // So if we are rendering only a clip of the texture, then we need to change renderQuad to match the clip's dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Put it to the screen!
    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int GameObject::getWidth()
{
    return mWidth;
}

int GameObject::getHeight()
{
    return mHeight;
}