#include "GameObject.h"

using namespace Ekul;

GameObject::GameObject()
{
    mPhysicsObject = new PhysicsObject(0, 0, 100, 200, 0.0);
    mPhysicsEngine = nullptr;
    mTexture = Texture();
}

GameObject::GameObject(PhysicsEngine* physicsEngine)
{
    mPhysicsObject = physicsEngine->newPhysicsObject(PhysicsObject(0, 0, 100, 200, 0.0));
    mPhysicsEngine = physicsEngine;
    mTexture = Texture();
}

// Copy Constructor
GameObject::GameObject(const GameObject& other)
{
    mPhysicsObject = new PhysicsObject(*other.mPhysicsObject);
    mPhysicsEngine = other.mPhysicsEngine;
    mTexture = other.mTexture;
}

// Move Constructor
GameObject::GameObject(GameObject&& other) noexcept
{
    mPhysicsObject = other.mPhysicsObject;
    mPhysicsEngine = other.mPhysicsEngine;
    other.mPhysicsObject = nullptr;

    mTexture = std::move(other.mTexture);
}

GameObject::~GameObject()
{
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

bool GameObject::loadImageFromFile(SDL_Renderer* renderer, TextureManager* textureManager, std::string path, SDL_Color keyColor, bool colorKeyFlag)
{
    // Load the image:
    bool success = mTexture.loadFromFile(renderer, textureManager, path, keyColor, colorKeyFlag);

    // Keep width and height the same between texture and physics object:
    mPhysicsObject->setHeight(mTexture.getHeight());
    mPhysicsObject->setHeight(mTexture.getWidth());

    // return success flag:
    return success;

}

void GameObject::setTextureClip(SDL_Rect clip)
{
    mTexture.setClip(clip);
}

void GameObject::free()
{
    if (mPhysicsEngine == nullptr)
    {
        delete mPhysicsObject;
        mPhysicsObject = nullptr;
    }
    else
    {
        mPhysicsEngine->deletePhysicsObject(mPhysicsObject);
        delete mPhysicsObject;
        mPhysicsObject = nullptr;
    }

    mTexture.free();
}