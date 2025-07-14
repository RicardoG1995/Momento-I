#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QVector>
#include <QPixmap>
#include "TigerItem.h"
#include <QMediaPlayer>
#include <QAudioOutput>

// Declaraciones adelantadas para evitar errores de compilación
class TigerItem;
class EnergyBallItem;

//Clase que representa gráficamente al jugador (Goku) y su comportamiento físico y animado
class PlayerItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    PlayerItem(); // Constructor que carga sprites y estado inicial
    QRectF boundingRect() const override;

    //Métodos de movimiento del jugador
    void moveLeft();     // Mover a la izquierda con animación
    void moveRight();    // Mover a la derecha con animación
    void jump();         // Saltar con física
    void shootEnergyBall(); //método para disparar

    //Interacción con el tigre (u otro enemigo)
    void setTigerReference(TigerItem* tigerRef); // Asigna referencia externa al tigre


signals:    // Señal para notificar a MainWindow
    void energyBallFired(EnergyBallItem* ball);
    void playShootSound();

protected:
    // advance() se ejecuta periódicamente para aplicar gravedad y lógica como colisiones
    void advance(int phase) override;

private:
    // Sprites individuales para distintos estados
    QPixmap standPixmap;     // Quieto
    QPixmap jumpPixmap;      // En el aire
    QPixmap attackPixmap;    // sprite para ataque

    // Animaciones: lista de frames para caminar
    QVector<QPixmap> leftAnimationFrames;
    QVector<QPixmap> rightAnimationFrames;

    // Índices actuales de animación
    int leftAnimIndex;
    int rightAnimIndex;

    //Estado físico del jugador
    qreal velocityY;     // Velocidad vertical para gravedad
    bool onGround;       // ¿Está en el suelo?
    bool isAttacking;    // Nuevo estado para controlar animación de ataque

    // Referencia al tigre para detectar proximidad
    TigerItem* tiger = nullptr;
    QMediaPlayer* shootSound;
    QAudioOutput* shootAudioOutput;

private slots:
    void finishAttackAnimation(); //slot para terminar animación de ataque
};

#endif // PLAYERITEM_H
