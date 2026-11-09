#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace Ekul {
    class PhysicsObject {
        public:
        PhysicsObject();
        PhysicsObject(int x, int y, int width, int height, float angle);

        PhysicsObject(const PhysicsObject&) = default;
        
        // Modifying Velocity:
        void changeVelocity(float x, float y);
        void setXVelocity(float x);
        void setYVelocity(float y);

        // Get Velocity:
        float getXVelocity();
        float getYVelocity();

        void applyVelocity();
        
        // Get center point:
        SDL_Point getCenterPos();

        // Change PhysicsObject position:
        void setCenterPos(int x, int y);
        void setCenterYPos(int y);
        void setCenterXPos(int x);
        void moveCenterPos(int x_change, int y_change);

        // Rotate Object:
        void rotateAngle(float degrees);

        // Get Width, Height, & Angle:
        int getWidth();
        int getHeight();
        float getAngle();

        // Set Width, Height, & Angle:
        void setWidth(int width);
        void setHeight(int height);
        void setAngle(float angle);


        private:
        SDL_Point mCenter;

        int mWidth;
        int mHeight;
        float mAngle;

        float mX_vel;
        float mY_vel;
    };
}

#endif