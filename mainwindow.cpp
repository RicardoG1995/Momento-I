#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QBrush>
#include <QPalette>
#include <QGraphicsOpacityEffect>  // Para efectos visuales
#include <QPropertyAnimation>

//Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

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

    ui->graphicsView->show();        // Asegura que se vea el fondo
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
    case 3:
        setupLevel3();
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
    bullets.clear();
    enemyBullets.clear();

    // Detener todos los timers para que no interfieran
    if (gameTimer->isActive()) gameTimer->stop();
    if (level1Timer && level1Timer->isActive()) level1Timer->stop();
    if (bulletSpawnerTimer && bulletSpawnerTimer->isActive()) bulletSpawnerTimer->stop();


    player = nullptr;
    tiger = nullptr;
    bulma = nullptr;
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
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Tigre con parámetros de ataque
    tiger = new TigerItem();
    tiger->setPos(400, 500);
    scene->addItem(tiger);
    tiger->setBaseX(tiger->x());
    tiger->startPos = tiger->pos();
    tiger->setTargetPlayer(player);


    // Bulma (objetivo)
    bulmaNormal = new QGraphicsPixmapItem(QPixmap(":/Img/Bulma/Bulma_Salvar.png").scaled(60, 90));
    bulmaSalvada = new QGraphicsPixmapItem(QPixmap(":/Img/Bulma/Bulma.png").scaled(60, 90));
    bulmaNormal->setPos(600, 500);
    bulmaNormal->setZValue(1);
    scene->addItem(bulmaNormal);

    // UI - Contador de balas
    bulletsFired = 5;
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
}

void MainWindow::setupLevel3() {
    // Jugador
    player = new PlayerItem();
    player->setPos(50, 500);
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // Bulma acompañante
    bulmaNormal = new QGraphicsPixmapItem(QPixmap(":/Img/Bulma/Bulma.png"));
    bulmaNormal->setPos(player->x() - 50, player->y()); // Detrás de Goku
    scene->addItem(bulmaNormal);

    // Esfera del Dragón (objetivo)
    dragonBall = new QGraphicsPixmapItem(QPixmap(":/Img/Elementos/Bala.png")); // Asegúrate de tenerla
    dragonBall->setPos(750, 500);
    scene->addItem(dragonBall);

    // MODIFICACIÓN: Timer para generar balas enemigas
    bulletSpawnerTimer = new QTimer(this);
    connect(bulletSpawnerTimer, &QTimer::timeout, this, &MainWindow::spawnLevel3Bullets);
    bulletSpawnerTimer->start(1500); // Genera una bala cada 1.5 segundos
}

// MODIFICACIÓN: Nueva función para generar balas en el Nivel 3
void MainWindow::spawnLevel3Bullets() {
    int randomType = rand() % 2; // 0 para recta, 1 para parabólica

    if (randomType == 0) { // Bala recta
        QGraphicsPixmapItem* bullet = new QGraphicsPixmapItem(QPixmap(":/Img/Elementos/Bala.png"));
        bullet->setPos(800, rand() % 550); // Posición Y aleatoria
        scene->addItem(bullet);
        enemyBullets.append(bullet);
    } else { // Bala parabólica
        EnergyBallItem* bullet = new EnergyBallItem(800, 500, 150 + (rand() % 20), 8); // Ángulo hacia arriba y a la izquierda
        scene->addItem(bullet);
        // La gestionaremos como EnergyBallItem para aprovechar su `advance`
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
        EnergyBallItem* ball = new EnergyBallItem(player->x(), player->y(), -20, 15); // Disparo parabólico
        scene->addItem(ball);
        bullets.append(ball);
        bulletsFired--;
        bulletCounterText->setPlainText("Balas: " + QString::number(bulletsFired));
    }
}

// MODIFICACIÓN: Lógica central de colisiones
void MainWindow::checkCollisions() {
    if (!player) return;

    // Nivel 1: Colisión con frutas
    if (currentLevelIndex == 1) {
        QList<FruitItem*> collected;
        for (FruitItem* fruit : fruits) {
            if (player->collidesWithItem(fruit)) {
                collected.append(fruit);
                scene->removeItem(fruit);
                fruitsCollected++;
                fruitCounterText->setPlainText("Frutas: " + QString::number(fruitsCollected) + " / 5");
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
    // Nivel 2: Colisiones de balas y con Bulma
    if (currentLevelIndex == 2) {
        // Balas de Goku vs Tigre
        if (!tigerDefeated) {
            QList<EnergyBallItem*> bulletsToRemove;
            for (EnergyBallItem* bullet : bullets) {
                if (bullet->collidesWithItem(tiger)) {
                    bulletsToRemove.append(bullet);
                    tiger->receiveHit();
                    if (tiger->getHitsReceived() >= 5) {
                        tigerDefeated = true;
                        tiger->setAlive(false);
                        QMessageBox::information(this, "¡Bien Hecho!", "Has derrotado al tigre. ¡Ahora rescata a Bulma!");
                    }
                }
            }
            for (EnergyBallItem* bullet : bulletsToRemove) {
                scene->removeItem(bullet);
                bullets.removeOne(bullet);
                delete bullet;
            }
        }

        // Jugador vs Bulma (condición de victoria)
        if (tigerDefeated && !bulmaRescatada) {
            // Detección de colisión simple
            if (player->collidesWithItem(bulmaNormal)) {
                bulmaRescatada = true;

                // Cambiar imagen de Bulma sin efectos adicionales
                scene->removeItem(bulmaNormal);
                bulmaSalvada->setPos(bulmaNormal->pos());
                scene->addItem(bulmaSalvada);

                // Mensaje de agradecimiento
                QMessageBox::information(this,
                                         "¡Rescate Exitoso!",
                                         "¡Gracias Goku por salvarme!\n"
                                         "Preparándote para el próximo nivel...");

                // Pasar al siguiente nivel después de 2 segundos
                QTimer::singleShot(2000, this, [this]() {
                    startLevel(3);
                });
            }
        }
    }
    // Nivel 3: Colisiones
    if (currentLevelIndex == 3) {
        // Mover a Bulma para que siga a Goku
        if(bulmaNormal) bulmaNormal->setPos(player->x() - 50, player->y());

        // Colisión con balas enemigas
        for(QGraphicsPixmapItem* bullet : enemyBullets) {
            bullet->setX(bullet->x() - 10); // Movimiento de la bala recta
            if (player->collidesWithItem(bullet)) {
                QMessageBox::critical(this, "¡Has perdido!", "Goku ha sido alcanzado.");
                showMainMenu();
                return;
            }
            if(bullet->x() < 0) { // Eliminar si sale de pantalla
                scene->removeItem(bullet);
                enemyBullets.removeOne(bullet);
                delete bullet;
            }
        }
        // Colisión con balas parabólicas enemigas
        for(EnergyBallItem* bullet : bullets) {
            if (player->collidesWithItem(bullet)) {
                QMessageBox::critical(this, "¡Has perdido!", "Goku ha sido alcanzado por un disparo parabólico.");
                showMainMenu();
                return;
            }
        }
        // Colisión con Esfera del Dragón (condición de victoria)
        if (dragonBall && player->collidesWithItem(dragonBall)) {
            QMessageBox::information(this, "¡Nivel Completado!", "Has encontrado la Esfera del Dragón.");
            startLevel(4); // Intentar iniciar el siguiente nivel o terminar
        }
    }
}
