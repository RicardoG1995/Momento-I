# Arquitectura del Sistema - GameDB

## 🏗️ Visión General de la Arquitectura

GameDB sigue una arquitectura modular basada en componentes, diseñada para separar claramente las responsabilidades y facilitar el mantenimiento y extensión del código.

## 📊 Diagrama de Arquitectura

```
┌─────────────────────────────────────────────────────────────┐
│                    MainWindow (UI Layer)                    │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │   Game      │  │   Level     │  │  Physics    │         │
│  │  Manager    │  │  Manager    │  │  Engine     │         │
│  └─────────────┘  └─────────────┘  └─────────────┘         │
├─────────────────────────────────────────────────────────────┤
│                 Graphics Layer (Qt Graphics)                │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │ PlayerItem  │  │ TigerItem   │  │ FruitItem   │         │
│  └─────────────┘  └─────────────┘  └─────────────┘         │
│  ┌─────────────┐  ┌─────────────┐                          │
│  │EnergyBall   │  │  Bulma      │                          │
│  │   Item      │  │  Items      │                          │
│  └─────────────┘  └─────────────┘                          │
├─────────────────────────────────────────────────────────────┤
│                 Logic Layer (Game Objects)                  │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │   Player    │  │   Enemy     │  │  Objective  │         │
│  └─────────────┘  └─────────────┘  └─────────────┘         │
│  ┌─────────────┐  ┌─────────────┐                          │
│  │ PhysicsModel│  │  Vector2D   │                          │
│  └─────────────┘  └─────────────┘                          │
├─────────────────────────────────────────────────────────────┤
│                 Audio Layer (Qt Multimedia)                 │
│  ┌─────────────┐  ┌─────────────┐                          │
│  │ QMediaPlayer│  │ QAudioOutput│                          │
│  └─────────────┘  └─────────────┘                          │
└─────────────────────────────────────────────────────────────┘
```

## 🎯 Principios de Diseño

### 1. Separación de Responsabilidades
- **UI Layer**: Manejo de interfaz y eventos de usuario
- **Graphics Layer**: Renderizado y animaciones
- **Logic Layer**: Lógica de juego y reglas de negocio
- **Audio Layer**: Gestión de sonidos y música

### 2. Patrón Observer
- Uso de señales y slots de Qt para comunicación entre componentes
- Desacoplamiento entre la lógica de juego y la presentación

### 3. Patrón Factory
- Creación de elementos de juego a través de métodos específicos
- Gestión centralizada de recursos

## 🏛️ Estructura de Clases

### Capa de Interfaz de Usuario

#### MainWindow
```cpp
class MainWindow : public QMainWindow
```
**Responsabilidades:**
- Gestión de la ventana principal
- Coordinación entre todos los sistemas
- Manejo de eventos de teclado
- Control del flujo del juego

**Atributos Principales:**
- `QGraphicsScene* scene`: Escena gráfica principal
- `Game game`: Instancia del controlador del juego
- `QTimer* gameTimer`: Temporizador principal del juego
- `QMediaPlayer* fruitSound`: Reproductor de sonidos

**Métodos Clave:**
- `updateGame()`: Actualización principal del juego
- `setupLevel(int index)`: Configuración de niveles
- `checkCollisions()`: Detección de colisiones

### Capa de Gráficos

#### PlayerItem
```cpp
class PlayerItem : public QObject, public QGraphicsPixmapItem
```
**Responsabilidades:**
- Representación gráfica del jugador (Goku)
- Animaciones de movimiento y ataque
- Física básica (gravedad, salto)
- Gestión de sprites

**Atributos Principales:**
- `QPixmap standPixmap`: Sprite de reposo
- `QVector<QPixmap> leftAnimationFrames`: Frames de animación izquierda
- `qreal velocityY`: Velocidad vertical
- `bool onGround`: Estado de contacto con el suelo

#### TigerItem
```cpp
class TigerItem : public QObject, public QGraphicsPixmapItem
```
**Responsabilidades:**
- Representación del enemigo principal
- IA básica de movimiento oscilatorio
- Sistema de ataque parabólico
- Gestión de estados (vivo/muerto)

**Atributos Principales:**
- `qreal amplitude`: Amplitud del movimiento
- `int hitsReceived`: Contador de impactos
- `bool isAttacking`: Estado de ataque
- `QTimer* attackTimer`: Temporizador de ataque

#### EnergyBallItem
```cpp
class EnergyBallItem : public QObject, public QGraphicsPixmapItem
```
**Responsabilidades:**
- Proyectiles de energía del jugador
- Física de movimiento parabólico
- Detección de colisiones con enemigos

**Atributos Principales:**
- `qreal vx, vy`: Componentes de velocidad
- `qreal gravity`: Aceleración gravitacional

### Capa de Lógica

#### Game
```cpp
class Game
```
**Responsabilidades:**
- Controlador principal del juego
- Gestión del estado global
- Coordinación entre sistemas

**Atributos Principales:**
- `int currentLevel`: Nivel actual
- `Player player`: Instancia del jugador
- `std::vector<Enemy> enemies`: Lista de enemigos
- `PhysicsEngine physicsEngine`: Motor de físicas

