# Diseño de Niveles - GameDB

## 🎯 Visión General del Sistema de Niveles

GameDB presenta un sistema de niveles progresivo diseñado para introducir gradualmente las mecánicas del juego y aumentar la dificultad de manera equilibrada. Cada nivel tiene objetivos únicos y mecánicas específicas que contribuyen a una experiencia de juego completa.

## 🏗️ Arquitectura del Sistema de Niveles

### Estructura de Niveles
```
┌─────────────────────────────────────────────────────────┐
│                    Level System                         │
├─────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │   Level 1   │  │   Level 2   │  │   Level 3   │     │
│  │  (Fruits)   │  │  (Rescue)   │  │(Survival)   │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
├─────────────────────────────────────────────────────────┤
│                 Level Manager                           │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │   Setup     │  │   State     │  │  Progress   │     │
│  │  Levels     │  │  Manager    │  │  Tracking   │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
└─────────────────────────────────────────────────────────┘
```

### Clase Level
```cpp
class Level {
public:
    int levelNumber;
    std::string description;
    std::vector<Objective> objectives;
    std::vector<PhysicsModel> physics;
    
    void loadLevel();
    bool checkCompletion();
};
```

## 🍎 Nivel 1: Recolección de Frutas

### Descripción General
El primer nivel introduce al jugador a las mecánicas básicas de movimiento y colección. Es un nivel de tutorial que establece los fundamentos del juego.

### Objetivos del Nivel
- **Objetivo Principal**: Recolectar todas las frutas disponibles
- **Objetivo Secundario**: Completar el nivel antes del tiempo límite
- **Objetivo de Aprendizaje**: Dominar el movimiento básico y salto

### Configuración del Nivel
```cpp
void MainWindow::setupLevel1() {
    // Configuración básica
    currentLevelIndex = 1;
    timeRemaining = 30;  // 30 segundos
    fruitsCollected = 0;
    bulletsFired = 0;
    
    // Configurar escena
    scene->setBackgroundBrush(QBrush(QPixmap(":/Img/Mapas/1/Fondo.jpg")));
    
    // Crear plataformas
    createPlatforms();
    
    // Spawn de frutas
    spawnFruits();
    
    // Crear jugador
    player = new PlayerItem();
    player->setPos(100, 400);
    scene->addItem(player);
    
    // Configurar UI
    setupLevel1UI();
    
    // Iniciar temporizador
    startLevel1Timer();
}
```

### Elementos del Nivel

#### Plataformas
- **Suelo principal**: Posición Y = 500
- **Plataformas flotantes**: 3-4 plataformas a diferentes alturas
- **Material**: Textura de suelo (`Piso.jpg`)

#### Frutas
- **Cantidad**: 5-8 frutas (configurable)
- **Posiciones**: Distribuidas estratégicamente
- **Colisión**: Radio de 30 unidades
- **Sprite**: `Fruta.png`

#### Configuración de Spawn
```cpp
void MainWindow::spawnFruits() {
    // Posiciones predefinidas para las frutas
    QList<QPointF> fruitPositions = {
        QPointF(200, 450),   // Plataforma baja
        QPointF(400, 350),   // Plataforma media
        QPointF(600, 250),   // Plataforma alta
        QPointF(300, 450),   // Suelo
        QPointF(500, 350),   // Plataforma media
        QPointF(700, 450)    // Suelo lejano
    };
    
    for (const QPointF& pos : fruitPositions) {
        FruitItem* fruit = new FruitItem(pos.x(), pos.y());
        fruits.append(fruit);
        scene->addItem(fruit);
    }
}
```

### Mecánicas Específicas

#### Sistema de Tiempo
```cpp
void MainWindow::updateLevel1Timer() {
    timeRemaining--;
    
    // Actualizar display
    if (timeText) {
        timeText->setPlainText(QString("Tiempo: %1").arg(timeRemaining));
    }
    
    // Verificar fin de tiempo
    if (timeRemaining <= 0) {
        gameOver("¡Se acabó el tiempo!");
    }
}
```

#### Condiciones de Victoria
```cpp
bool MainWindow::checkLevel1Completion() {
    // Verificar si se recolectaron todas las frutas
    if (fruitsCollected >= totalFruits) {
        // Calcular puntuación
        int timeBonus = timeRemaining * 5;  // 5 puntos por segundo
        int totalScore = (fruitsCollected * 10) + timeBonus;
        
        // Mostrar pantalla de victoria
        showLevelComplete(totalScore);
        return true;
    }
    return false;
}
```

