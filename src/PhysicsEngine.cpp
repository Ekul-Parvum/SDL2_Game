#include "PhysicsEngine.h"

using namespace Ekul;

PhysicsEngine::PhysicsEngine()
{

}

PhysicsEngine::PhysicsEngine(float gravity)
{
    mGravity = gravity;
}

PhysicsObject* PhysicsEngine::newPhysicsObject(PhysicsObject physicsObject)
{
    mPhysicsObjects.push_back(physicsObject);

    return &mPhysicsObjects[mPhysicsObjects.size() - 1];
}

void PhysicsEngine::applyVelocities()
{
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        mPhysicsObjects[i].changeVelocity(0, mGravity);
    }
}

// std::vector<Contract> PhysicsEngine::createContracts()
// {

// }

// bool PhysicsEngine::resolveContracts()
// {

// }