// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// std
#include <sstream>

// My Stuff
#include "Window.h"
#include "GameObject.h"

bool initSDL2();

// These are only used when creating the window - it is resizable after.
const int SCREEN_WIDTH = 640; 
const int SCREEN_HEIGHT = 480;

Ekul::Window gWindow;

SDL_Renderer* gRenderer = NULL;

Ekul::GameObject gameObject = Ekul::GameObject();

int main(int argc, char* args[]) 
{
    if(!initSDL2())
    {
        printf("[Line %d] initSDL2() failed.\n", __LINE__);
    }
    else
    {
        bool quit = false;

        SDL_Event event;

        // TODO: Add fps controll

        while (!quit)
        {
            // Handle events on queue:
            while (SDL_PollEvent(&event) != 0)
            {
                // If user clicks the x to quit
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }

                // Handle window events
                gWindow.handleEvent(event);
            }
            
            if (!gWindow.isMinimized())
            {
                // Clear Screen
                SDL_SetRenderDrawColor( gRenderer, 0xAA, 0xAA, 0xAA, 0xAA );
                SDL_RenderClear(gRenderer);

                // REnder:

                // Present to window:
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    
    return 0;
}

#pragma region functions
bool initSDL2()
{
     // Initialization flag
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("[Line %d] SDL could not initialize! SDL_Error: %s\n", __LINE__, SDL_GetError());
        success = false;
    }
     else
    {
        //Create window
        if(!gWindow.init())
        {
            printf("[Line %d] Window could not be created! SDL_Error: %s\n", __LINE__, SDL_GetError());
            success = false;
        }
        else
        {
            // Create Renderer:
            gRenderer = gWindow.createRenderer();
            if (gRenderer == NULL)
            {
                printf("[Line %d] Renderer could not be created! SDL_Error: %s\n", __LINE__, SDL_GetError());
                success = false;
            }
            else
            {
                // Init Renderer color
                Uint8 greyScaleNumber = 0xAA;
                SDL_SetRenderDrawColor(gRenderer, greyScaleNumber, greyScaleNumber, greyScaleNumber, greyScaleNumber);
            }
        }
    }

    // Init PNG Loading from SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("[Line %d] SDL_image could not init! SDL_Error: %s\n", __LINE__, IMG_GetError());
        success = false;
    } 

    // Init SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("[Line %d] SDL_ttf could not init! Error: %s\n", __LINE__, TTF_GetError());
        success = false;
    } 

    return success;
}

#pragma endregion