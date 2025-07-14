#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QBrush>
#include <QPalette>
#include <QGraphicsOpacityEffect>  // Para efectos visuales
#include <QPropertyAnimation>
#include <QGraphicsScene>

//Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Inicializar sonidos
    fruitSound = new QMediaPlayer(this);
    fruitSound->setAudioOutput(new QAudioOutput(this));

    shootSound = new QMediaPlayer(this);
    shootSound->setAudioOutput(new QAudioOutput(this));
    // Configuración de la escena gráfica
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 798, 598);

    // Ocultar la vista de gráficos inicialmente
    ui->graphicsView->hide();

    // Timer principal del juego
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateGame);

    ui->graphicsView->show();
    showMainMenu();

}

//  destructor
MainWindow::~MainWindow() {
    delete ui;
}

// MODIFICACIÓN: Nueva función para la lógica principal del juego
void MainWindow::updateGame() {
    scene->advance();
    checkCollisions();
}

void MainWindow::startLevel(int index) {
    clearScene(); // Limpiar la escena antes de cargar un nivel
    currentLevelIndex = index;
    tigerDefeated = false; // Reiniciar estado del tigre

    switch (index) {
    case 1:
        setupLevel1();
        break;
    case 2:
        setupLevel2();
        break;
    default:
        // Regresar al menú si no hay más niveles
        showMainMenu();
        return;
    }
    gameTimer->start(16); // Iniciar el bucle de juego (aprox. 60 FPS)
}

// MODIFICACIÓN: Nueva función para limpiar la escena
void MainWindow::clearScene() {
    scene->clear();
    fruits.clear();
    // Limpiar balas de energía
    for (EnergyBallItem* bullet : bullets) {
        if (bullet->scene()) {
            scene->removeItem(bullet);
        }
        delete bullet;
    }
    bullets.clear();
    enemyBullets.clear();

    // Detener todos los timers para que no interfieran
    if (gameTimer->isActive()) gameTimer->stop();
    if (level1Timer && level1Timer->isActive()) level1Timer->stop();
    if (bulletSpawnerTimer && bulletSpawnerTimer->isActive()) bulletSpawnerTimer->stop();


    player = nullptr;
    tiger = nullptr;
    bulmaNormal = nullptr;
    dragonBall = nullptr;
    // Limpiar recursos de Bulma
    if (bulmaNormal) {
        scene->removeItem(bulmaNormal);
        delete bulmaNormal;
        bulmaNormal = nullptr;
    }
    if (bulmaSalvada) {
        scene->removeItem(bulmaSalvada);
        delete bulmaSalvada;
        bulmaSalvada = nullptr;
    }
    bulmaRescatada = false;
}


// MODIFICACIÓN: Nueva función para mostrar el menú

void MainWindow::showMainMenu() {
    scene->clear(); // Limpia la escena anterior

    // Fondo del menú
    QPixmap fondoMenu(":/Img/Mapas/1/Inicio.jpg");
    if (!fondoMenu.isNull()) {
        QGraphicsPixmapItem* fondoItem = scene->addPixmap(fondoMenu);
        fondoItem->setZValue(-1);
        scene->setSceneRect(0, 0, fondoMenu.width(), fondoMenu.height());
    }

    // Mostrar botones — como widgets independientes (NO agregarlos a la escena)
    playButton = new QPushButton("Play", this);
    exitButton = new QPushButton("Exit", this);

    playButton->setGeometry(300, 250, 200, 50);
    exitButton->setGeometry(300, 320, 200, 50);

    playButton->setStyleSheet("background-color: orange; font-size: 18px;");
    exitButton->setStyleSheet("background-color: crimson; font-size: 18px; color: white;");

    playButton->show();
    exitButton->show();

    // Conectar señales
    connect(playButton, &QPushButton::clicked, this, [this]() {
        // Ocultar botones al iniciar el juego
        playButton->hide();
        exitButton->hide();
        currentLevelIndex = 1;
        startLevel(currentLevelIndex);
    });

    connect(exitButton, &QPushButton::clicked, this, &QApplication::quit);
}


