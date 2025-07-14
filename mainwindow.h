#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <vector>
#include <QMediaPlayer>  // Añadir Sonido

#include "Game.h"
#include "Level.h"
#include "PlayerItem.h"
#include "FruitItem.h"
#include "TigerItem.h"
#include "EnergyBallItem.h" // Bolas de energía

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void defeatTiger();

private slots:
    void updateGame();                // Lógica del juego
    void updateLevel1Timer();         // Temporizador nivel 1
    void spawnLevel3Bullets();        // Balas enemigas nivel 3
    void addBulletToList(EnergyBallItem* ball);


private:
    Ui::MainWindow *ui;
    Game game;
    int currentLevelIndex;
    QTimer* balaTimer = nullptr;

    // Escena gráfica
    QGraphicsScene* scene;
    PlayerItem* player;
    TigerItem* tiger;
    QGraphicsPixmapItem* bulma = nullptr;
    QGraphicsPixmapItem* dragonBall = nullptr;
    QGraphicsPixmapItem* bulmaNormal = nullptr;  // Bulma en estado "necesita rescate"
    QGraphicsPixmapItem* bulmaSalvada = nullptr; // Bulma en estado "rescatada"
    bool bulmaRescatada = false;                 // Bandera de estado

    // Botones del menú principal
    QPushButton* playButton = nullptr;
    QPushButton* exitButton = nullptr;

    //Sonido
    QMediaPlayer* fruitSound;
    QMediaPlayer* shootSound;

    // Elementos dinámicos
    QList<FruitItem*> fruits;
    QList<EnergyBallItem*> bullets;
    QList<QGraphicsPixmapItem*> balasEnemigasNivel2;
    QList<QGraphicsPixmapItem*> enemyBullets;

    // Temporizadores
    QTimer* gameTimer = nullptr;
    QTimer* level1Timer = nullptr;
    QTimer* bulletSpawnerTimer = nullptr;

    // UI en escena
    QGraphicsTextItem* timeText = nullptr;
    QGraphicsTextItem* fruitCounterText = nullptr;
    QGraphicsTextItem* bulletCounterText = nullptr;

    // Estado del juego
    int timeRemaining = 30;
    int fruitsCollected = 0;
    int bulletsFired = 5;
    bool tigerDefeated = false;

    // Lógica y configuración
    void setupLevels();
    void startLevel(int index);
    void showMainMenu();
    void clearScene();

    void setupLevel1();
    void setupLevel2();
    void setupLevel3();

    void checkCollisions();
    void playFruitSound();
    void playShootSound();


    void keyPressEvent(QKeyEvent* event) override;
};

#endif // MAINWINDOW_H