### Progresión de Dificultad
- **Movimiento**: Introducción gradual de controles
- **Salto**: Timing y precisión
- **Colección**: Eficiencia y planificación
- **Tiempo**: Presión temporal

## 🦸 Nivel 2: Rescate de Bulma

### Descripción General
El segundo nivel introduce elementos de combate y enemigos. El jugador debe rescatar a Bulma mientras evita o derrota al tigre enemigo.

### Objetivos del Nivel
- **Objetivo Principal**: Llegar a Bulma y rescatarla
- **Objetivo Secundario**: Derrotar al tigre (opcional)
- **Objetivo de Aprendizaje**: Combate y evasión

### Configuración del Nivel
```cpp
void MainWindow::setupLevel2() {
    // Configuración del nivel
    currentLevelIndex = 2;
    tigerDefeated = false;
    bulmaRescatada = false;
    
    // Configurar escena
    scene->setBackgroundBrush(QBrush(QPixmap(":/Img/Mapas/1/Fondo.jpg")));
    
    // Crear plataformas más complejas
    createComplexPlatforms();
    
    // Crear jugador
    player = new PlayerItem();
    player->setPos(100, 400);
    scene->addItem(player);
    
    // Crear tigre enemigo
    tiger = new TigerItem();
    tiger->setPos(400, 450);
    tiger->setTargetPlayer(player);
    scene->addItem(tiger);
    
    // Crear Bulma
    bulma = new QGraphicsPixmapItem(QPixmap(":/Img/Bulma/Bulma.png"));
    bulma->setPos(700, 450);
    scene->addItem(bulma);
    
    // Configurar UI
    setupLevel2UI();
}
```

### Elementos del Nivel

#### Plataformas Complejas
- **Múltiples niveles**: 3-4 alturas diferentes
- **Gaps estratégicos**: Requieren timing de salto
- **Posicionamiento**: Para crear rutas alternativas

#### Tigre Enemigo
- **Posición inicial**: Centro del nivel
- **Comportamiento**: Movimiento oscilatorio
- **IA de ataque**: Salto parabólico hacia el jugador
- **Vida**: 5 impactos

#### Bulma (Objetivo)
- **Posición**: Extremo derecho del nivel
- **Estados**: Normal → Rescatada
- **Trigger**: Contacto con el jugador

### Mecánicas Específicas

#### Sistema de Combate
```cpp
void MainWindow::checkLevel2Collisions() {
    // Colisión jugador-tigre
    if (tiger && checkDistanceCollision(player->pos(), tiger->pos(), 50.0)) {
        // El tigre ataca al jugador
        if (tiger->isAttackingState()) {
            // Daño al jugador (si implementado)
            playerDamaged();
        }
    }
    
    // Colisión bola-tigre
    for (EnergyBallItem* bullet : bullets) {
        if (tiger && checkDistanceCollision(bullet->pos(), tiger->pos(), 40.0)) {
            tiger->receiveHit();
            scene->removeItem(bullet);
            bullets.removeOne(bullet);
            delete bullet;
            
            if (tiger->getHitsReceived() >= 5) {
                defeatTiger();
            }
        }
    }
    
    // Colisión jugador-Bulma
    if (bulma && !bulmaRescatada) {
        if (checkDistanceCollision(player->pos(), bulma->pos(), 60.0)) {
            rescueBulma();
        }
    }
}
```

#### IA del Tigre
```cpp
void TigerItem::updateAI() {
    // Movimiento oscilatorio
    moveOscillate();
    
    // Verificar proximidad del jugador
    if (targetPlayer) {
        qreal distance = QLineF(pos(), targetPlayer->pos()).length();
        
        if (distance <= attackRange && !isAttacking) {
            initiateAttack();
        }
    }
}
```

#### Rescate de Bulma
```cpp
void MainWindow::rescueBulma() {
    bulmaRescatada = true;
    
    // Cambiar sprite de Bulma
    bulma->setPixmap(QPixmap(":/Img/Bulma/Bulma_Salvar.png"));
    
    // Mostrar mensaje de victoria
    showMessage("¡Bulma rescatada! Nivel completado.");
    
    // Transición al siguiente nivel
    QTimer::singleShot(2000, this, &MainWindow::nextLevel);
}
```

### Progresión de Dificultad
- **Enemigos**: Introducción del tigre
- **Combate**: Sistema de disparos
- **Objetivos**: Múltiples objetivos
- **Estrategia**: Planificación de rutas

## ⚡ Nivel 3: Supervivencia

### Descripción General
El tercer nivel es un desafío de supervivencia donde el jugador debe evitar balas enemigas mientras usa munición limitada para defenderse.

