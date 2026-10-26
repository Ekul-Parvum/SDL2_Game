#include "GameObject.h"

using namespace Ekul;

GameObject::GameObject()
{
    mPhysicsObject = {
        10, //x
        10, //y
        100, //w
        200, //h
    };
}

#pragma region Getters & Setters
SDL_Rect* GameObject::getPhysicsObject()
{
    return &mPhysicsObject;
}

Ekul::Texture GameObject::getTexture()
{
    return mTexture;
}

#pragma endregion
