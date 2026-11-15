#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

// SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace Ekul {
    struct Point_f {
        float x, y;
    };

    class PhysicsObject {
        public:
        PhysicsObject();
        PhysicsObject(float x, float y, int width, int height, float angle);

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
        Point_f getCenterPos();

        // Change PhysicsObject position:
        void setCenterPos(float x, float y);
        void setCenterYPos(float y);
        void setCenterXPos(float x);
        void moveCenterPos(float x_change, float y_change);

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
        Point_f mCenter;

        int mWidth;
        int mHeight;
        float mAngle;

        float mX_vel;
        float mY_vel;
    };
}

#endif