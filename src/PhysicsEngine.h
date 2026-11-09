#ifndef EKUL_PHYSICS_ENGINE_H
#define EKUL_PHYSICS_ENGINE_H

// std
#include <vector>
#include <limits>
#include <cmath>

// My Stuff
#include "PhysicsObject.h"

namespace Ekul {

    class Contract {
        public:
        Contract(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2);
        Contract(PhysicsObject* physicsObject1);

        PhysicsObject* mPhysicsObject1;
        PhysicsObject* mPhysicsObject2;

        bool mIsBoundContract;
    };

    class PhysicsEngine {
        public:
        
        // Default Constructor
        PhysicsEngine();
        
        // Nice Constructor
        PhysicsEngine(float gravity);

        // Destructor
        ~PhysicsEngine();

        PhysicsObject* newPhysicsObject(PhysicsObject physicsObject);

        bool deletePhysicsObject(PhysicsObject* physicsObject);

        void applyVelocities();

        bool isCollision(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2);

        bool isCollisionWithBound(PhysicsObject* physicsObject);

        std::vector<Contract> createContracts();

        bool resolveContracts(std::vector<Contract> contracts);

        void setGravity(float gravity);
        float getGravity();

        void setLowerBound(int lowerBound);
        int getLowerBound();
        
        void setUpperBound(int lowerBound);
        int getUpperBound();

        void setRightBound(int lowerBound);
        int getRightBound();

        void setLeftBound(int lowerBound);
        int getLeftBound();

        void free();

        private:

        std::vector<PhysicsObject*> mPhysicsObjects;

        float mGravity;

        int mLowerBound;
        int mUpperBound;
        int mRightBound;
        int mLeftBound;
    };
}

#endif