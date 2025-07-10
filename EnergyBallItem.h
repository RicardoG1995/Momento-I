#ifndef ENERGYBALLITEM_H
#define ENERGYBALLITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>

class EnergyBallItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    EnergyBallItem(qreal startX, qreal startY, qreal angleDeg, qreal speed);

protected:
    void advance(int phase) override;

private:
    qreal vx;       // Velocidad horizontal
    qreal vy;       // Velocidad vertical
    qreal gravity;  // Aceleración gravitacional
};

#endif // ENERGYBALLITEM_H