### Objetivos del Nivel
- **Objetivo Principal**: Sobrevivir el mayor tiempo posible
- **Objetivo Secundario**: Destruir balas enemigas críticas
- **Objetivo de Aprendizaje**: Evasión y gestión de recursos

### Configuración del Nivel
```cpp
void MainWindow::setupLevel3() {
    // Configuración del nivel
    currentLevelIndex = 3;
    bulletsFired = 0;
    maxBullets = 5;
    
    // Configurar escena
    scene->setBackgroundBrush(QBrush(QPixmap(":/Img/Mapas/1/Fondo.jpg")));
    
    // Crear plataformas de supervivencia
    createSurvivalPlatforms();
    
    // Crear jugador
    player = new PlayerItem();
    player->setPos(400, 400);
    scene->addItem(player);
    
    // Configurar spawn de balas enemigas
    setupEnemyBulletSpawner();
    
    // Configurar UI
    setupLevel3UI();
}
```

### Elementos del Nivel

#### Plataformas de Supervivencia
- **Plataformas móviles**: Cambian de posición
- **Plataformas destructibles**: Desaparecen al tocarlas
- **Zonas seguras**: Áreas temporales de refugio

#### Balas Enemigas
- **Spawn automático**: Cada 2 segundos
- **Patrones variados**: Directo, parabólico, en zigzag
- **Velocidades diferentes**: 5-15 unidades/frame
- **Colisión**: Daño instantáneo al jugador

### Mecánicas Específicas

#### Sistema de Spawn de Balas
```cpp
void MainWindow::spawnLevel3Bullets() {
    // Generar posición aleatoria en los bordes
    qreal spawnX, spawnY;
    int side = QRandomGenerator::global()->bounded(4);
    
    switch (side) {
        case 0: // Arriba
            spawnX = QRandomGenerator::global()->bounded(800);
            spawnY = -50;
            break;
        case 1: // Derecha
            spawnX = 850;
            spawnY = QRandomGenerator::global()->bounded(600);
            break;
        case 2: // Abajo
            spawnX = QRandomGenerator::global()->bounded(800);
            spawnY = 650;
            break;
        case 3: // Izquierda
            spawnX = -50;
            spawnY = QRandomGenerator::global()->bounded(600);
            break;
    }
    
    // Calcular dirección hacia el jugador
    QPointF direction = player->pos() - QPointF(spawnX, spawnY);
    qreal distance = QLineF(spawnX, spawnY, player->pos().x(), player->pos().y()).length();
    
    // Normalizar y aplicar velocidad
    qreal speed = QRandomGenerator::global()->bounded(5, 15);
    qreal vx = (direction.x() / distance) * speed;
    qreal vy = (direction.y() / distance) * speed;
    
    // Crear bala enemiga
    QGraphicsPixmapItem* enemyBullet = new QGraphicsPixmapItem(QPixmap(":/Img/Elementos/Bala.png"));
    enemyBullet->setPos(spawnX, spawnY);
    enemyBullets.append(enemyBullet);
    scene->addItem(enemyBullet);
    
    // Configurar movimiento
    QTimer* bulletTimer = new QTimer();
    connect(bulletTimer, &QTimer::timeout, [=]() {
        moveEnemyBullet(enemyBullet, vx, vy);
    });
    bulletTimer->start(16);  // 60 FPS
}
```

#### Movimiento de Balas Enemigas
```cpp
void MainWindow::moveEnemyBullet(QGraphicsPixmapItem* bullet, qreal vx, qreal vy) {
    // Actualizar posición
    bullet->setPos(bullet->pos().x() + vx, bullet->pos().y() + vy);
    
    // Verificar límites de pantalla
    if (bullet->pos().x() < -100 || bullet->pos().x() > 900 ||
        bullet->pos().y() < -100 || bullet->pos().y() > 700) {
        scene->removeItem(bullet);
        enemyBullets.removeOne(bullet);
        delete bullet;
    }
    
    // Verificar colisión con jugador
    if (checkDistanceCollision(player->pos(), bullet->pos(), 35.0)) {
        gameOver("¡Has sido golpeado por una bala enemiga!");
    }
}
```

#### Gestión de Munición
```cpp
void MainWindow::updateBulletCounter() {
    if (bulletCounterText) {
        bulletCounterText->setPlainText(QString("Balas: %1/%2")
            .arg(maxBullets - bulletsFired)
            .arg(maxBullets));
    }
}

void MainWindow::checkBulletLimit() {
    if (bulletsFired >= maxBullets) {
        // Deshabilitar disparo
        player->setCanShoot(false);
    }
}
```

