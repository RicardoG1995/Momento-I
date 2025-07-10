#ifndef TIGERITEM_H
#define TIGERITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

// Clase que representa al enemigo tigre con movimiento oscilatorio (senoidal)
class TigerItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    TigerItem();  // Constructor que inicializa el movimiento
    void moveOscillate(); // Movimiento en onda senoidal

private:
    QPixmap normalPixmap;      // Imagen normal del tigre
    QPixmap attackPixmap;      // (No usada aún, pero disponible para ataques)
    QTimer* moveTimer;         // Timer que actualiza su movimiento
    int direction;             // Dirección horizontal (opcional para más lógica)
    qreal amplitude;           // Amplitud de oscilación (cuánto se mueve a los lados)
    qreal baseX;               // Posición base (centro) del movimiento
};

#endif // TIGERITEM_H