void MainWindow::setupLevel1() {
    // Jugador
    QPixmap fondo(":/Img/Mapas/1/Fondo.jpg");
    if (!fondo.isNull()) {
        QGraphicsPixmapItem* fondoItem = scene->addPixmap(fondo);
        fondoItem->setZValue(-1); // Detrás de todos los objetos
        scene->setSceneRect(0, 0, fondo.width(), fondo.height());
    }
    player = new PlayerItem();
    player->setPos(50, 500); // Posición inicial
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // MODIFICACIÓN: Crear 5 frutas en diferentes posiciones
    fruitsCollected = 0;
    fruits.append(new FruitItem(150, 500)); // En el suelo
    fruits.append(new FruitItem(300, 400)); // Requiere salto
    fruits.append(new FruitItem(450, 500)); // En el suelo
    fruits.append(new FruitItem(600, 350)); // Requiere salto alto
    fruits.append(new FruitItem(750, 500)); // Al final
    for (FruitItem* fruit : fruits) {
        scene->addItem(fruit);
    }

    // Interfaz (Contador de frutas y tiempo)
    fruitCounterText = new QGraphicsTextItem();
    fruitCounterText->setPlainText("Frutas: 0 / 5");
    fruitCounterText->setDefaultTextColor(Qt::yellow);
    fruitCounterText->setFont(QFont("Arial", 16));
    fruitCounterText->setPos(10, 10);
    scene->addItem(fruitCounterText);

    timeText = new QGraphicsTextItem();
    timeRemaining = 20;
    timeText->setPlainText("Tiempo: " + QString::number(timeRemaining));
    timeText->setDefaultTextColor(Qt::red);
    timeText->setFont(QFont("Arial", 16));
    timeText->setPos(650, 10);
    scene->addItem(timeText);

    level1Timer = new QTimer(this);
    connect(level1Timer, &QTimer::timeout, this, &MainWindow::updateLevel1Timer);
    level1Timer->start(1000);
}

void MainWindow::updateLevel1Timer() {
    timeRemaining--;
    timeText->setPlainText("Tiempo: " + QString::number(timeRemaining));
    if (timeRemaining <= 0) {
        level1Timer->stop();
        QMessageBox::information(this, "Tiempo Agotado", "No recolectaste todas las frutas a tiempo.");
        showMainMenu();
    }
}

void MainWindow::addBulletToList(EnergyBallItem* ball) {
    if (ball && ball->scene() && !bullets.contains(ball)) {
        bullets.append(ball);
    }
}
//NIVEL 2


void MainWindow::setupLevel2() {
    // Configuración del fondo
    QPixmap fondo(":/Img/Mapas/1/Piso.jpg");
    if (!fondo.isNull()) {
        QGraphicsPixmapItem* fondoItem = scene->addPixmap(fondo.scaled(800, 600));
        fondoItem->setZValue(-1);
        scene->setSceneRect(0, 0, 800, 600);
    }

    // Jugador
    player = new PlayerItem();
    player->setPos(50, 500);
    player->setZValue(1);
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //Conecta la señal del jugador a la MainWindow
    connect(player, &PlayerItem::energyBallFired, this, &MainWindow::addBulletToList);

    // Bulma (objetivo)
    bulmaNormal = new QGraphicsPixmapItem(QPixmap(":/Img/Bulma/Bulma_Salvar.png").scaled(60, 90));
    bulmaSalvada = new QGraphicsPixmapItem(QPixmap(":/Img/Bulma/Bulma.png").scaled(60, 90));
    bulmaNormal->setPos(600, 500);
    bulmaNormal->setZValue(1);
    bulmaNormal->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    scene->addItem(bulmaNormal);

    // Debug visual - Mostrar posición
    qDebug() << "Posición Bulma:" << bulmaNormal->pos();
    qDebug() << "Posición Inicial Goku:" << player->pos();

    // Tigre con parámetros de ataque
    tiger = new TigerItem();
    tiger->setPos(400, 500);
    scene->addItem(tiger);
    tiger->setBaseX(tiger->x());
    tiger->startPos = tiger->pos();
    tiger->setTargetPlayer(player);
    player->setTigerReference(tiger);

    bool ok = connect(tiger, &TigerItem::tigerShouldBeEliminated, this, &MainWindow::defeatTiger);
    qDebug() << "¿Se conectó la señal tigerShouldBeEliminated?" << ok;

    // UI - Contador de balas
    bulletsFired = 100;
    bulletCounterText = new QGraphicsTextItem();
    bulletCounterText->setPlainText("Balas: " + QString::number(bulletsFired));
    bulletCounterText->setDefaultTextColor(Qt::cyan);
    bulletCounterText->setFont(QFont("Arial", 16, QFont::Bold));
    bulletCounterText->setPos(10, 10);
    scene->addItem(bulletCounterText);
    bulmaRescatada = false; // Resetear estado al iniciar nivel

    // Mensaje inicial
    QGraphicsTextItem* hint = new QGraphicsTextItem("¡Dispara al tigre con F (5 veces)!");
    hint->setDefaultTextColor(Qt::yellow);
    hint->setFont(QFont("Arial", 14));
    hint->setPos(250, 100);
    scene->addItem(hint);
    QTimer::singleShot(3000, [hint]() { hint->hide(); });

    //Balas enemigas automáticas en fases
    balaTimer = new QTimer(this);
    connect(balaTimer, &QTimer::timeout, this, [this]() {
        QGraphicsPixmapItem* bala = new QGraphicsPixmapItem(QPixmap(":/Img/Elementos/Bala.png"));
        bala->setZValue(1);
        int x = 100 + rand() % 600;
        bala->setPos(x, 0);

        scene->addItem(bala);
        enemyBullets.append(bala);

        QTimer* moveTimer = new QTimer(this);
        connect(moveTimer, &QTimer::timeout, this, [this, bala, moveTimer]() {
            if (bala->scene()) {
                // Mover según fase
                if (bala->y() <= 480 && bala->x() > 100) {
                    bala->setY(bala->y() + 5);  // Vertical
                }

                if (bala->x() < 0 || bala->y() > 500) {
                    scene->removeItem(bala);
                    enemyBullets.removeOne(bala);
                    delete bala;
                    moveTimer->stop();
                    moveTimer->deleteLater();
                } else if (player && bala->collidesWithItem(player)) {
                    QMessageBox::critical(this, "¡Perdiste!", "Te golpeó una bala enemiga.");
                    qApp->exit();
                }
            }
        });
        moveTimer->start(30);
    });
    balaTimer->start(3000);  // Nueva bala cada 3 segundos
}

