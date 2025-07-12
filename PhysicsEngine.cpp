#include "PhysicsEngine.h"
#include <iostream>
using namespace std;

//Aplica todos los modelos físicos disponibles al objeto
void PhysicsEngine::applyPhysics(void* entity) {
    cout << "[PhysicsEngine] Aplicando física a entidad...\n";
    for (auto& model : models) {
        model.simulate();
    }
}
