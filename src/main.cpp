/*
Author: Me
Purpose: Learn SDL2, and make a cool thing
Description: Trying to make a simple 2d game
*/

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// std
#include <sstream>
#include <vector>

// My Stuff
#include "Global.h"
#include "Window.h"
#include "GameObject.h"
#include "PhysicsEngine.h"
#include "TextureManager.h"

bool initSDL2();
bool loadMedia();
void close();

Ekul::PhysicsEngine physicsEngine = Ekul::PhysicsEngine();

Ekul::TextureManager textureManager = Ekul::TextureManager();

Ekul::GameObject gameObject2 = Ekul::GameObject(&physicsEngine);

Ekul::GameObject gameObject = Ekul::GameObject(&physicsEngine);

// const int GAME_OBJECTS_SIZE = 10;
// Ekul::GameObject gameObjects[GAME_OBJECTS_SIZE];

// Ekul::LinkedList<Ekul::GameObject> gameObjects;
std::vector<Ekul::GameObject> gameObjects;


int main(int argc, char* args[]) 
{
    printf("Starting\n");
    
    physicsEngine.setGravity(0.05);
    physicsEngine.setLowerBound(Constants::SCREEN_HEIGHT);
    physicsEngine.setUpperBound(0);
    physicsEngine.setRightBound(Constants::SCREEN_WIDTH);
    physicsEngine.setLeftBound(0);

    // Init gameobjects
    for (int i = 0; i < 10; i++)
    {
        gameObjects.push_back(Ekul::GameObject(&physicsEngine));
    }

    if(!initSDL2())
    {
        printf("[Line %d] initSDL2() failed.\n", __LINE__);
    }
    else
    {
        if (!loadMedia())
        {
            printf("[Line %d] loadMedia() failed.\n", __LINE__);
        }
        else
        {
            bool quit = false;

            SDL_Event event;

            // TODO: Add fps controll

            gameObject.setHeight(50);
            gameObject.setWidth(150);

            while (!quit)
            {
                
                // Clear screen:
                printf("\033[H\033[2J");

                // Handle events on queue:
                while (SDL_PollEvent(&event) != 0)
                {
                    // If user clicks the x to quit
                    if (event.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    // Handle window events
                    Global::gWindow.handleEvent(event);
                }

                // User input
                const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
                const int speed = 5;
                if (currentKeyStates[ SDL_SCANCODE_LEFT ])
                {
                    gameObject.moveCenterPos(-speed, 0);
                }
                if (currentKeyStates[ SDL_SCANCODE_RIGHT ])
                {
                    gameObject.moveCenterPos(speed, 0);
                }
                if (currentKeyStates[ SDL_SCANCODE_UP ])
                {
                    gameObject.moveCenterPos(0, -speed);
                }
                if (currentKeyStates[ SDL_SCANCODE_DOWN ])
                {
                    gameObject.moveCenterPos(0, speed);
                }

                physicsEngine.applyVelocities();

                if (!Global::gWindow.isMinimized())
                {
                    // Clear Screen
                    SDL_SetRenderDrawColor( Global::gRenderer, 0xAA, 0xAA, 0xAA, 0xAA );
                    SDL_RenderClear(Global::gRenderer);

                    // Render:
                    gameObject.render(Global::gRenderer);
                    gameObject2.render(Global::gRenderer);

                    for (int i = 0; i < (int)gameObjects.size(); i++)
                    {
                        gameObjects[i].render(Global::gRenderer);
                    }

                    // Present to window:
                    SDL_RenderPresent(Global::gRenderer);
                }
            }
        }
    }

    close();
    
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
        if(!Global::gWindow.init())
        {
            printf("[Line %d] Window could not be created! SDL_Error: %s\n", __LINE__, SDL_GetError());
            success = false;
        }
        else
        {
            // Create Renderer:
            Global::gRenderer = Global::gWindow.createRenderer();
            if (Global::gRenderer == NULL)
            {
                printf("[Line %d] Renderer could not be created! SDL_Error: %s\n", __LINE__, SDL_GetError());
                success = false;
            }
            else
            {
                // Init Renderer color
                Uint8 greyScaleNumber = 0xAA;
                SDL_SetRenderDrawColor(Global::gRenderer, greyScaleNumber, greyScaleNumber, greyScaleNumber, greyScaleNumber);
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

bool loadMedia()
{
    bool success = true;

    // Load texture 
    if (!gameObject.loadImageFromFile(Global::gRenderer, &textureManager, Constants::FilePaths::plainColor))
    {
        printf("[Line %d] Couldn't load text to texture\n", __LINE__);
        success = false;
    }
    else
    {
        gameObject.setTextureClip({0, 0, 1, 1});
    }

    // Load texture 
    if (!gameObject2.loadImageFromFile(Global::gRenderer, &textureManager, Constants::FilePaths::plainColor))
    {
        printf("[Line %d] Couldn't load text to texture\n", __LINE__);
        success = false;
    }
    else
    {
        gameObject2.setTextureClip({4, 0, 1, 1});
        gameObject2.setWidth(500);
        gameObject2.setHeight(10);
    }

    for (int i = 0; i < (int)gameObjects.size(); i++)
    {
        if (!gameObjects[i].loadImageFromFile(Global::gRenderer, &textureManager, Constants::FilePaths::plainColor))
        {
            printf("[Line %d] Couldn't load image to texture\n", __LINE__);
            success = false;
        }
        else
        {
            gameObjects[i].setTextureClip({3, 0, 1, 1});
            gameObjects[i].setWidth(10);
            gameObjects[i].setHeight(30);
            gameObjects[i].setCenterPos(100 + 60 * i, 100 + 60 * i);
        }
    }

    return success;
}

void close()
{
    // Free gameobject
    gameObject.free();
    gameObject2.free();

    SDL_DestroyRenderer( Global::gRenderer );
    Global::gWindow.free();

    physicsEngine.free();
    textureManager.free();
    
    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
}
#pragma endregion