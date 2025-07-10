//Bloque 1
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Level.h"
#include "EnergyBallItem.h" 
#include <QMessageBox>
#include <QKeyEvent>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Botones
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::on_playButton_clicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);

    // Ocultar vista de juego hasta iniciar
    ui->gameView->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

//Bloque 2
// Muestra información del nivel en un mensaje
void MainWindow::showLevelInfo(int index) {
    if (index >= 0 && static_cast<size_t>(index) < levels.size()) {
        QMessageBox::information(this,
                                 QString("Nivel %1").arg(levels[index].levelNumber),
                                 QString::fromStdString(levels[index].description));
    }
}

//Bloque 3: Comenzar un nivel
void MainWindow::startLevel(int index) {
    if (index >= 0 && static_cast<size_t>(index) < levels.size()) {
        currentLevelIndex = index;
        showLevelInfo(index);

        if (QMessageBox::question(this, "¿Completaste el nivel?",
                                  "¿Deseas avanzar al siguiente nivel?") == QMessageBox::Yes) {
            if (index + 1 < static_cast<int>(levels.size())) {
                startLevel(index + 1);
            } else {
                QMessageBox::information(this, "¡Felicidades!", "¡Has completado todos los niveles!");
            }
        }
    }
}

//Bloque 4: Botones de jugar y salir
// Inicia el juego
void MainWindow::on_playButton_clicked() {
    ui->playButton->hide();
    ui->exitButton->hide();
    ui->gameView->show();
    setupLevel1(); // Comienza en el nivel 1
}

// Sale del juego
void MainWindow::on_exitButton_clicked() {
    close();
}


//Bloque 5: setupLevel1() — Movimiento Oscilatorio Tigre
void MainWindow::setupLevel1() {
    currentLevel = 1;

    // Crear escena
    scene = new QGraphicsScene(this);
    ui->gameView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 480);
    scene->setBackgroundBrush(Qt::gray);

    // Fondo
    QPixmap fondoPixmap(":/Img/Mapas/1/Fondo.jpg");
    scene->addPixmap(fondoPixmap)->setZValue(-2);

    // Piso
    QPixmap pisoPixmap(":/Img/Mapas/1/Piso.jpg");
    QGraphicsPixmapItem* piso = scene->addPixmap(pisoPixmap);
    piso->setPos(0, 400);
    piso->setZValue(-1);

    // Goku (Jugador)
    player = new PlayerItem();
    player->setPos(100, 350);
    scene->addItem(player);

    // Fruta
    fruits.clear();
    FruitItem* fruta = new FruitItem(600, 350);
    fruits.append(fruta);
    scene->addItem(fruta);

    // Tigre (con movimiento oscilatorio)
    tiger = new TigerItem();
    tiger->setPos(750, 350);
    scene->addItem(tiger);

    // Contador de tiempo visual
    timeRemaining = 30;
    timeText = new QGraphicsTextItem(QString("Tiempo: %1").arg(timeRemaining));
    timeText->setDefaultTextColor(Qt::white);
    timeText->setFont(QFont("Arial", 16, QFont::Bold));
    timeText->setPos(10, 10);
    timeText->setZValue(10);
    scene->addItem(timeText);

    // Timer del tiempo del nivel
    level1Timer = new QTimer(this);
    connect(level1Timer, &QTimer::timeout, this, &MainWindow::updateLevel1Timer);
    level1Timer->start(1000);

    // Avance general de la escena
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(20);

    // Ataque automático del tigre hacia el jugador
    QTimer* tigerAttackTimer = new QTimer(this);
    connect(tigerAttackTimer, &QTimer::timeout, this, [this]() {
        if (!player || !tiger) return;
        if (tiger->x() > player->x()) tiger->setX(tiger->x() - 2);
        else if (tiger->x() < player->x()) tiger->setX(tiger->x() + 2);

        if (player->collidesWithItem(tiger)) {
            QMessageBox::warning(this, "¡Perdiste!", "El tigre te atrapó");
            qApp->exit();
        }
    });
    tigerAttackTimer->start(40);
}


