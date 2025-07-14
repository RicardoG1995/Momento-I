# Sistema de Físicas - GameDB

## ⚙️ Visión General del Sistema

El sistema de físicas de GameDB implementa un motor de físicas 2D simplificado pero efectivo, diseñado específicamente para un juego de plataformas. Utiliza matemáticas vectoriales y ecuaciones de movimiento para crear una experiencia de juego realista y responsiva.

## 📐 Clase Vector2D

### Descripción
Clase matemática fundamental que representa vectores bidimensionales y proporciona operaciones vectoriales básicas.

### Implementación
```cpp
class Vector2D {
public:
    float x;
    float y;
    
    // Constructores
    Vector2D();
    Vector2D(float xVal, float yVal);
    
    // Operaciones vectoriales
    float magnitude() const;
    Vector2D normalize() const;
    float dot(const Vector2D& other) const;
    
    // Operadores
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
};
```

### Operaciones Matemáticas

#### Magnitud del Vector
```cpp
float Vector2D::magnitude() const {
    return sqrt(x * x + y * y);
}
```
**Fórmula**: `|v| = √(x² + y²)`
**Uso**: Calcular distancia entre puntos, normalizar vectores

#### Vector Normalizado
```cpp
Vector2D Vector2D::normalize() const {
    float mag = magnitude();
    if (mag > 0) {
        return Vector2D(x / mag, y / mag);
    }
    return Vector2D(0, 0);
}
```
**Fórmula**: `v̂ = v / |v|`
**Uso**: Dirección unitaria, vectores de velocidad

#### Producto Punto
```cpp
float Vector2D::dot(const Vector2D& other) const {
    return x * other.x + y * other.y;
}
```
**Fórmula**: `a · b = ax*bx + ay*by`
**Uso**: Calcular ángulos, proyecciones

## 🌍 Motor de Físicas Principal

### Clase PhysicsEngine
```cpp
class PhysicsEngine {
public:
    std::vector<PhysicsModel> models;
    void applyPhysics(void* entity);
};
```

### Funcionalidades Principales

#### Aplicación de Fuerzas
- **Gravedad**: Fuerza constante hacia abajo
- **Fricción**: Reducción de velocidad en superficies
- **Impulso**: Aplicación de fuerzas instantáneas

#### Integración Temporal
- **Método**: Euler simple
- **Fórmula**: `v(t+dt) = v(t) + a*dt`
- **Precisión**: Adecuada para 60 FPS

## 🎯 Física del Jugador

### Movimiento Horizontal

#### Aceleración y Velocidad
```cpp
// En PlayerItem::moveLeft()
qreal targetVelocity = -MOVE_SPEED;
qreal acceleration = 0.8;
velocityX = velocityX * (1 - acceleration) + targetVelocity * acceleration;
```

**Parámetros:**
- **Velocidad máxima**: 5.0 unidades/frame
- **Aceleración**: 0.8 (80% del objetivo por frame)
- **Fricción**: 0.2 (20% de pérdida por frame)

#### Fórmulas de Movimiento
- **Velocidad**: `v = v_prev * (1 - friction) + target * acceleration`
- **Posición**: `x = x_prev + v * dt`
- **Límite**: `|v| ≤ max_speed`

### Sistema de Salto

#### Física del Salto
```cpp
// En PlayerItem::jump()
if (onGround) {
    velocityY = JUMP_VELOCITY;  // -15.0
    onGround = false;
}
```

**Parámetros del Salto:**
- **Velocidad inicial**: -15.0 unidades/frame
- **Gravedad**: 0.5 unidades/frame²
- **Altura máxima**: ~225 unidades
- **Tiempo de vuelo**: ~30 frames

#### Cálculos de Salto
- **Tiempo de subida**: `t_up = |v0| / g = 15.0 / 0.5 = 30 frames`
- **Altura máxima**: `h_max = v0² / (2*g) = 225² / (2*0.5) = 225 unidades`
- **Tiempo total**: `t_total = 2 * t_up = 60 frames`

### Aplicación de Gravedad
```cpp
// En PlayerItem::advance()
if (!onGround) {
    velocityY += GRAVITY;  // 0.5
    setPos(pos().x(), pos().y() + velocityY);
}
```

