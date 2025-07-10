#include "TigerItem.h"
#include <QPixmap>
#include <QTimer>
#include <QtMath> // Para funciones trigonométricas

TigerItem::TigerItem() :
    direction(1), amplitude(50)
{
    // Cargar sprites
    normalPixmap = QPixmap(":/Img/Enemigos/Tigre.png");
    attackPixmap = QPixmap(":/Img/Enemigos/Tigre_Ataca.png");
    setPixmap(normalPixmap);

    // Guardar posición inicial X como referencia del movimiento
    baseX = x();

    // Crear e iniciar un temporizador para moverse automáticamente
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &TigerItem::moveOscillate);
    moveTimer->start(50); // cada 50 ms (20 FPS aprox)
}

// Movimiento oscilatorio tipo onda senoidal
void TigerItem::moveOscillate() {
    static qreal t = 0;
    t += 0.1; // Incremento del tiempo simulado
    setX(baseX + amplitude * qSin(t));
}
