#ifndef EKUL_PHYSICS_ENGINE_H
#define EKUL_PHYSICS_ENGINE_H

// std
#include <vector>

// My Stuff
#include "PhysicsObject.h"

namespace Ekul {

    class Contract {
        public:
        Contract(PhysicsObject* physicsObject1, PhysicsObject* physicsObject2);

        private:
        PhysicsObject* mPhysicsObject1;
        PhysicsObject* mPhysicsObject2;
    };

    class PhysicsEngine {
        public:
        
        // Default Constructor
        PhysicsEngine();
        
        // Nice Constructor
        PhysicsEngine(float gravity);

        PhysicsObject* newPhysicsObject(PhysicsObject physicsObject);

        void applyVelocities();

        // TODO: std::vector<Contract> createContracts();

        // TODO: bool resolveContracts();

        private:

        std::vector<PhysicsObject> mPhysicsObjects;

        float mGravity;
    };
}

#endif