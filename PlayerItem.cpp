#include "PlayerItem.h"
#include "TigerItem.h"
#include "EnergyBallItem.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

// Constructor: inicializa sprites, animaciones y estado físico del jugador
PlayerItem::PlayerItem() : QObject(), QGraphicsPixmapItem(), tiger(nullptr) {
    // Cargar imagen de espera
    standPixmap.load(":/Img/Goku/goku_stand.png");
    jumpPixmap.load(":/Img/Goku/goku_jump.png");
    attackPixmap.load(":/Img/Goku/Goku_Ataca.png");
    isAttacking = false;

    // Estado físico inicial
    onGround = true;
    velocityY = 0;

    // Animación de movimiento hacia la izquierda
    leftAnimationFrames.append(QPixmap(":/Img/Goku/goku_left.png"));
    leftAnimationFrames.append(QPixmap(":/Img/Goku/goku_left1.png"));
    leftAnimationFrames.append(QPixmap(":/Img/Goku/goku_left2.png"));
    leftAnimationFrames.append(QPixmap(":/Img/Goku/goku_left.png"));

    // Animación de movimiento hacia la derecha
    rightAnimationFrames.append(QPixmap(":/Img/Goku/goku_right.png"));
    rightAnimationFrames.append(QPixmap(":/Img/Goku/goku_right1.png"));
    rightAnimationFrames.append(QPixmap(":/Img/Goku/goku_right2.png"));
    rightAnimationFrames.append(QPixmap(":/Img/Goku/goku_right.png"));

    // Imagen de salto (ya cargada arriba, pero incluida por claridad)
    jumpPixmap.load(":/Img/Goku/goku_jump.png");

    // Estado visual y animación inicial
    setPixmap(standPixmap);
    leftAnimIndex = 0;
    rightAnimIndex = 0;
}
// // Función que define la caja de colisión del jugado

    QRectF PlayerItem::boundingRect() const {
    // Devuelve un rectángulo que define el área de colisión del jugador.
    // Asumimos que los sprites de Goku miden 60x90 píxeles.
    // ¡Ajusta estos valores si el tamaño de tus imágenes es diferente!
    return QRectF(0, 0, 90, 90);
}

// Asignación de referencia externa al tigre desde MainWindow
void PlayerItem::setTigerReference(TigerItem* tigerRef) {
    tiger = tigerRef;
}

// Movimiento hacia la izquierda con animación de ciclos
void PlayerItem::moveLeft() {
    leftAnimIndex++;
    if (leftAnimIndex >= leftAnimationFrames.size()) {
        leftAnimIndex = 0;
    }

    setPixmap(leftAnimationFrames[leftAnimIndex]);
    setPos(x() - 15, y());

    // Límite izquierdo de pantalla
    if (x() < 0) {
        setPos(0, y());
    }
}


void PlayerItem::shootEnergyBall() {
    if (!tiger || isAttacking || !onGround|| !scene()) return;

    isAttacking = true;
    setPixmap(attackPixmap);

    // Crear y lanzar bola de energía
    EnergyBallItem* ball = new EnergyBallItem(
        x() + (tiger->x() < x() ? -10 : 40),
        y() + 20,
        (tiger->x() < x() ? -165 : -15),
        20
        );

    scene()->addItem(ball);
    // Notifica a MainWindow sobre la nueva bala ===
    emit energyBallFired(ball);

    // Reproducir sonido de disparo (emitir señal para que MainWindow lo maneje)
    emit playShootSound();

    QTimer::singleShot(200, this, &PlayerItem::finishAttackAnimation);
}

// Movimiento hacia la derecha con animación de ciclos
void PlayerItem::moveRight() {
    // Verificar si el tigre está vivo y estamos cerca de él
    if (tiger && tiger->isAliveState() && x() > tiger->x() - 50) {
        // Animación estática cuando choca con el tigre
        setPixmap(standPixmap);
        return;
    }

    // Animación normal de movimiento
    rightAnimIndex++;
    if (rightAnimIndex >= rightAnimationFrames.size()) {
        rightAnimIndex = 0;
    }
    setPixmap(rightAnimationFrames[rightAnimIndex]);

    // Movimiento normal
    setPos(x() + 15, y());

    // Límite derecho de pantalla
    if (x() > 800 - pixmap().width()) {
        setPos(800 - pixmap().width(), y());
    }
}

// Acción de salto con cambio de sprite
void PlayerItem::jump() {
    if (onGround && !isAttacking) {
        onGround = false;
        velocityY = -20;
        setPixmap(jumpPixmap);
    }
}

void PlayerItem::finishAttackAnimation() {
    isAttacking = false;
    setPixmap(standPixmap);
}

// Lógica de física y proximidad con el tigre. Se ejecuta cada frame.
void PlayerItem::advance(int phase) {
    if (phase == 0) return;

    // Aplicar gravedad si el jugador está en el aire
    if (!onGround) {
        velocityY += 0.98;
        setPos(x(), y() + velocityY);

        // Detectar colisión con el suelo
        if (y() >= 500) {
            setY(500);
            onGround = true;
            velocityY = 0;
            setPixmap(standPixmap);
        }
    }

    // Detectar si el jugador está cerca del tigre y activar su comportamiento
    if (tiger && tiger->isAliveState() && qAbs(x() - tiger->x()) < 150 && !tiger->isAttackingState()) {
        tiger->initiateAttack();
    }
}
