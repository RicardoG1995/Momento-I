#include "EnergyBallItem.h"
#include "TigerItem.h"
#include <QtMath>
#include <QGraphicsScene>

EnergyBallItem::EnergyBallItem(qreal startX, qreal startY, qreal angleDeg, qreal speed)
    : gravity(0.8)
{
    QPixmap pix(":/Img/Elementos/Bala.png");
    setPixmap(pix);
    setPos(startX, startY);

    // Convertir ángulo a radianes y calcular velocidades iniciales
    qreal angleRad = qDegreesToRadians(angleDeg);
    vx = speed * qCos(angleRad);
    vy = -speed * qSin(angleRad); // Y es hacia abajo en Qt

    setZValue(2);
}

// Movimiento parabólico + detección de colisiones
void EnergyBallItem::advance(int phase) {
    if (!phase || !scene()) return;

    // Movimiento parabólico
    setX(x() + vx);
    vy += gravity;
    setY(y() + vy);

    // Revisar colisión con el tigre
    QList<QGraphicsItem*> colliding = collidingItems();
    for (QGraphicsItem* item : colliding) {
        TigerItem* tiger = dynamic_cast<TigerItem*>(item);
        if (tiger && tiger->isAliveState()) {
            tiger->receiveHit();            //aplicar golpe
            scene()->removeItem(this);      // Eliminar la bola
            deleteLater();
            return;
        }
    }

    // Eliminar si se sale del mapa
    if (x() > 800 || y() > 600) {
        if (scene()) {
            scene()->removeItem(this);
        }
    }
}
