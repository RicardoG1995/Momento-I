#ifndef PHYSICSMODEL_H
#define PHYSICSMODEL_H

#include <string>

//Representa un modelo de física individual, con nombre y fórmula.
class PhysicsModel {
public:
    std::string name;
    std::string formula;

    void simulate();
};

#endif // PHYSICSMODEL_H 
