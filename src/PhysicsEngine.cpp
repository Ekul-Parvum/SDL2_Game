#include "PhysicsEngine.h"

using namespace Ekul;

float getDistance(SDL_Point point1, SDL_Point point2);

/// @brief Creates a contract between two physicsObjects
/// @param physicsObject1 
/// @param physicsObject2 
Contract::Contract(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2)
{
    mPhysicsObject1 = physicsObject1;
    mPhysicsObject2 = physicsObject2;

    mIsBoundContract = false;
}

/// @brief Creates a boundContract - A contract with one phpysicsObject which is colliding with one of the physicsEngine's bounds
/// @param physicsObject1 
Contract::Contract(PhysicsObject* physicsObject1)
{
    mPhysicsObject1 = physicsObject1;
    mPhysicsObject2 = nullptr;
    
    mIsBoundContract = true;
}

/// @brief PhysicsEngine Constructor
PhysicsEngine::PhysicsEngine()
{
    mGravity = 0;

    // Set boundries:
    mLowerBound = std::numeric_limits<int>::max();
    mUpperBound = std::numeric_limits<int>::min();
    mRightBound = std::numeric_limits<int>::max();
    mLeftBound = std::numeric_limits<int>::min();
}

/// @brief Creates a new physicsObject, and stores a pointer to it in physics engine
/// @param physicsObject The new physicsObject will be a copy of this one
/// @return Returns a pointer to the new physcisObject
PhysicsObject* PhysicsEngine::newPhysicsObject(PhysicsObject physicsObject)
{
    mPhysicsObjects.push_back(new PhysicsObject(physicsObject));

    return mPhysicsObjects[mPhysicsObjects.size() - 1];
}

/// @brief PhysicsEngine destructor - just calls PhysicsEngine::free()
PhysicsEngine::~PhysicsEngine()
{
    free();
}

/// @brief Deletes the physicsObject at the given address if it is in physicsEngine
/// @param physicsObject A pointer to the physicsObject to be deleted
/// @return Returns true if it found the physicsObject in itself, and deleted it - If it didin't find it, it returns false and does nothing.
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

/// @brief Applies some velocities, like gravity, and then moves all the physicsObjects around based on their velocities
void PhysicsEngine::applyVelocities()
{
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        mPhysicsObjects[i]->changeVelocity(0, mGravity);

        mPhysicsObjects[i]->applyVelocity();

        // Create and resolve contracts:
        std::vector<Contract> contracts = createContracts();
        resolveContracts(contracts);
    }
}

/// @brief Tests if two physicsObjects are colliding
/// @param physicsObject1 
/// @param physicsObject2 
/// @return Returns true if they are colliding, false otherwise
bool PhysicsEngine::isCollision(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2)
{
    SDL_Point   pos1    = physicsObject1->getCenterPos();
    int         width1  = physicsObject1->getWidth();
    int         height1 = physicsObject1->getHeight();

    SDL_Point   pos2    = physicsObject2->getCenterPos();
    int         width2  = physicsObject2->getWidth();
    int         height2 = physicsObject2->getHeight();

    if (pos1.x < pos2.x + width2 &&
        pos1.x + width1 > pos2.x &&
        pos1.y < pos2.y + height2 &&
        pos1.y + height1 > pos2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// @brief Tests if the given physicsObject is outside of physicsEngine's bounds
/// @param physicsObject 
/// @return Returns true if it is outside of bounds, false otherwise
bool PhysicsEngine::isCollisionWithBound(PhysicsObject* physicsObject)
{
    SDL_Point   pos     = physicsObject->getCenterPos();
    int         width   = physicsObject->getWidth();
    int         height  = physicsObject->getHeight();

    if (pos.x < mRightBound ||
        pos.x + width > mLeftBound ||
        pos.y < mUpperBound ||
        pos.y + height > mLowerBound)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// @brief Creates contracts between all the physicsObjects that are colliding with eachother
/// @return Returns a vector of contracts between all the physicsObjects that are colliding with eachother
std::vector<Contract> PhysicsEngine::createContracts()
{
    std::vector<Contract> contracts;

    // Loop through all the physics Objects:
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        // If this object collides with one of the boundries, create a contract for that:
        if (isCollisionWithBound(mPhysicsObjects[i]))
        {
            // Create bond contract:
            contracts.push_back(Contract(mPhysicsObjects[i]));
        }

        // Loop through all the objects that haven't had all their contracts created:
        // Which is just all the objects after i:
        for (int j = i + 1; j < (int)mPhysicsObjects.size(); j++)
        {
            // If there is a collision between the i and j physicsObjects, create a contract between them
            if (isCollision(mPhysicsObjects[i], mPhysicsObjects[j]))
            {
                // Create a contract:
                contracts.push_back(Contract(mPhysicsObjects[i], mPhysicsObjects[j]));
            }
        }
    }

    return contracts;
}

/// @brief Moves physicsObjects around to resolve all the given contracts. Note that this may create new collisions.
/// @param contracts 
void PhysicsEngine::resolveContracts(std::vector<Contract> contracts)
{
    for (int i = 0; i < (int)contracts.size(); i++)
    {
        if (contracts[i].mIsBoundContract)
        {
            PhysicsObject* physicsObject1 = contracts[i].mPhysicsObject1;
            SDL_Point pos = physicsObject1->getCenterPos();
            int height = physicsObject1->getHeight();
            int width = physicsObject1->getWidth();

            // Resolve lower bound collision:
            if (pos.y + height / 2 > mLowerBound)
            {
                physicsObject1->setYVelocity(0);
                physicsObject1->setCenterYPos(mLowerBound - physicsObject1->getHeight() / 2);
            }
            // Resolve upper bound collision:
            if (pos.y - height / 2 < mUpperBound)
            {
                physicsObject1->setYVelocity(0);
                physicsObject1->setCenterYPos(mUpperBound + height / 2);
            }
            // Resolve left bound collision:
            if (pos.x - height / 2 < mLeftBound)
            {
                physicsObject1->setXVelocity(0);
                physicsObject1->setCenterXPos(mLeftBound + height / 2);
            }
            // Resolve right bound collision:
            if (pos.x + width / 2 > mRightBound)
            {
                physicsObject1->setXVelocity(0);
                physicsObject1->setCenterXPos(mRightBound - width / 2);
            }
        }
        else
        {
            // TODO: Add actual collisions between PhysicsObjects
        }
    }
}

/// @brief Frees all the physicsObjects in physicsEngine
void PhysicsEngine::free()
{
    // Loop through physics objects and free them:
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        delete mPhysicsObjects[i];
        mPhysicsObjects[i] = nullptr;
    }
}

#pragma region getters & Setters
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

void PhysicsEngine::setUpperBound(int upperBound)
{
    mUpperBound = upperBound;
}

int PhysicsEngine::getUpperBound()
{
    return mUpperBound;
}

void PhysicsEngine::setRightBound(int rightBound)
{
    mRightBound = rightBound;
}

int PhysicsEngine::getRightBound()
{
    return mRightBound;
}

void PhysicsEngine::setLeftBound(int leftBound)
{
    mLeftBound = leftBound;
}

int PhysicsEngine::getLeftBound()
{
    return mLeftBound;
}
#pragma endregion

float getDistance(SDL_Point point1, SDL_Point point2)
{
    return std::hypot(point1.x - point2.x, point1.y - point2.y);
}

