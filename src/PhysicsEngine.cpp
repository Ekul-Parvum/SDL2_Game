#include "PhysicsEngine.h"
#include "Global.h"

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
    // Loop through physicsObjects, and apply velocities to them:
    for (int i = 0; i < (int)mPhysicsObjects.size(); i++)
    {
        mPhysicsObjects[i]->changeVelocity(0, mGravity);

        mPhysicsObjects[i]->applyVelocity();
    }

    // Create and resolve contracts:
    std::vector<Contract> contracts = createContracts();
    resolveContracts(contracts);
}

/// @brief Tests if two physicsObjects are colliding - But assumes they are both right side up/at angle 0
/// @param physicsObject1 
/// @param physicsObject2 
/// @return Returns true if they are colliding, false otherwise
bool PhysicsEngine::isCollisionNoAngle(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2)
{
    // TODO: Modify this to also consider the angle of the objects

    Point_f     pos1    = physicsObject1->getCenterPos();
    int         width1  = physicsObject1->getWidth();
    int         height1 = physicsObject1->getHeight();

    Point_f     pos2    = physicsObject2->getCenterPos();
    int         width2  = physicsObject2->getWidth();
    int         height2 = physicsObject2->getHeight();

    int obj1_top    = pos1.y - height1 / 2.0f;
    int obj1_bottom = pos1.y + height1 / 2.0f;
    int obj1_right  = pos1.x + width1 / 2.0f;
    int obj1_left   = pos1.x - width1 / 2.0f;
    
    int obj2_top    = pos2.y - height2 / 2.0f;
    int obj2_bottom = pos2.y + height2 / 2.0f;
    int obj2_right  = pos2.x + width2 / 2.0f;
    int obj2_left   = pos2.x - width2 / 2.0f;

    if (obj1_left >= obj2_right ||
        obj1_right <= obj2_left ||
        obj1_top >= obj2_bottom ||
        obj1_bottom <= obj2_top)
    {
        return false;
    }
    else
    {
        printf("COLLISION NO ANGLE\n");
        return true;
    }
}

/// @brief Tests if two physicsObjects are colliding
///
///        - I have documentation/notes on this algorithm and math in my black notebook, pg57-59
/// @param physicsObject1 
/// @param physicsObject2 
/// @return Returns true if they are colliding, false otherwise
bool PhysicsEngine::isCollisionWithAngle(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2)
{
    Point_f pos1 = physicsObject1->getCenterPos();
    Point_f pos2 = physicsObject2->getCenterPos();

    float halfWidth1  = physicsObject1->getWidth() / 2.0f;
    float halfHeight1 = physicsObject1->getHeight() / 2.0f;

    float halfWidth2  = physicsObject2->getWidth() / 2.0f;
    float halfHeight2 = physicsObject2->getHeight() / 2.0f;

    // Convert angles to radians
    float angle1 = physicsObject1->getAngle() * Constants::PI / 180.0f;
    float angle2 = physicsObject2->getAngle() * Constants::PI / 180.0f;

    // Local axes for each rectangle
    Point_f axes[4] = {
        { cos(angle1), sin(angle1) },
        { -sin(angle1), cos(angle1) },
        { cos(angle2), sin(angle2) },
        { -sin(angle2), cos(angle2) }
    };

    // Vector from object 1 to object 2
    Point_f centerDiff = {
        pos2.x - pos1.x,
        pos2.y - pos1.y
    };

    // Check overlap on each axis
    for (int i = 0; i < 4; i++)
    {
        Point_f axis = axes[i];

        // Project center distance onto axis
        float distance = fabs(
            centerDiff.x * axis.x +
            centerDiff.y * axis.y
        );

        // Calculate projection radius of rectangle 1
        float radius1 =
            halfWidth1 * fabs(cos(angle1) * axis.x + sin(angle1) * axis.y) +
            halfHeight1 * fabs(-sin(angle1) * axis.x + cos(angle1) * axis.y);

        // Calculate projection radius of rectangle 2
        float radius2 =
            halfWidth2 * fabs(cos(angle2) * axis.x + sin(angle2) * axis.y) +
            halfHeight2 * fabs(-sin(angle2) * axis.x + cos(angle2) * axis.y);

        // No overlap means no collision
        if (distance >= radius1 + radius2)
            return false;
    }

    printf("COLLISION WITH ANGLE\n");
    return true;
}

/// @brief Tests if the given physicsObject is outside of physicsEngine's bounds
/// @param physicsObject 
/// @return Returns true if it is outside of bounds, false otherwise
bool PhysicsEngine::isCollisionWithBound(PhysicsObject* physicsObject)
{
    Point_f     pos     = physicsObject->getCenterPos();
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
            // Create bound contract:
            contracts.push_back(Contract(mPhysicsObjects[i]));
        }

        // Loop through all the objects that haven't had all their contracts created:
        // Which is just all the objects after i:
        for (int j = i + 1; j < (int)mPhysicsObjects.size(); j++)
        {
            isCollisionWithAngle(mPhysicsObjects[i], mPhysicsObjects[j]);

            // If there is a collision between the i and j physicsObjects, create a contract between them
            if (isCollisionNoAngle(mPhysicsObjects[i], mPhysicsObjects[j]))
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
            Point_f pos = physicsObject1->getCenterPos();
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
            // TODO: Modify this to work on physicsObjects that can be at an angle.

            // Get the relevant info on the first physicsObject:
            Point_f pos1    = contracts[i].mPhysicsObject1->getCenterPos();
            int height1     = contracts[i].mPhysicsObject1->getHeight();
            int width1      = contracts[i].mPhysicsObject1->getWidth();
            
            // And the second:
            Point_f pos2    = contracts[i].mPhysicsObject2->getCenterPos();
            int height2     = contracts[i].mPhysicsObject2->getHeight();
            int width2      = contracts[i].mPhysicsObject2->getWidth();

            float overlapX = (width1 + width2) / 2.0f - abs(pos1.x - pos2.x);
            float overlapY = (height1 + height2) / 2.0f - abs(pos1.y - pos2.y);

            Point_f movement = {0, 0};

            if (overlapX < overlapY)
            {
                movement.x = (pos1.x < pos2.x) ? -overlapX / 2.0 : overlapX / 2.0;
                contracts[i].mPhysicsObject1->setXVelocity(0);
                contracts[i].mPhysicsObject2->setXVelocity(0);
            }
            else
            {
                movement.y = (pos1.y < pos2.y) ? -overlapY / 2.0 : overlapY / 2.0;
                contracts[i].mPhysicsObject1->setYVelocity(0);
                contracts[i].mPhysicsObject2->setYVelocity(0);
            }

            // if ((pos1.x < pos2.x && pos1.x + width1 > pos2.x + width2) || // If obj1's left & right bounds surround obj2
            //     (pos2.x < pos1.x && pos2.x + width2 > pos1.x + width1))   // If obj2's left & right bounds surround obj1
            // {
            //     movement.x = 0;
            // }

            // if ((pos1.y < pos2.y && pos1.y + height1 > pos2.y + height2) || // If obj1's top & bottom bounds surround obj2
            //     (pos2.y < pos1.y && pos2.y + height2 > pos1.y + height1))   // If obj2's top & bottom bounds surround obj1
            // {
            //     movement.y = 0;
            // }

            // Move the physicsObjects equaly along that normal:
            contracts[i].mPhysicsObject1->moveCenterPos(movement.x, movement.y);
            contracts[i].mPhysicsObject2->moveCenterPos(-movement.x, -movement.y);
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

