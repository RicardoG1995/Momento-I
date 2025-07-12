#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "PhysicsEngine.h"

// Controlador central del juego
class Game {
public:
    int currentLevel; // Nivel actual
    Player player;  // Jugador
    std::vector<Enemy> enemies; // Enemigos en el nivel
    PhysicsEngine physicsEngine; // Motor físico

    void startGame();     // Inicia el juego
    void nextLevel();     // Pasa al siguiente nivel
    void update();        // Actualiza la lógica del juego
};

#endif // GAME_H 