void MainWindow::spawnLevel3Bullets() {
    int randomType = rand() % 2; // 0 para recta, 1 para parabólica

    if (randomType == 0) { // Bala recta
        QGraphicsPixmapItem* bullet = new QGraphicsPixmapItem(QPixmap(":/Img/Elementos/Bala.png"));
        bullet->setPos(800, rand() % 550); // Posición Y aleatoria
        scene->addItem(bullet);
        enemyBullets.append(bullet);
    } else { // Bala parabólica
        EnergyBallItem* bullet = new EnergyBallItem(800, 500, 150 + (rand() % 20), 8);
        scene->addItem(bullet);
        bullets.append(bullet);
    }
}
void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!player) return;

    if (event->key() == Qt::Key_A) {
        player->moveLeft();
    } else if (event->key() == Qt::Key_D) {
        player->moveRight();
    }
    // MODIFICACIÓN: Tecla de salto W
    else if (event->key() == Qt::Key_W) {
        player->jump();
    }
    // MODIFICACIÓN: Tecla de disparo (F) para Nivel 2
    else if (event->key() == Qt::Key_F && currentLevelIndex == 2 && bulletsFired > 0 && !tigerDefeated) {
        player->shootEnergyBall(); // usa la lógica encapsulada
        bulletsFired--;
        bulletCounterText->setPlainText("Balas: " + QString::number(bulletsFired));
    }
}

