#ifndef TIGERITEM_H
#define TIGERITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

//Clase que representa al enemigo Tigre en el juego.

class TigerItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    TigerItem();

    // Movimiento y estado

    void moveOscillate();                   // Movimiento oscilante en forma de seno
    void setAlive(bool alive);             // Activa o desactiva al tigre
    void receiveHit();                     // Recibe un impacto (si llega a 5, desaparece)
    bool isAliveState() const { return isAlive; }      // Consulta si está vivo
    bool isAttackingState() const { return isAttacking; } // Consulta si está atacando

    // Ataque y configuración
    void initiateAttack();                 // Inicia ataque parabólico
    void setAttackParameters(qreal range, qreal height); // Configura rango y altura del ataque
    void setTargetPlayer(QGraphicsItem* player);        // Define el objetivo (Goku)

    int getHitsReceived() const { return hitsReceived; }

    // Posición de inicio
    QPointF startPos;
    void returnToStart();                  // Regresa al punto de partida
    void setBaseX(qreal x) { baseX = x; }

private:
    // Sprites
    QPixmap normalPixmap;
    QPixmap attackPixmap;

    // Animación de caminata
    QVector<QPixmap> walkLeftFrames;
    QVector<QPixmap> walkRightFrames;
    int currentFrame = 0;
    int animationSpeed = 5; // Velocidad de animación (frames por movimiento)
    int frameCounter = 0;
    bool movingRight = true;

    // Temporizadores
    QTimer* moveTimer;
    QTimer* attackTimer;

    // Estado del tigre
    qreal amplitude = 100;      // Amplitud del movimiento oscilatorio
    qreal baseX;               // Posición base en X
    bool isAlive = true;       // ¿Está vivo?
    int hitsReceived = 0;      // Contador de impactos
    bool isAttacking = false;  // ¿Está en modo ataque?

    // Parámetros del ataque
    qreal attackRange = 150;      // Distancia de ataque
    qreal jumpHeight = -100;      // Altura máxima del salto parabólico
    QGraphicsItem* targetPlayer = nullptr; // Goku u otro objetivo

};

#endif // TIGERITEM_H
