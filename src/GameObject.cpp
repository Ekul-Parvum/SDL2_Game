#include "GameObject.h"

using namespace Ekul;

GameObject::GameObject()
{
    mPhysicsObject = new PhysicsObject(0, 0, 100, 200, 0.0);
    mTexture = Texture();
}

GameObject::GameObject(PhysicsEngine physicsEngine)
{
    mPhysicsObject = physicsEngine.newPhysicsObject(PhysicsObject(0, 0, 100, 200, 0.0));
    mTexture = Texture();
}

// Copy Constructor
GameObject::GameObject(const GameObject& other)
{
    mPhysicsObject = new PhysicsObject(*other.mPhysicsObject);
    mTexture = other.mTexture;
}

// Move Constructor
GameObject::GameObject(GameObject&& other) noexcept
{
    mPhysicsObject = other.mPhysicsObject;
    other.mPhysicsObject = nullptr;

    mTexture = std::move(other.mTexture);
}

GameObject::~GameObject()
{
    delete mPhysicsObject;
    free();
}

void GameObject::changeVelocity(float x, float y)
{
    mPhysicsObject->changeVelocity(x, y);
}

void GameObject::setXVelocity(float x)
{
    mPhysicsObject->setXVelocity(x);
}

void GameObject::setYVelocity(float y)
{
    mPhysicsObject->setYVelocity(y);
}

float GameObject::getXVelocity()
{
    return mPhysicsObject->getXVelocity();
}

float GameObject::getYVelocity()
{
    return mPhysicsObject->getYVelocity();
}

SDL_Point GameObject::getCenterPos()
{
    return mPhysicsObject->getCenterPos();
}

void GameObject::setCenterPos(int x, int y)
{
    mPhysicsObject->setCenterPos(x, y);
}

void GameObject::moveCenterPos(int x_change, int y_change)
{
    mPhysicsObject->moveCenterPos(x_change, y_change);
}

void GameObject::rotateAngle(float degrees)
{
    mPhysicsObject->rotateAngle(degrees);
}

void GameObject::setAngle(float degrees)
{
    mPhysicsObject->setAngle(degrees);
}

int GameObject::getHitboxWidth()
{
    return mPhysicsObject->getWidth();
}

int GameObject::getHitboxHeight()
{
    return mPhysicsObject->getHeight();
}

float GameObject::getHitboxAngle()
{
    return mPhysicsObject->getAngle();
}

void GameObject::setWidth(int width)
{
    mPhysicsObject->setWidth(width);
    mTexture.forceSetWidth(width);
}

void GameObject::setHeight(int height)
{
    mPhysicsObject->setHeight(height);
    mTexture.forceSetHeight(height);
}

void GameObject::render(SDL_Renderer* renderer)
{
    SDL_Point gameObjectPosition = mPhysicsObject->getCenterPos();
    SDL_Point rectPos = {gameObjectPosition.x - mTexture.getWidth() / 2, gameObjectPosition.y - mTexture.getHeight() / 2};

    mTexture.render(renderer, rectPos.x, rectPos.y, mPhysicsObject->getAngle());
}

bool GameObject::loadImageFromFile(SDL_Renderer* renderer, std::string path)
{
    return mTexture.loadFromFile(renderer, path);
}

void GameObject::setTextureClip(SDL_Rect clip)
{
    mTexture.setClip(clip);
}

void GameObject::free()
{
    mTexture.free();
}