### Progresión de Dificultad
- **Frecuencia de balas**: Aumenta con el tiempo
- **Velocidad de balas**: Varía aleatoriamente
- **Patrones complejos**: Balas que siguen al jugador
- **Munición limitada**: Gestión estratégica de recursos

## 📊 Sistema de Progresión

### Transición Entre Niveles
```cpp
void MainWindow::nextLevel() {
    // Limpiar nivel actual
    clearScene();
    
    // Incrementar nivel
    currentLevelIndex++;
    
    // Configurar siguiente nivel
    switch (currentLevelIndex) {
        case 2:
            setupLevel2();
            break;
        case 3:
            setupLevel3();
            break;
        default:
            showGameComplete();
            break;
    }
}
```

### Sistema de Puntuación
```cpp
struct LevelScore {
    int baseScore;
    int timeBonus;
    int efficiencyBonus;
    int totalScore;
};

LevelScore calculateLevelScore(int level, int timeRemaining, int objectivesCompleted) {
    LevelScore score;
    
    switch (level) {
        case 1:
            score.baseScore = objectivesCompleted * 10;
            score.timeBonus = timeRemaining * 5;
            score.efficiencyBonus = (timeRemaining > 15) ? 50 : 0;
            break;
        case 2:
            score.baseScore = 100;  // Completar rescate
            score.timeBonus = 0;    // Sin límite de tiempo
            score.efficiencyBonus = (tigerDefeated) ? 50 : 0;
            break;
        case 3:
            score.baseScore = survivalTime * 10;
            score.timeBonus = bulletsRemaining * 20;
            score.efficiencyBonus = (bulletsRemaining > 2) ? 100 : 0;
            break;
    }
    
    score.totalScore = score.baseScore + score.timeBonus + score.efficiencyBonus;
    return score;
}
```

### Persistencia de Progreso
```cpp
void MainWindow::saveProgress() {
    QSettings settings("GameDB", "Progress");
    settings.setValue("currentLevel", currentLevelIndex);
    settings.setValue("totalScore", totalScore);
    settings.setValue("highestLevel", qMax(highestLevel, currentLevelIndex));
}

void MainWindow::loadProgress() {
    QSettings settings("GameDB", "Progress");
    currentLevelIndex = settings.value("currentLevel", 1).toInt();
    totalScore = settings.value("totalScore", 0).toInt();
    highestLevel = settings.value("highestLevel", 1).toInt();
}
```

## 🎮 Configuración de Dificultad

### Niveles de Dificultad
```cpp
enum DifficultyLevel {
    EASY,
    NORMAL,
    HARD
};

struct DifficultyConfig {
    qreal enemySpeed;
    qreal bulletFrequency;
    int timeLimit;
    int maxBullets;
    qreal playerSpeed;
};
```

### Configuraciones por Dificultad
```cpp
std::map<DifficultyLevel, DifficultyConfig> difficultyConfigs = {
    {EASY, {0.8, 0.7, 40, 7, 1.2}},    // Más tiempo, más munición
    {NORMAL, {1.0, 1.0, 30, 5, 1.0}},  // Configuración estándar
    {HARD, {1.3, 1.5, 20, 3, 0.8}}     // Menos tiempo, menos munición
};
```

## 🔧 Herramientas de Diseño

### Editor de Niveles (Conceptual)
```cpp
class LevelEditor {
public:
    void addPlatform(qreal x, qreal y, qreal width, qreal height);
    void addEnemy(qreal x, qreal y, EnemyType type);
    void addObjective(qreal x, qreal y, ObjectiveType type);
    void setBackground(const QString& backgroundPath);
    void saveLevel(const QString& filename);
    void loadLevel(const QString& filename);
};
```

### Validación de Niveles
```cpp
bool validateLevel(const Level& level) {
    // Verificar que el jugador puede alcanzar todos los objetivos
    // Verificar que no hay áreas inaccesibles
    // Verificar que la dificultad es apropiada
    // Verificar que todos los recursos están disponibles
    
    return true;
}
```

## 📈 Métricas y Análisis

### Métricas de Nivel
```cpp
struct LevelMetrics {
    int completionRate;      // Porcentaje de jugadores que completan
    float averageTime;       // Tiempo promedio de completado
    int averageScore;        // Puntuación promedio
    int restartCount;        // Número de reintentos promedio
    QString hardestSection;  // Sección más difícil
};
```

### Análisis de Jugabilidad
- **Tiempo de completado**: 2-5 minutos por nivel
- **Tasa de éxito**: 70-90% en primer intento
- **Puntos de frustración**: Identificar y ajustar
- **Flujo del juego**: Mantener engagement constante 