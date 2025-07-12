#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include "PhysicsModel.h"

// Motor de físicas para manejar una lista de modelos físicos.
class PhysicsEngine {
public:
    std::vector<PhysicsModel> models;
    void applyPhysics(void* entity);
};

#endif // PHYSICSENGINE_H 