**Fórmula de Gravedad:**
- **Aceleración**: `a = g = 0.5 unidades/frame²`
- **Velocidad**: `v(t) = v0 + g*t`
- **Posición**: `y(t) = y0 + v0*t + 0.5*g*t²`

## 🎯 Física de Proyectiles

### Clase EnergyBallItem

#### Inicialización del Proyectil
```cpp
EnergyBallItem::EnergyBallItem(qreal startX, qreal startY, qreal angleDeg, qreal speed) {
    // Convertir ángulo a radianes
    qreal angleRad = qDegreesToRadians(angleDeg);
    
    // Calcular componentes de velocidad
    vx = speed * cos(angleRad);
    vy = speed * sin(angleRad);
    
    // Configurar posición inicial
    setPos(startX, startY);
}
```

#### Movimiento Parabólico
```cpp
void EnergyBallItem::advance(int phase) {
    if (phase == 0) {
        // Aplicar gravedad
        vy += gravity;  // 0.3
        
        // Actualizar posición
        setPos(pos().x() + vx, pos().y() + vy);
        
        // Verificar límites de pantalla
        if (pos().y() > 600 || pos().x() < 0 || pos().x() > 800) {
            scene()->removeItem(this);
            delete this;
        }
    }
}
```

**Parámetros del Proyectil:**
- **Velocidad inicial**: Configurable (típicamente 8-12 unidades/frame)
- **Gravedad**: 0.3 unidades/frame² (menor que la del jugador)
- **Ángulo**: Configurable (-90° a +90°)
- **Vida útil**: Hasta salir de pantalla o colisionar

### Cálculos de Trayectoria

#### Ecuaciones de Movimiento
- **Posición X**: `x(t) = x0 + vx * t`
- **Posición Y**: `y(t) = y0 + vy * t + 0.5 * g * t²`
- **Velocidad X**: `vx(t) = vx0` (constante)
- **Velocidad Y**: `vy(t) = vy0 + g * t`

#### Punto de Impacto
```cpp
// Calcular tiempo hasta el suelo
qreal timeToGround = (-vy - sqrt(vy*vy + 2*gravity*pos().y())) / gravity;
qreal impactX = pos().x() + vx * timeToGround;
```

## 🐯 Física del Enemigo (Tigre)

### Movimiento Oscilatorio

#### Patrón de Movimiento
```cpp
void TigerItem::moveOscillate() {
    qreal time = frameCounter * 0.1;  // Factor de tiempo
    qreal newX = baseX + amplitude * sin(time);
    
    setPos(newX, pos().y());
    
    // Actualizar dirección para animación
    if (newX > pos().x()) {
        movingRight = true;
    } else if (newX < pos().x()) {
        movingRight = false;
    }
}
```

**Parámetros del Movimiento:**
- **Amplitud**: 100 unidades
- **Frecuencia**: 0.1 radianes por frame
- **Período**: ~63 frames (aproximadamente 1 segundo)
- **Velocidad máxima**: ~10 unidades/frame

#### Fórmula de Oscilación
- **Posición**: `x(t) = x_base + A * sin(ω*t)`
- **Velocidad**: `v(t) = A * ω * cos(ω*t)`
- **Aceleración**: `a(t) = -A * ω² * sin(ω*t)`

### Sistema de Ataque

#### Ataque Parabólico
```cpp
void TigerItem::initiateAttack() {
    if (!isAttacking && targetPlayer) {
        isAttacking = true;
        
        // Calcular dirección hacia el jugador
        qreal dx = targetPlayer->pos().x() - pos().x();
        qreal dy = targetPlayer->pos().y() - pos().y();
        
        // Configurar parámetros de salto
        qreal jumpDistance = sqrt(dx*dx + dy*dy);
        qreal jumpTime = jumpDistance / attackSpeed;
        
        // Calcular velocidad inicial
        qreal vx0 = dx / jumpTime;
        qreal vy0 = (dy - 0.5 * gravity * jumpTime * jumpTime) / jumpTime;
        
        // Aplicar movimiento
        attackVelocityX = vx0;
        attackVelocityY = vy0;
    }
}
```