//Bloque 6: keyPressEvent() — Movimiento y Disparo
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!player) return;

    switch (event->key()) {
    case Qt::Key_A: player->moveLeft(); break;
    case Qt::Key_D: player->moveRight(); break;
    case Qt::Key_W: player->jump(); break;
    case Qt::Key_X: player->attack(); break;

        // Disparo de energía (movimiento parabólico)
    case Qt::Key_Space: {
        EnergyBallItem* bola = new EnergyBallItem(player->x() + 30, player->y(), 30.0, 15.0);
        scene->addItem(bola);
        break;
    }
    }

    // Revisión de colisión con frutas
    for (auto f : fruits) {
        if (player->collidesWithItem(f)) {
            scene->removeItem(f);
            fruits.removeOne(f);
            delete f;

            if (currentLevel == 1) {
                if (level1Timer) level1Timer->stop();
                QTimer::singleShot(0, this, [this]() { setupLevel2(); });
                return;
            } else if (currentLevel == 2) {
                if (bulma) bulma->setPixmap(QPixmap(":/Img/Bulma/Bulma.png"));
                QMessageBox::information(this, "¡Salvaste a Bulma!", "¡Bulma es libre!");
                QTimer::singleShot(0, this, [this]() { setupLevel3(); });
                return;
            } else if (currentLevel == 3) {
                QMessageBox::information(this, "¡Ganaste!", "¡Has esquivado las balas y recogido la fruta!");
                qApp->exit();
                return;
            }
            break;
        }
    }
}


//Bloque 7: Temporizador Nivel 1 (updateLevel1Timer())
void MainWindow::updateLevel1Timer() {
    if (currentLevel != 1) return;

    timeRemaining--;
    if (timeText) {
        timeText->setPlainText(QString("Tiempo: %1").arg(timeRemaining));
        if (timeRemaining <= 10) timeText->setDefaultTextColor(Qt::red);
    }

    if (timeRemaining <= 0) {
        if (level1Timer) level1Timer->stop();
        QMessageBox::warning(this, "¡Tiempo agotado!", "No lograste tomar la fruta. ¡Perdiste!");
        qApp->exit();
    }
}

//Bloque 8: setupLevel2() – Nivel de rescate física directa
void MainWindow::setupLevel2() {
    currentLevel = 2;

    // Limpiar escena anterior
    if (scene) { delete scene; scene = nullptr; }
    player = nullptr;
    tiger = nullptr;
    bulma = nullptr;
    fruits.clear();

    // Crear nueva escena
    scene = new QGraphicsScene(this);
    ui->gameView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 480);
    scene->setBackgroundBrush(Qt::gray);

    // Fondo
    QPixmap fondoPixmap(":/Img/Mapas/1/Fondo.jpg");
    scene->addPixmap(fondoPixmap)->setZValue(-2);

    // Piso
    QPixmap pisoPixmap(":/Img/Mapas/1/Piso.jpg");
    QGraphicsPixmapItem* piso = scene->addPixmap(pisoPixmap);
    piso->setPos(0, 400);
    piso->setZValue(-1);

    // Jugador
    player = new PlayerItem();
    player->setPos(100, 350);
    scene->addItem(player);

    // Fruta
    FruitItem* fruta = new FruitItem(600, 350);
    fruits.append(fruta);
    scene->addItem(fruta);

    // Bulma
    bulma = new QGraphicsPixmapItem(QPixmap(":/Img/Bulma/Bulma_Salvar.png"));
    bulma->setPos(600, 290);
    scene->addItem(bulma);

    // Timer para detectar colisión entre jugador y fruta (luego se activa Bulma)
    QTimer* frutaBulmaTimer = new QTimer(this);
    connect(frutaBulmaTimer, &QTimer::timeout, this, [this, fruta, frutaBulmaTimer]() {
        if (player && fruta && player->collidesWithItem(fruta)) {
            QMessageBox::information(this, "¡Nivel completado!", "¡Has rescatado a Bulma!");
            frutaBulmaTimer->stop();
        }
    });
    frutaBulmaTimer->start(30);
}

