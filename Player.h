#ifndef PLAYER_H
#define PLAYER_H

#include "Vector2D.h"
#include <string>

class Player {
public:
    std::string name;
    Vector2D position;
    Vector2D velocity;
    int health;

    void move();
    void attack();
    void collectItem();
};

#endif // PLAYER_H



