#ifndef FRUITITEM_H
#define FRUITITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

// Representa una fruta recolectable dentro del juego.

class FruitItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    FruitItem(qreal x, qreal y);

private:
    QPixmap fruitPixmap;  // Imagen de la fruta
};

#endif // FRUITITEM_H