//Bloque 9: setupLevel3() – Física de proyectiles (balas con trayectoria)
void MainWindow::setupLevel3() {
    currentLevel = 3;

    // Limpiar escena y objetos anteriores
    if (scene) { delete scene; scene = nullptr; }
    player = nullptr;
    bulma = nullptr;
    tiger = nullptr;
    fruits.clear();
    for (auto b : balas) delete b;
    balas.clear();
    if (balaTimer) { balaTimer->stop(); delete balaTimer; balaTimer = nullptr; }

    // Nueva escena
    scene = new QGraphicsScene(this);
    ui->gameView->setScene(scene);
    scene->setSceneRect(0, 0, 800, 480);
    scene->setBackgroundBrush(Qt::gray);

    // Fondo y piso
    QPixmap fondoPixmap(":/Img/Mapas/1/Fondo.jpg");
    scene->addPixmap(fondoPixmap)->setZValue(-2);
    QGraphicsPixmapItem* piso = scene->addPixmap(QPixmap(":/Img/Mapas/1/Piso.jpg"));
    piso->setPos(0, 400);
    piso->setZValue(-1);

    // Jugador
    player = new PlayerItem();
    player->setPos(100, 350);
    scene->addItem(player);

    // Fruta final
    FruitItem* fruta = new FruitItem(700, 350);
    fruits.append(fruta);
    scene->addItem(fruta);

    // Avance de escena
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start(20);

    // Timer de balas
    balaTimer = new QTimer(this);
    connect(balaTimer, &QTimer::timeout, this, [this]() {
        static int phase = 0;
        QPixmap balaPixmap(":/Img/Elementos/Bala.png");
        QGraphicsPixmapItem* bala = new QGraphicsPixmapItem(balaPixmap);
        bala->setZValue(1);

        if (phase < 3) {
            // Balas de arriba hacia abajo
            int x = 100 + rand() % 600;
            bala->setPos(x, 0);
        } else if (phase < 6) {
            // Balas de derecha a izquierda
            int y = 50 + rand() % 350;
            bala->setPos(800, y);
        }
        scene->addItem(bala);
        balas.append(bala);

        // Movimiento
        QTimer* moveTimer = new QTimer(this);
        connect(moveTimer, &QTimer::timeout, this, [this, bala, moveTimer]() {
            if (!bala || !scene) return;
            if (bala->x() > 0 && bala->y() < 480) {
                if (bala->x() == 800) bala->setX(bala->x() - 10); // Izquierda
                else bala->setY(bala->y() + 10);                  // Abajo
            }

            if (player && bala->collidesWithItem(player)) {
                QMessageBox::warning(this, "¡Perdiste!", "Te golpeó una bala");
                qApp->exit();
            }

            if (bala->x() < 0 || bala->y() > 480) {
                scene->removeItem(bala);
                balas.removeOne(bala);
                delete bala;
                moveTimer->stop();
                moveTimer->deleteLater();
            }
        });
        moveTimer->start(30);
        phase++;
        if (phase >= 6) balaTimer->stop();
    });
    balaTimer->start(1000); // Cada segundo

    // Colisión final con la fruta
    bool* frutaColisionActiva = new bool(false);
    QTimer::singleShot(1000, this, [frutaColisionActiva]() { *frutaColisionActiva = true; });

    QTimer* frutaTimer = new QTimer(this);
    connect(frutaTimer, &QTimer::timeout, this, [this, fruta, frutaTimer, frutaColisionActiva]() {
        if (*frutaColisionActiva && player && fruta && player->collidesWithItem(fruta)) {
            QMessageBox::information(this, "¡Ganaste!", "¡Has esquivado las balas y recogido la fruta!\n¡Juego terminado!");
            frutaTimer->stop();
            delete frutaColisionActiva;
            qApp->exit();
        }
    });
    frutaTimer->start(30);
}