**Parámetros del Ataque:**
- **Rango de detección**: 150 unidades
- **Velocidad de ataque**: 8 unidades/frame
- **Altura máxima**: -100 unidades (hacia arriba)
- **Cooldown**: 3-5 segundos

## 🔍 Sistema de Colisiones

### Detección de Colisiones

#### Método de Bounding Box
```cpp
bool checkCollision(QGraphicsItem* item1, QGraphicsItem* item2) {
    QRectF rect1 = item1->boundingRect();
    QRectF rect2 = item2->boundingRect();
    
    QRectF transformedRect1 = item1->mapRectToScene(rect1);
    QRectF transformedRect2 = item2->mapRectToScene(rect2);
    
    return transformedRect1.intersects(transformedRect2);
}
```

#### Colisión por Distancia (Radio)
```cpp
bool checkDistanceCollision(QPointF pos1, QPointF pos2, qreal radius) {
    qreal dx = pos1.x() - pos2.x();
    qreal dy = pos1.y() - pos2.y();
    qreal distance = sqrt(dx*dx + dy*dy);
    
    return distance <= radius;
}
```

### Tipos de Colisión

#### Jugador vs Fruta
```cpp
// En MainWindow::checkCollisions()
for (FruitItem* fruit : fruits) {
    if (checkDistanceCollision(player->pos(), fruit->pos(), 30.0)) {
        // Recolectar fruta
        fruitsCollected++;
        scene()->removeItem(fruit);
        fruits.removeOne(fruit);
        playFruitSound();
        delete fruit;
    }
}
```

**Parámetros:**
- **Radio de colisión**: 30 unidades
- **Efecto**: Recolección inmediata
- **Sonido**: `fruit_collect.wav`

#### Bola de Energía vs Tigre
```cpp
// En MainWindow::checkCollisions()
for (EnergyBallItem* bullet : bullets) {
    if (tiger && checkDistanceCollision(bullet->pos(), tiger->pos(), 40.0)) {
        // Dañar tigre
        tiger->receiveHit();
        scene()->removeItem(bullet);
        bullets.removeOne(bullet);
        delete bullet;
        
        if (tiger->getHitsReceived() >= 5) {
            defeatTiger();
        }
    }
}
```

**Parámetros:**
- **Radio de colisión**: 40 unidades
- **Daño**: +1 hit al tigre
- **Destrucción**: Bola eliminada

#### Jugador vs Bulma
```cpp
// En MainWindow::checkCollisions()
if (bulma && !bulmaRescatada) {
    if (checkDistanceCollision(player->pos(), bulma->pos(), 60.0)) {
        // Rescatar Bulma
        bulmaRescatada = true;
        bulma->setPixmap(QPixmap(":/Img/Bulma/Bulma_Salvar.png"));
        // Nivel completado
    }
}
```

**Parámetros:**
- **Radio de colisión**: 60 unidades
- **Efecto**: Rescate exitoso
- **Trigger**: Victoria del nivel

### Optimización de Colisiones

#### Spatial Partitioning
```cpp
// Dividir pantalla en sectores
const int GRID_SIZE = 100;
int gridX = pos().x() / GRID_SIZE;
int gridY = pos().y() / GRID_SIZE;

// Solo verificar colisiones en sectores adyacentes
for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
        checkSectorCollisions(gridX + dx, gridY + dy);
    }
}
```

#### Broad Phase vs Narrow Phase
1. **Broad Phase**: Detección aproximada por sectores
2. **Narrow Phase**: Detección precisa por bounding box

## 📊 Constantes Físicas

### Configuración Global
```cpp
// Gravedad
const qreal GRAVITY = 0.5;                    // unidades/frame²
const qreal PROJECTILE_GRAVITY = 0.3;         // unidades/frame²

// Movimiento del jugador
const qreal MOVE_SPEED = 5.0;                 // unidades/frame
const qreal JUMP_VELOCITY = -15.0;            // unidades/frame
const qreal ACCELERATION = 0.8;               // factor de aceleración
const qreal FRICTION = 0.2;                   // factor de fricción

// Proyectiles
const qreal PROJECTILE_SPEED = 10.0;          // unidades/frame
const qreal PROJECTILE_LIFETIME = 120;        // frames

// Enemigos
const qreal TIGER_AMPLITUDE = 100.0;          // unidades
const qreal TIGER_FREQUENCY = 0.1;            // radianes/frame
const qreal TIGER_ATTACK_RANGE = 150.0;       // unidades
```

