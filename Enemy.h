#ifndef ENEMY_H
#define ENEMY_H

#include "Vector2D.h"
#include <string>

// Clase base lógica para un enemigo
class Enemy {
public:
    std::string type;  // Tipo de enemigo
    Vector2D position; // Posición lógica
    std::string behavior; // Comportamiento

    void act(); // Acción principal según comportamiento
    void attackPlayer(); // Lógica para atacar al jugador
};

#endif // ENEMY_H

