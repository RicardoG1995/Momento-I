#include "Game.h"
#include <iostream>

//Inicia el juego (nivel 1)
void Game::startGame() {
    currentLevel = 1;
    std::cout << "Juego iniciado. Nivel: " << currentLevel << "\n";
}
//Avanza al siguiente nivel.
void Game::nextLevel() {
    currentLevel++;
    std::cout << "Avanzando al nivel: " << currentLevel << "\n";
}

//Lógica principal del juego en ejecución.
void Game::update() {
    physicsEngine.applyPhysics(&player); // Aplica físicas al jugador
    for (Enemy& enemy : enemies) {
        enemy.act();
    }
}