### Ajustes por Nivel

#### Nivel 1 (Frutas)
- **Gravedad**: Estándar (0.5)
- **Fricción**: Normal (0.2)
- **Velocidad de movimiento**: Estándar (5.0)

#### Nivel 2 (Tigre)
- **Gravedad**: Estándar (0.5)
- **Velocidad del tigre**: Variable según dificultad
- **Rango de ataque**: 150 unidades

#### Nivel 3 (Balas)
- **Gravedad**: Reducida para proyectiles (0.3)
- **Velocidad de balas**: Configurable
- **Frecuencia de spawn**: Cada 2 segundos

## 🔧 Debugging y Visualización

### Visualización de Físicas
```cpp
// Dibujar vectores de velocidad
void drawVelocityVector(QPainter* painter, QPointF pos, Vector2D velocity) {
    painter->setPen(QPen(Qt::red, 2));
    painter->drawLine(pos, pos + QPointF(velocity.x, velocity.y));
}

// Dibujar bounding boxes
void drawBoundingBox(QPainter* painter, QGraphicsItem* item) {
    painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
    painter->drawRect(item->mapRectToScene(item->boundingRect()));
}
```

### Logging de Físicas
```cpp
// Log de posiciones y velocidades
qDebug() << "Player pos:" << player->pos() << "vel:" << player->velocityY;
qDebug() << "Tiger pos:" << tiger->pos() << "hits:" << tiger->getHitsReceived();
qDebug() << "Bullet count:" << bullets.size();
```

### Métricas de Rendimiento
```cpp
// Medir tiempo de cálculo de físicas
QElapsedTimer physicsTimer;
physicsTimer.start();

// ... cálculos de físicas ...

qDebug() << "Physics calculation time:" << physicsTimer.elapsed() << "ms";
```

## 🎯 Optimizaciones

### Optimizaciones Implementadas

#### Culling de Objetos
- **Frustum Culling**: Solo procesar objetos visibles
- **Distance Culling**: Ignorar objetos muy lejanos
- **State Culling**: No procesar objetos inactivos

#### Caching de Cálculos
```cpp
// Cache de valores trigonométricos
static qreal sinCache[360];
static qreal cosCache[360];
static bool cacheInitialized = false;

void initializeTrigCache() {
    if (!cacheInitialized) {
        for (int i = 0; i < 360; i++) {
            sinCache[i] = sin(qDegreesToRadians(i));
            cosCache[i] = cos(qDegreesToRadians(i));
        }
        cacheInitialized = true;
    }
}
```

#### Batch Processing
```cpp
// Procesar múltiples objetos en lotes
void processPhysicsBatch(const QList<QGraphicsItem*>& items) {
    for (QGraphicsItem* item : items) {
        if (item->isVisible()) {
            applyPhysics(item);
        }
    }
}
```

### Optimizaciones Futuras

#### Motor de Físicas Avanzado
- **Verlet Integration**: Mayor precisión temporal
- **Constraint Solver**: Para objetos conectados
- **Soft Body Physics**: Para efectos especiales

#### GPU Acceleration
- **Compute Shaders**: Para cálculos masivos
- **Particle Systems**: Para efectos visuales
- **Collision Detection**: Paralelización

## 📈 Escalabilidad

### Adición de Nuevas Físicas

#### Nuevos Tipos de Movimiento
1. **Movimiento Circular**: Para enemigos orbitales
2. **Movimiento Elíptico**: Para patrones complejos
3. **Movimiento Aleatorio**: Para comportamiento impredecible

#### Nuevos Tipos de Colisión
1. **Colisión Elástica**: Para rebotes realistas
2. **Colisión Inelástica**: Para absorción de energía
3. **Colisión Compuesta**: Para objetos complejos

### Configuración Dinámica
```cpp
// Sistema de configuración de físicas
struct PhysicsConfig {
    qreal gravity;
    qreal friction;
    qreal bounce;
    qreal airResistance;
};

// Configuración por nivel
std::map<int, PhysicsConfig> levelPhysicsConfigs;
``` 