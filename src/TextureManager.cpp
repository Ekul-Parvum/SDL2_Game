#include "TextureManager.h"

using namespace Ekul;

TextureManager::TextureManager()
{
    
}

TextureManager::~TextureManager()
{
    printf("Texture Manager Destructor\n");
    free();
}

/// @brief Loads image at the given path into an SDL_Texture, keeps a pointer to that 
/// texture to manage, and returns pointer to that SDL_Texture
/// @param renderer 
/// @param path 
/// @param keyColor 
/// @param colorKeyFlag 
/// @return returns pointer to the SDL_Texture it creates
SDL_Texture* TextureManager::loadImageFromFile(SDL_Renderer* renderer, std::string path, SDL_Color keyColor, bool colorKeyFlag)
{
    // The new texture we are making.
    SDL_Texture* newTexture = NULL;

    // Load the given image:
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("[TextureManager - %d] WARNING: Failed to load image at %s.", __LINE__, path.c_str());

        return NULL;
    }
    else
    {
        // Set color keying:
        if (colorKeyFlag)
        {
            SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, keyColor.r, keyColor.g, keyColor.b));
        }

        // Make a new texture out of the surface:
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (newTexture == NULL)
        {
            printf("[TextureManager - %d] WARNING: Failed to create texture from surface.", __LINE__);
        }
        else
        {
            // Add the new texture to mTextures:
            mTextures.push_back(newTexture);
        }
        
        // Free the surface
        SDL_FreeSurface(loadedSurface);

        return newTexture;
    }

}

/// @brief Searches mTextures for the given texture, deletes the SDL_Texture, and pops it from the vector.
/// @param texture A pointer to the texture to delete.
/// @return Returns true if it found and deleted the texture - false otherwise.
bool TextureManager::deleteTexture(SDL_Texture* texture)
{
    printf("Deleting Texture: %p\n", (void*)texture);

    // Find the texture:
    for (int i = 0; i < (int)mTextures.size(); i++)
    {
        if (mTextures[i] == texture)
        {
            // Destroy the Texture:
            SDL_DestroyTexture(texture);

            // Move target texture to back, and delete it:
            // I do it this way to avoid moving every element after the target.
            // This method is O(1) while the other is O(n).
            std::swap(mTextures[i], mTextures.back());
            mTextures.pop_back();

            // We found and deleted the texture, so return true:
            return true;
        }
    }

    // In this case, we did not find the texture, so return false
    return false;
}

/// @brief Destroys all the SDL_Textures it has.
void TextureManager::free()
{
    printf("Freeing Textures\n");

    // Loop through textures, and free them:
    for (int i = (int)mTextures.size() - 1; i >= 0; i--)
    {
        // Destroy the SDL_Texture:
        SDL_DestroyTexture(mTextures.back());

        // Remove it from the vector:
        mTextures.pop_back();
    }
}