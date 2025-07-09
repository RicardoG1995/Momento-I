#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

// Clase que representa gráficamente al jugador (Goku) y su comportamiento
class PlayerItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    PlayerItem();

    // Métodos de movimiento
    void moveLeft();
    void moveRight();
    void jump();
    void attack();
    void applyGravity();
    void setOnGround(bool onGround);

protected:
    void advance(int phase) override; // Llamado por QGraphicsScene::advance()

private:
    QPixmap standPixmap, jumpPixmap, attackPixmap; // Sprites de Goku
    qreal velocityY;       // Velocidad vertical para saltos y gravedad
    bool jumping;          // Indica si está en el aire
    bool onGround;         // Indica si está en el suelo
    QTimer* animationTimer;
};

#endif // PLAYERITEM_H
