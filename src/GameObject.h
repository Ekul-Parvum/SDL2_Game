#ifndef EKUL_GAME_OBJECT_H
#define EKUL_GAME_OBJECT_H

// My Stuff
#include "PhysicsObject.h"
#include "PhysicsEngine.h"
#include "Texture.h"
#include "TextureManager.h"

// std
#include <string>

namespace Ekul {
    class GameObject {
        public:
        // Default constructor
        GameObject();

        // Constructor which also makes the physics object
        GameObject(PhysicsEngine* physicsEngine);

        // Copy Constructor
        // Makes copies of the GameObject at the given address
        GameObject(const GameObject&);

        // Copy Assignment
        // Copies the GameObject at the given address into a new address
        GameObject& operator=(const GameObject&)= default;

        // Move Constructor
        // Makes copies of the GameObject at the given address
        // But uses rvalue - so it reasigns pointers rather than remaking the object they point at.
        GameObject(GameObject&&) noexcept;

        // Move Assignment
        // Copies the GameObject at the given address into a new address
        // But uses rvalue - so it reasigns pointers rather than remaking the object they point at.
        GameObject& operator=(GameObject&&) noexcept = default;

        // Destructor
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
        bool loadImageFromFile(SDL_Renderer* renderer, TextureManager* textureManager, std::string path, SDL_Color keyColor = {0, 0, 0, 0}, bool colorKeyFlag = false);

        // Set the clip of the texture to be rendered
        void setTextureClip(SDL_Rect clip);

        void free();

        private:
        PhysicsEngine* mPhysicsEngine;
        PhysicsObject* mPhysicsObject;
        Texture mTexture;
    };
}

#endif
