#include "TigerItem.h"
#include <QPixmap>
#include <QTimer>
#include <QtMath>             // Para qSin
#include <QGraphicsScene>
#include <QGraphicsTextItem>

// Constructor: inicializa sprites y movimiento oscilante
TigerItem::TigerItem()
    : amplitude(50), isAlive(true), hitsReceived(0), isAttacking(false)
{
    // Cargar sprites de animación
    walkLeftFrames.append(QPixmap(":/Img/Enemigos/Tigre_Camina1.png"));
    walkLeftFrames.append(QPixmap(":/Img/Enemigos/Tigre_Camina2.png"));
    walkLeftFrames.append(QPixmap(":/Img/Enemigos/Tigre.png")); // Frame neutral

    walkRightFrames.append(QPixmap(":/Img/Enemigos/Tigre_Camina1_Derecha.png"));
    walkRightFrames.append(QPixmap(":/Img/Enemigos/Tigre_Camina2_Derecha.png"));
    walkRightFrames.append(QPixmap(":/Img/Enemigos/Tigre_Derecha.png")); // Frame neutral

    normalPixmap = QPixmap(":/Img/Enemigos/Tigre.png");
    attackPixmap = QPixmap(":/Img/Enemigos/Tigre_Ataca.png");
    setPixmap(normalPixmap);

    baseX = x();
    startPos = pos();

    // Timer para movimiento oscilante
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &TigerItem::moveOscillate);
    moveTimer->start(50); // ~20 FPS
}

// Movimiento oscilante con onda seno
void TigerItem::moveOscillate() {
    if (!isAlive || isAttacking) return;

    static qreal t = 0;
    t += 0.1;

    // Determinar dirección
    bool wasMovingRight = movingRight;
    movingRight = (qSin(t) > 0);

    // Actualizar sprite según dirección
    if (movingRight != wasMovingRight) {
        currentFrame = 0; // Reiniciar animación al cambiar dirección
    }

    // Avanzar animación
    frameCounter++;
    if (frameCounter >= animationSpeed) {
        frameCounter = 0;
        currentFrame = (currentFrame + 1) % 2; // Solo usa los frames 0 y 1 para caminata

        if (movingRight) {
            setPixmap(walkRightFrames[currentFrame]);
        } else {
            setPixmap(walkLeftFrames[currentFrame]);
        }
    }

    // Movimiento físico
    qreal newX = baseX + amplitude * qSin(t);
    setX(newX);
}

// Establece si el tigre está vivo o muerto
void TigerItem::setAlive(bool alive) {
    isAlive = alive;

    if (!alive) {
        moveTimer->stop();
        hide();

        // Mensaje en pantalla
        if (scene()) {
            QGraphicsTextItem* msg = new QGraphicsTextItem("¡El camino está libre!");
            msg->setDefaultTextColor(Qt::yellow);
            msg->setFont(QFont("Arial", 16, QFont::Bold));
            msg->setPos(x(), y() - 40);
            scene()->addItem(msg);
        }
    }
}

// Recibe impacto. Si llega a 5, muere.
void TigerItem::receiveHit() {
    qDebug() << "Tigre que recibe el golpe (dentro de TigerItem):" << static_cast<void*>(this);
    qDebug() << "Recibiendo golpe...";
    hitsReceived++;
    qDebug() << "Hits acumulados:" << hitsReceived;
    if (hitsReceived >= 5) {
        qDebug() << "Emitiendo señal tigerShouldBeEliminated";
        emit tigerShouldBeEliminated();
    }

    // Mostrar sprite de daño temporalmente
    setPixmap(QPixmap(":/Img/Enemigos/Tigre_Herido.png"));
    QTimer::singleShot(200, this, [this]() {
        setPixmap(normalPixmap);
    });
}

// Permite definir el objetivo del ataque
void TigerItem::setTargetPlayer(QGraphicsItem* player) {
    targetPlayer = player;
}

// Configura distancia y altura del ataque
void TigerItem::setAttackParameters(qreal range, qreal height) {
    attackRange = range;
    jumpHeight = height;
}

// Inicia ataque parabólico hacia el objetivo
void TigerItem::initiateAttack() {
    if (isAttacking || !isAlive || !targetPlayer) return;

    isAttacking = true;
    setPixmap(attackPixmap);

    QPointF start = pos();
    QPointF target = targetPlayer->pos();
    qreal distance = target.x() - start.x();
    qreal height = jumpHeight;

    attackTimer = new QTimer(this);
    int frame = 0;

    connect(attackTimer, &QTimer::timeout, this, [=]() mutable {
        if (frame < 30) {
            qreal progress = frame / 30.0;
            qreal x = start.x() + distance * progress;
            qreal y = start.y() + height * (4 * progress * (1 - progress));
            setPos(x, y);
            frame++;
        } else {
            attackTimer->stop();
            attackTimer->deleteLater();
            returnToStart();
        }
    });

    attackTimer->start(16);
}

// Movimiento suave de regreso al punto inicial
void TigerItem::returnToStart() {
    QTimer* retreat = new QTimer(this);
    movingRight = (startPos.x() > x()); // Determinar dirección

    connect(retreat, &QTimer::timeout, this, [this, retreat]() {
        // Animación durante el retroceso
        frameCounter++;
        if (frameCounter >= animationSpeed) {
            frameCounter = 0;
            currentFrame = (currentFrame + 1) % 2;
            setPixmap(movingRight ? walkRightFrames[currentFrame] : walkLeftFrames[currentFrame]);
        }

        QPointF current = pos();
        QPointF delta = startPos - current;

        if (qAbs(delta.x()) < 1 && qAbs(delta.y()) < 1) {
            retreat->stop();
            delete retreat;
            isAttacking = false;
            setPixmap(movingRight ? walkRightFrames[2] : walkLeftFrames[2]); // Frame neutral
            setPos(startPos);
        } else {
            setPos(x() + delta.x() / 10, y() + delta.y() / 10);
        }
    });

    retreat->start(50);
}

