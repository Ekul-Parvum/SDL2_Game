#include "./PhysicsObject.h"

using namespace Ekul;

PhysicsObject::PhysicsObject(int x, int y, int width, int height, float angle)
{
    mCenter = {x, y};

    mWidth = width;
    mHeight = height;
    mAngle = angle;

    mX_vel = 0;
    mY_vel = 0;
}

void PhysicsObject::changeVelocity(float x, float y)
{
    mX_vel += x;
    mY_vel += y;
}

void PhysicsObject::setXVelocity(float x)
{
    mX_vel = x;
}

void PhysicsObject::setYVelocity(float y)
{
    mY_vel = y;
}

float PhysicsObject::getXVelocity() 
{
    return mX_vel;
}

float PhysicsObject::getYVelocity() 
{
    return mY_vel;
}

SDL_Point PhysicsObject::getCenterPos()
{
    return mCenter;
}

void PhysicsObject::setCenterPos(int x, int y)
{
    mCenter = {x, y};
}

void PhysicsObject::moveCenterPos(int x_change, int y_change)
{
    mCenter.x += x_change;
    mCenter.y += y_change;
}

void PhysicsObject::rotateAngle(float degrees)
{
    mAngle += degrees;

    while (mAngle > 360)
    {
        mAngle -= 360;
    }
}

int PhysicsObject::getWidth()
{
    return mWidth;
}

int PhysicsObject::getHeight()
{
    return mHeight;
}

float PhysicsObject::getAngle()
{
    return mAngle;
}
