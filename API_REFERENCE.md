# Referencia de API - GameDB

## 📚 Índice de Clases

### Clases Principales
- [MainWindow](#mainwindow)
- [Game](#game)
- [PlayerItem](#playeritem)
- [TigerItem](#tigeritem)
- [EnergyBallItem](#energyballitem)
- [FruitItem](#fruititem)

### Clases de Soporte
- [Player](#player)
- [Enemy](#enemy)
- [Vector2D](#vector2d)
- [Level](#level)
- [PhysicsEngine](#physicsengine)
- [PhysicsModel](#physicsmodel)
- [Objective](#objective)

---

## 🏠 MainWindow

### Descripción
Clase principal que maneja la interfaz de usuario y coordina todos los sistemas del juego.

### Herencia
```cpp
class MainWindow : public QMainWindow
```

### Constructor
```cpp
MainWindow(QWidget *parent = nullptr)
```

### Métodos Públicos

#### Gestión del Juego
```cpp
void defeatTiger()
```
**Descripción:** Marca al tigre como derrotado y actualiza el estado del juego.

#### Slots Privados
```cpp
void updateGame()
```
**Descripción:** Actualiza la lógica principal del juego en cada frame.

```cpp
void updateLevel1Timer()
```
**Descripción:** Actualiza el temporizador del nivel 1.

```cpp
void spawnLevel3Bullets()
```
**Descripción:** Genera balas enemigas en el nivel 3.

```cpp
void addBulletToList(EnergyBallItem* ball)
```
**Descripción:** Añade una bala de energía a la lista de proyectiles activos.

### Atributos Privados

#### Componentes de UI
```cpp
Ui::MainWindow *ui
QGraphicsScene* scene
QPushButton* playButton
QPushButton* exitButton
```

#### Elementos del Juego
```cpp
PlayerItem* player
TigerItem* tiger
QGraphicsPixmapItem* bulma
QGraphicsPixmapItem* dragonBall
QGraphicsPixmapItem* bulmaNormal
QGraphicsPixmapItem* bulmaSalvada
```

#### Audio
```cpp
QMediaPlayer* fruitSound
QMediaPlayer* shootSound
```

#### Listas de Elementos
```cpp
QList<FruitItem*> fruits
QList<EnergyBallItem*> bullets
QList<QGraphicsPixmapItem*> balasEnemigasNivel2
QList<QGraphicsPixmapItem*> enemyBullets
```

#### Temporizadores
```cpp
QTimer* gameTimer
QTimer* level1Timer
QTimer* bulletSpawnerTimer
QTimer* balaTimer
```

#### Estado del Juego
```cpp
int timeRemaining
int fruitsCollected
int bulletsFired
bool tigerDefeated
bool bulmaRescatada
int currentLevelIndex
```

#### UI en Escena
```cpp
QGraphicsTextItem* timeText
QGraphicsTextItem* fruitCounterText
QGraphicsTextItem* bulletCounterText
```

### Métodos Privados

#### Configuración de Niveles
```cpp
void setupLevels()
void startLevel(int index)
void setupLevel1()
void setupLevel2()
void setupLevel3()
```

#### Gestión de Escena
```cpp
void clearScene()
void showMainMenu()
```

#### Lógica del Juego
```cpp
void checkCollisions()
void playFruitSound()
void playShootSound()
```

#### Eventos
```cpp
void keyPressEvent(QKeyEvent* event) override
```

---

## 🎮 Game

### Descripción
Controlador principal del juego que maneja el estado global y coordina los sistemas.

### Constructor
```cpp
Game()
```

### Atributos Públicos
```cpp
int currentLevel
Player player
std::vector<Enemy> enemies
PhysicsEngine physicsEngine
```

### Métodos Públicos
```cpp
void startGame()
void nextLevel()
void update()
```

---

## 🦸 PlayerItem

### Descripción
Representación gráfica del jugador (Goku) con animaciones y física básica.

### Herencia
```cpp
class PlayerItem : public QObject, public QGraphicsPixmapItem
```

### Constructor
```cpp
PlayerItem()
```

### Métodos Públicos

#### Movimiento
```cpp
void moveLeft()
void moveRight()
void jump()
void shootEnergyBall()
```

#### Configuración
```cpp
void setTigerReference(TigerItem* tigerRef)
QRectF boundingRect() const override
```

### Señales
```cpp
void energyBallFired(EnergyBallItem* ball)
void playShootSound()
```

### Métodos Protegidos
```cpp
void advance(int phase) override
```

### Atributos Privados

#### Sprites
```cpp
QPixmap standPixmap
QPixmap jumpPixmap
QPixmap attackPixmap
QVector<QPixmap> leftAnimationFrames
QVector<QPixmap> rightAnimationFrames
```

#### Estado de Animación
```cpp
int leftAnimIndex
int rightAnimIndex
bool isAttacking
```

#### Física
```cpp
qreal velocityY
bool onGround
```

#### Referencias
```cpp
TigerItem* tiger
QMediaPlayer* shootSound
QAudioOutput* shootAudioOutput
```

### Slots Privados
```cpp
void finishAttackAnimation()
```

---

## 🐯 TigerItem

### Descripción
Enemigo principal con IA de movimiento oscilatorio y sistema de ataque.

### Herencia
```cpp
class TigerItem : public QObject, public QGraphicsPixmapItem
```

### Constructor
```cpp
TigerItem()
```

### Métodos Públicos

#### Movimiento y Estado
```cpp
void moveOscillate()
void setAlive(bool alive)
void receiveHit()
bool isAliveState() const
bool isAttackingState() const
```

#### Ataque
```cpp
void initiateAttack()
void setAttackParameters(qreal range, qreal height)
void setTargetPlayer(QGraphicsItem* player)
```

#### Información
```cpp
int getHitsReceived() const
QPointF startPos
void returnToStart()
void setBaseX(qreal x)
```

### Señales
```cpp
void tigerShouldBeEliminated()
```

### Atributos Privados

#### Sprites
```cpp
QPixmap normalPixmap
QPixmap attackPixmap
QVector<QPixmap> walkLeftFrames
QVector<QPixmap> walkRightFrames
```

#### Animación
```cpp
int currentFrame
int animationSpeed
int frameCounter
bool movingRight
```

#### Estado
```cpp
qreal amplitude
qreal baseX
bool isAlive
int hitsReceived
bool isAttacking
```

#### Ataque
```cpp
qreal attackRange
qreal jumpHeight
QGraphicsItem* targetPlayer
QTimer* attackTimer
QTimer* moveTimer
```

---

## ⚡ EnergyBallItem

### Descripción
Proyectil de energía disparado por el jugador con física parabólica.

### Herencia
```cpp
class EnergyBallItem : public QObject, public QGraphicsPixmapItem
```

### Constructor
```cpp
EnergyBallItem(qreal startX, qreal startY, qreal angleDeg, qreal speed)
```

**Parámetros:**
- `startX`: Posición inicial en X
- `startY`: Posición inicial en Y
- `angleDeg`: Ángulo de disparo en grados
- `speed`: Velocidad inicial del proyectil

### Métodos Protegidos
```cpp
void advance(int phase) override
```

### Atributos Privados
```cpp
qreal vx
qreal vy
qreal gravity
```

---

## 🍎 FruitItem

### Descripción
Objeto recolectable que otorga puntos al jugador.

### Herencia
```cpp
class FruitItem : public QObject, public QGraphicsPixmapItem
```

### Constructor
```cpp
FruitItem(qreal x, qreal y)
```

**Parámetros:**
- `x`: Posición X en la escena
- `y`: Posición Y en la escena

### Atributos Privados
```cpp
QPixmap fruitPixmap
```

---

## 👤 Player

### Descripción
Clase lógica que representa al jugador con sus estadísticas y comportamiento.

### Atributos Públicos
```cpp
std::string name
Vector2D position
Vector2D velocity
int health
```

### Métodos Públicos
```cpp
void move()
void attack()
void collectItem()
```

---

## 👹 Enemy

### Descripción
Clase base para enemigos con comportamiento básico.

### Atributos Públicos
```cpp
std::string type
Vector2D position
std::string behavior
```

### Métodos Públicos
```cpp
void act()
void attackPlayer()
```

---

## 📐 Vector2D

### Descripción
Clase matemática para representar vectores bidimensionales.

### Constructor
```cpp
Vector2D()
Vector2D(float xVal, float yVal)
```

### Atributos Públicos
```cpp
float x
float y
```

### Métodos Públicos

#### Operaciones Vectoriales
```cpp
float magnitude() const
Vector2D normalize() const
float dot(const Vector2D& other) const
```

#### Operadores
```cpp
Vector2D operator+(const Vector2D& other) const
Vector2D operator-(const Vector2D& other) const
Vector2D operator*(float scalar) const
Vector2D& operator+=(const Vector2D& other)
Vector2D& operator-=(const Vector2D& other)
```

#### Utilidad
```cpp
void print() const
```

---

## 🎯 Level

### Descripción
Representa un nivel del juego con objetivos y modelos físicos.

### Atributos Públicos
```cpp
int levelNumber
std::string description
std::vector<Objective> objectives
std::vector<PhysicsModel> physics
```

### Métodos Públicos
```cpp
void loadLevel()
bool checkCompletion()
```

---

## ⚙️ PhysicsEngine

### Descripción
Motor de físicas que maneja una lista de modelos físicos.

### Atributos Públicos
```cpp
std::vector<PhysicsModel> models
```

### Métodos Públicos
```cpp
void applyPhysics(void* entity)
```

---

## 🔬 PhysicsModel

### Descripción
Modelo físico individual con nombre y fórmula de simulación.

### Atributos Públicos
```cpp
std::string name
std::string formula
```

### Métodos Públicos
```cpp
void simulate()
```

---

## 🎯 Objective

### Descripción
Objetivo individual dentro de un nivel del juego.

### Atributos Públicos
```cpp
std::string description
bool completed
```

### Métodos Públicos
```cpp
void check()
```

---

## 🔧 Constantes y Configuración

### Configuración del Juego
```cpp
// Temporizadores
const int GAME_TIMER_INTERVAL = 16;  // ~60 FPS
const int LEVEL1_TIME_LIMIT = 30;    // segundos
const int BULLET_SPAWN_INTERVAL = 2000; // ms

// Física
const qreal GRAVITY = 0.5;
const qreal JUMP_VELOCITY = -15.0;
const qreal MOVE_SPEED = 5.0;

// Colisiones
const qreal COLLISION_THRESHOLD = 50.0;
const qreal TIGER_ATTACK_RANGE = 150.0;

// Estados
const int TIGER_MAX_HITS = 5;
const int PLAYER_MAX_BULLETS = 5;
```

### Configuración de Audio
```cpp
// Volúmenes
const int FRUIT_SOUND_VOLUME = 50;
const int SHOOT_SOUND_VOLUME = 70;

// Archivos de sonido
const QString FRUIT_SOUND_FILE = "sounds/fruit_collect.wav";
const QString SHOOT_SOUND_FILE = "sounds/energy_ball.wav";
```

---

## 📋 Convenciones de Nomenclatura

### Clases
- **PascalCase**: `PlayerItem`, `TigerItem`, `EnergyBallItem`
- **Prefijos descriptivos**: `QGraphicsPixmapItem` para elementos gráficos

### Métodos
- **camelCase**: `moveLeft()`, `shootEnergyBall()`, `checkCollisions()`
- **Verbos descriptivos**: `initiateAttack()`, `receiveHit()`

### Variables
- **camelCase**: `velocityY`, `isAttacking`, `fruitsCollected`
- **Prefijos de tipo**: `qreal` para valores reales, `bool` para booleanos

### Constantes
- **UPPER_SNAKE_CASE**: `GAME_TIMER_INTERVAL`, `TIGER_MAX_HITS`

---

## 🚨 Manejo de Errores

### Excepciones Comunes
1. **Resource Loading Errors**: Archivos de imagen o sonido no encontrados
2. **Null Pointer Exceptions**: Referencias no inicializadas
3. **Timer Errors**: Temporizadores no configurados correctamente
4. **Collision Detection Errors**: Elementos fuera de la escena

### Estrategias de Recuperación
1. **Graceful Degradation**: Continuar sin recursos faltantes
2. **Default Values**: Usar valores por defecto para configuraciones
3. **State Validation**: Verificar estados antes de operaciones críticas
4. **Error Logging**: Registrar errores para debugging

---

## 🔍 Debugging y Logging

### Funciones de Debug
```cpp
qDebug() << "Player position:" << player->pos();
qDebug() << "Tiger hits:" << tiger->getHitsReceived();
qDebug() << "Fruits collected:" << fruitsCollected;
```

### Estados de Debug
```cpp
// Verificar estado del jugador
if (player->onGround) {
    qDebug() << "Player is on ground";
}

// Verificar colisiones
if (collisionDetected) {
    qDebug() << "Collision detected between" << item1 << "and" << item2;
}
```

### Performance Monitoring
```cpp
// Medir tiempo de frame
QElapsedTimer frameTimer;
frameTimer.start();
// ... código del frame ...
qDebug() << "Frame time:" << frameTimer.elapsed() << "ms";
``` 