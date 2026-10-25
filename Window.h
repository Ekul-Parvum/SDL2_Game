#ifndef WINDOW_HPP
#define WINDOW_HPP

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// std
#include <sstream>

namespace Ekul {
    class Window 
    {
        public:
            //Intializes internals
            Window();

            //Creates window
            bool init();

            //Creates renderer from internal window
            SDL_Renderer* createRenderer();

            //Handles window events
            void handleEvent( SDL_Event& e );

            //Deallocates internals
            void free();

            //Window dimensions
            int getWidth();
            int getHeight();

            //Window focii
            bool hasMouseFocus();
            bool hasKeyboardFocus();
            bool isMinimized();

        private:
            //Window data
            SDL_Window* mWindow;

            //Window dimensions
            int mWidth;
            int mHeight;

            //Window focus
            bool mMouseFocus;
            bool mKeyboardFocus;
            bool mFullScreen;
            bool mMinimized;
    };
}

#endif