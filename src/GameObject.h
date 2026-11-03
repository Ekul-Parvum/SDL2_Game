#ifndef EKUL_GAME_OBJECT_H
#define EKUL_GAME_OBJECT_H

// My Stuff
#include "PhysicsObject.h"
#include "Texture.h"

// std
#include <string>

namespace Ekul {
    class GameObject {
        public:
        GameObject();

        ~GameObject();

        // Modifying Velocity:
        void changeVelocity(float x, float y);
        void setXVelocity(float x);
        void setYVelocity(float y);

        // Get Velocity:
        float getXVelocity();
        float getYVelocity();
        
        // Get center point:
        SDL_Point getCenterPos();

        // Change PhysicsObject position:
        void setCenterPos(int x, int y);
        void moveCenterPos(int x_change, int y_change);

        // Rotate Object:
        void rotateAngle(float degrees);
        void setAngle(float degrees);

        // Get Width, Height, & Angle:
        int getHitboxWidth();
        int getHitboxHeight();
        float getHitboxAngle();
        
        //Set Width & Height:
        void setWidth(int width);
        void setHeight(int height);
        
        void render(SDL_Renderer* renderer);

        // Loads the given image into the texture
        bool loadImageFromFile(SDL_Renderer* renderer, std::string path);

        // Set the clip of the texture to be rendered
        void setTextureClip(SDL_Rect clip);

        void free();

        private:
        PhysicsObject mPhysicsObject;
        Texture mTexture;
    };
}

#endif