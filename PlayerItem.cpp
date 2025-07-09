#include "PlayerItem.h"
#include <QPixmap>

PlayerItem::PlayerItem() :
    velocityY(0), jumping(false), onGround(true)
{
    // Cargar imágenes de sprites
    standPixmap = QPixmap(":/Img/Goku/Goku.png");
    jumpPixmap = QPixmap(":/Img/Goku/Goku_Saltar.png");
    attackPixmap = QPixmap(":/Img/Goku/Goku_Ataca.png");

    // Establecer sprite inicial
    setPixmap(standPixmap);

    // Habilitar interacción del teclado
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
}

// Mueve a Goku hacia la izquierda
void PlayerItem::moveLeft() {
    setX(x() - 10);
}

// Mueve a Goku hacia la derecha
void PlayerItem::moveRight() {
    setX(x() + 10);
}

// Salto inicial: establece la velocidad vertical hacia arriba
void PlayerItem::jump() {
    if (onGround) {
        velocityY = -18;  // salto hacia arriba
        jumping = true;
        onGround = false;
        setPixmap(jumpPixmap);
    }
}

// Cambia temporalmente a sprite de ataque
void PlayerItem::attack() {
    setPixmap(attackPixmap);
}

// Simula gravedad en el eje Y cuando está en el aire
void PlayerItem::applyGravity() {
    if (!onGround) {
        velocityY += 1.2; // gravedad (aceleración positiva)
        setY(y() + velocityY);

        // Si toca el suelo (nivel y = 350), lo reestablece
        if (y() >= 350) {
            setY(350);
            velocityY = 0;
            onGround = true;
            setPixmap(standPixmap);
        }
    }
}

// Permite forzar el estado de estar en el suelo
void PlayerItem::setOnGround(bool g) {
    onGround = g;
}

// Función automática de avance en la escena
void PlayerItem::advance(int phase) {
    if (!phase) return;
    applyGravity();
}
