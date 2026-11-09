#include "PhysicsEngine.h"

using namespace Ekul;

PhysicsEngine::PhysicsEngine()
{
    mGravity = 0;
    mLowerBound = std::numeric_limits<int>::max();
}

PhysicsObject* PhysicsEngine::newPhysicsObject(PhysicsObject physicsObject)
{
    mPhysicsObjects.push_back(new PhysicsObject(physicsObject));

    return mPhysicsObjects[mPhysicsObjects.size() - 1];
}

PhysicsEngine::~PhysicsEngine()
{
    free();
}

bool PhysicsEngine::deletePhysicsObject(PhysicsObject* physicsObject)
{
    printf("Delete Physics Object\n");
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        if (mPhysicsObjects[i] == physicsObject)
        {
            std::swap(mPhysicsObjects[i], mPhysicsObjects.back());
            mPhysicsObjects.pop_back();
            return true;
        }
    }
    return false;
}

void PhysicsEngine::applyVelocities()
{
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        mPhysicsObjects[i]->changeVelocity(0, mGravity);

        mPhysicsObjects[i]->applyVelocity();

        if (mPhysicsObjects[i]->getCenterPos().y + mPhysicsObjects[i]->getHeight() / 2 > mLowerBound)
        {
            mPhysicsObjects[i]->setYVelocity(0);
        }
    }
}

// std::vector<Contract> PhysicsEngine::createContracts()
// {

// }

// bool PhysicsEngine::resolveContracts()
// {

// }

void PhysicsEngine::setGravity(float gravity)
{
    mGravity = gravity;
}

float PhysicsEngine::getGravity()
{
    return mGravity;
}

void PhysicsEngine::setLowerBound(int lowerBound)
{
    mLowerBound = lowerBound;
}

int PhysicsEngine::getLowerBound()
{
    return mLowerBound;
}

void PhysicsEngine::free()
{
    // Loop through physics objects and free them:
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        delete mPhysicsObjects[i];
        mPhysicsObjects[i] = nullptr;
    }
}