#### Player
```cpp
class Player
```
**Responsabilidades:**
- Lógica del jugador
- Gestión de estadísticas
- Comportamiento básico

**Atributos Principales:**
- `std::string name`: Nombre del jugador
- `Vector2D position`: Posición en el mundo
- `Vector2D velocity`: Velocidad actual
- `int health`: Salud del jugador

#### Vector2D
```cpp
class Vector2D
```
**Responsabilidades:**
- Representación matemática de vectores 2D
- Operaciones vectoriales básicas
- Cálculos de física

**Métodos Principales:**
- `magnitude()`: Magnitud del vector
- `normalize()`: Vector normalizado
- `dot(const Vector2D& other)`: Producto punto

### Capa de Físicas

#### PhysicsEngine
```cpp
class PhysicsEngine
```
**Responsabilidades:**
- Motor de físicas principal
- Aplicación de fuerzas y movimientos
- Gestión de modelos físicos

**Atributos Principales:**
- `std::vector<PhysicsModel> models`: Modelos físicos

#### PhysicsModel
```cpp
class PhysicsModel
```
**Responsabilidades:**
- Modelo físico individual
- Fórmulas de simulación
- Parámetros de física

### Capa de Audio

#### Sistema de Sonido
**Componentes:**
- `QMediaPlayer`: Reproductor de medios
- `QAudioOutput`: Salida de audio
- Archivos de sonido: `.wav` para efectos

## 🔄 Flujo de Datos

### 1. Inicialización
```
main() → MainWindow() → setupLevels() → startLevel()
```

### 2. Bucle Principal
```
gameTimer → updateGame() → checkCollisions() → updateGraphics()
```

### 3. Eventos de Usuario
```
keyPressEvent() → PlayerItem::moveLeft/Right/Jump() → updatePosition()
```

### 4. Colisiones
```
checkCollisions() → detectCollision() → handleCollision() → updateState()
```

## 🎮 Gestión de Estados

### Estados del Juego
1. **MENU**: Menú principal
2. **PLAYING**: Jugando activamente
3. **PAUSED**: Juego pausado
4. **GAME_OVER**: Fin del juego
5. **LEVEL_COMPLETE**: Nivel completado

### Estados del Jugador
1. **IDLE**: Reposo
2. **WALKING**: Caminando
3. **JUMPING**: Saltando
4. **ATTACKING**: Atacando
5. **FALLING**: Cayendo

### Estados del Enemigo
1. **PATROLLING**: Patrullando
2. **ATTACKING**: Atacando
3. **RETREATING**: Retirándose
4. **DEAD**: Muerto

## 🔧 Patrones de Diseño Implementados

### 1. Singleton (Implícito)
- `MainWindow`: Instancia única de la ventana principal
- `Game`: Controlador único del juego

### 2. Observer
- Señales y slots de Qt para comunicación entre componentes
- `energyBallFired()`: Notificación de disparo
- `tigerShouldBeEliminated()`: Notificación de eliminación

### 3. State Machine
- Gestión de estados del juego y personajes
- Transiciones controladas entre estados

### 4. Factory Method
- Creación de elementos de juego en `MainWindow`
- `setupLevel1()`, `setupLevel2()`, `setupLevel3()`

## 📈 Escalabilidad y Mantenibilidad

### Ventajas de la Arquitectura
1. **Modularidad**: Cada componente tiene responsabilidades claras
2. **Extensibilidad**: Fácil adición de nuevos niveles y enemigos
3. **Testabilidad**: Componentes aislados para testing
4. **Reutilización**: Clases base reutilizables

### Puntos de Extensión
1. **Nuevos Enemigos**: Extender `TigerItem` o crear nuevas clases
2. **Nuevos Niveles**: Implementar en `setupLevelX()`
3. **Nuevas Mecánicas**: Añadir a `PhysicsEngine`
4. **Nuevos Sonidos**: Integrar en el sistema de audio

## 🔍 Consideraciones de Rendimiento

### Optimizaciones Implementadas
1. **Sprite Caching**: Sprites cargados una vez y reutilizados
2. **Collision Detection**: Detección eficiente de colisiones
3. **Timer Management**: Uso eficiente de temporizadores
4. **Memory Management**: Gestión automática con Qt

### Puntos de Atención
1. **Frame Rate**: Objetivo de 60 FPS
2. **Memory Usage**: Control de memoria para sprites
3. **Audio Latency**: Minimización de latencia de audio
4. **Input Responsiveness**: Respuesta rápida a input del usuario

## 🛡️ Gestión de Errores

### Estrategias de Error Handling
1. **Resource Loading**: Verificación de carga de recursos
2. **Null Pointer Checks**: Validación de punteros
3. **Exception Handling**: Manejo de excepciones en operaciones críticas
4. **Graceful Degradation**: Funcionamiento con recursos limitados

### Logging y Debugging
1. **Qt Debug Output**: Uso de `qDebug()` para logging
2. **State Validation**: Verificación de estados válidos
3. **Performance Monitoring**: Monitoreo de rendimiento
4. **Error Recovery**: Recuperación automática de errores 