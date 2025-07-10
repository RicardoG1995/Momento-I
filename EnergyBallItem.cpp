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
    if (!phase) return;

    // Actualizar posición
    setX(x() + vx);
    vy += gravity;
    setY(y() + vy);

    // Revisar colisión con el tigre
    QList<QGraphicsItem*> colliding = collidingItems();
    for (QGraphicsItem* item : colliding) {
        TigerItem* tiger = dynamic_cast<TigerItem*>(item);
        if (tiger) {
            scene()->removeItem(tiger); // Elimina al tigre
            delete tiger;
            scene()->removeItem(this); // Elimina la bola también
            delete this;
            return;
        }
    }

    // Eliminar si se sale del mapa
    if (x() > 800 || y() > 600) {
        scene()->removeItem(this);
        delete this;
    }
}
