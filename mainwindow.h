#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsTextItem>
#include <vector>

#include "Game.h"
#include "Level.h"
#include "PlayerItem.h"
#include "FruitItem.h"
#include "TigerItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playButton_clicked(); // Maneja el botón "Jugar"
    void on_exitButton_clicked(); // Maneja el botón "Salir"

private:
    // UI y lógica de juego
    Ui::MainWindow *ui;
    Game game;
    std::vector<Level> levels;
    int currentLevelIndex;

    // Escena gráfica
    QGraphicsScene* scene;
    PlayerItem* player;
    TigerItem* tiger;
    QList<FruitItem*> fruits;

    // Nivel actual
    int currentLevel = 1;

    // Elementos especiales
    QGraphicsPixmapItem* bulma = nullptr;
    QList<QGraphicsPixmapItem*> balas;
    QTimer* balaTimer = nullptr;

    // Tiempo para el nivel 1
    QTimer* level1Timer = nullptr;
    QGraphicsTextItem* timeText = nullptr;
    int timeRemaining = 30;

    // Funciones de configuración
    void setupLevels();               // Inicializa niveles
    void startLevel(int index);       // Inicia nivel por índice
    void showLevelInfo(int index);    // Muestra diálogo informativo

    // Configuración específica de niveles
    void setupLevel1(); // Nivel con tigre y oscilación
    void setupLevel2(); // Nivel con Bulma
    void setupLevel3(); // Nivel con balas y física

    void keyPressEvent(QKeyEvent* event) override; // Teclado
    void updateLevel1Timer(); // Temporizador del nivel 1
};

#endif // MAINWINDOW_H