// MODIFICACIÓN: Lógica central de colisiones
void MainWindow::checkCollisions() {
    if (!player) return;

    // =============================================
    // NIVEL 1: Colisión con frutas
    // =============================================
    if (currentLevelIndex == 1) {
        QList<FruitItem*> collected;
        for (FruitItem* fruit : fruits) {
            if (player->collidesWithItem(fruit)) {
                collected.append(fruit);
                scene->removeItem(fruit);
                fruitsCollected++;
                fruitCounterText->setPlainText("Frutas: " + QString::number(fruitsCollected) + " / 5");
                //Reproducir sonido de recolectar fruta
                playFruitSound();
            }
        }
        for (FruitItem* fruit : collected) {
            fruits.removeOne(fruit);
            delete fruit;
        }
        // Condición de victoria Nivel 1
        if (fruitsCollected >= 5) {
            level1Timer->stop();
            QMessageBox::information(this, "¡Nivel Completado!", "Has recolectado todas las frutas.");
            startLevel(2); // Pasar al siguiente nivel
        }
    }

    // =============================================
    // NIVEL 2: Colisiones de balas y con Bulma (VERSIÓN DEFINITIVA)
    // =============================================
    if (currentLevelIndex == 2) {
        // 1. Manejo de balas
        auto it = bullets.begin();
        while (it != bullets.end()) {
            EnergyBallItem* bullet = *it;

            if (!bullet) {
                it = bullets.erase(it);
                continue;
            }

            // Verificar si la bala fue eliminada por otro proceso
            if (!bullet->scene()) {
                delete bullet;
                it = bullets.erase(it);
                continue;
            }

            bool collisionWithTiger = false;

            // Colisión con el tigre
            if (!tigerDefeated && tiger && tiger->isAliveState() && bullet->collidesWithItem(tiger)) {
                qDebug() << "Referencia del TIGER desde MainWindow:" << static_cast<void*>(tiger);
                qDebug() << "ANTES de recibir golpe: " << tiger->getHitsReceived();
                tiger->receiveHit(); // Sumar impacto
                qDebug() << "DESPUÉS de recibir golpe: " << tiger->getHitsReceived();
                qDebug() << "Impactos al tigre:" << tiger->getHitsReceived();

                qDebug() << "Clase de tiger evaluado:" << tiger->metaObject()->className();
                qDebug() << "MainWindow ve hits:" << tiger->getHitsReceived();
                if (tiger->getHitsReceived() >= 5 && !tigerDefeated ) {
                    qDebug() << " TIGRE DERROTADO. Ejecutando lógica de eliminación.";
                    tigerDefeated = true;
                    tiger->setAlive(false);
                    tiger->hide();
                    qDebug() << "¿Tigre tiene escena antes de eliminar?" << tiger->scene();
                    if (tiger->scene()) {
                        scene->removeItem(tiger);  // Lo elimina visualmente
                    }
                    if (tiger->moveTimer) {
                        tiger->moveTimer->stop();  //  Esto detiene la lógica oscilante
                    }
                    player->setTigerReference(nullptr);
                    tiger->deleteLater();
                    QMessageBox::information(this, "¡Victoria!", "Has derrotado al tigre. ¡Ahora rescata a Bulma!");
                }
                collisionWithTiger = true;
            }
            // Eliminar balas fuera de pantalla
            else if (bullet->x() < 0 || bullet->x() > 800 || bullet->y() > 600) {
                collisionWithTiger = true; // Marcamos para eliminar
            }

            if (collisionWithTiger) {
                if (bullet->scene()) {
                    scene->removeItem(bullet);
                }
                delete bullet;
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }

        // 2. Rescate de Bulma
        if (tigerDefeated && !bulmaRescatada && bulmaNormal && bulmaNormal->scene()) {
            if (player->collidesWithItem(bulmaNormal)) {
                bulmaRescatada = true;
                QPointF bulmaPos = bulmaNormal->pos();

                // Eliminar Bulma normal
                scene->removeItem(bulmaNormal);
                delete bulmaNormal;
                bulmaNormal = nullptr;

                // Mostrar Bulma rescatada
                if (bulmaSalvada) {
                    bulmaSalvada->setPos(bulmaPos);
                    scene->addItem(bulmaSalvada);
                }

                QMessageBox::information(this, "¡Rescate Exitoso!",
                                         "¡Gracias Goku por salvarme!\n"
                                         "Preparándote para el próximo nivel...");

                QTimer::singleShot(2000, this, [this]() {
                    startLevel(3);
                });
            }
        }
    }

}
void MainWindow::playFruitSound() {
    if (!fruitSound->source().isEmpty()) {
        fruitSound->play();
        return;
    }
    fruitSound->setSource(QUrl(":/sounds/fruit_collect.wav"));
    fruitSound->play();
}

void MainWindow::playShootSound() {
    if (!shootSound->source().isEmpty()) {
        shootSound->play();
        return;
    }
    shootSound->setSource(QUrl(":/sounds/energy_ball.wav"));
    shootSound->play();
}
void MainWindow::defeatTiger() {
    if (!tiger || tigerDefeated) return;

    tigerDefeated = true;
    tiger->setAlive(false);
    tiger->hide();
    if (tiger->scene()) scene->removeItem(tiger);
    if (tiger->moveTimer) tiger->moveTimer->stop();
    player->setTigerReference(nullptr);
    tiger->deleteLater();
    QMessageBox::information(this, "¡Victoria!", "Has derrotado al tigre. ¡Ahora rescata a Bulma!");
}
