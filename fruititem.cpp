
#include "FruitItem.h"
#include <QPixmap>

// Constructor de la fruta. Establece su posición e imagen.
// x Posición horizontal
// y Posición vertical

FruitItem::FruitItem(qreal x, qreal y) {
    fruitPixmap = QPixmap(":/Img/Elementos/Fruta.png");
    setPixmap(fruitPixmap);
    setPos(x, y);
}
