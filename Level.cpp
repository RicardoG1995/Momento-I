#include "Level.h"
#include <iostream>
using namespace std;

//Cargara el contenido lógico del nivel.
void Level::loadLevel() {
    std::cout << "Cargando nivel " << levelNumber << ": " << description << "\n";

    for (auto& obj : objectives) {
        obj.check();
    }
    for (auto& phys : physics) {
        phys.simulate();
    }
}

//Verificara si todos los objetivos del nivel están completados.
bool Level::checkCompletion() {
    for (const auto& obj : objectives) {
        if (!obj.completed) {
            return false;
        }
    }
    return true;
}
