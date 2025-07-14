# Mecánicas de Juego - GameDB

## 🎮 Controles del Jugador

### Controles Básicos

#### Movimiento Horizontal
- **Tecla A** o **Flecha Izquierda**: Mover a la izquierda
- **Tecla D** o **Flecha Derecha**: Mover a la derecha

**Comportamiento:**
- Movimiento suave con aceleración y desaceleración
- Animación de caminata con múltiples frames
- Cambio automático de sprite según dirección

#### Salto
- **Tecla W** o **Flecha Arriba** o **Barra Espaciadora**: Saltar

**Mecánicas de Salto:**
- **Velocidad inicial**: -15.0 unidades
- **Gravedad**: 0.5 unidades por frame
- **Altura máxima**: ~225 unidades
- **Detección de suelo**: Automática al tocar plataformas

#### Ataque
- **Tecla S** o **Flecha Abajo**: Disparar bola de energía

**Características del Ataque:**
- **Munición limitada**: 5 bolas por nivel
- **Velocidad del proyectil**: Configurable por nivel
- **Ángulo de disparo**: Hacia la dirección que mira el jugador
- **Cooldown**: Sin cooldown, limitado por munición

### Estados del Jugador

#### Estado de Reposo (IDLE)
- **Sprite**: `goku_stand.png`
- **Transiciones**: A cualquier movimiento
- **Duración**: Indefinida

#### Estado de Caminata (WALKING)
- **Sprites**: `goku_left.png`, `goku_right.png` + frames de animación
- **Velocidad**: 5.0 unidades por frame
- **Animación**: 3 frames por dirección
- **Transiciones**: A salto, ataque o reposo

#### Estado de Salto (JUMPING)
- **Sprite**: `goku_jump.png`
- **Física**: Aplicación de gravedad
- **Duración**: Hasta tocar el suelo
- **Transiciones**: A caída o aterrizaje

#### Estado de Ataque (ATTACKING)
- **Sprite**: `Goku_Ataca.png`
- **Duración**: 500ms (configurable)
- **Efectos**: Genera `EnergyBallItem`
- **Transiciones**: A reposo automáticamente

#### Estado de Caída (FALLING)
- **Sprite**: `goku_jump.png` (mismo que salto)
- **Física**: Gravedad aplicada
- **Duración**: Hasta tocar el suelo
- **Transiciones**: A aterrizaje

## 🎯 Sistema de Niveles

### Nivel 1: Recolección de Frutas

#### Objetivo Principal
Recolectar todas las frutas disponibles en el nivel antes de que se agote el tiempo.

#### Configuración
- **Tiempo límite**: 30 segundos
- **Frutas disponibles**: 5-8 frutas (configurable)
- **Enemigos**: Ninguno
- **Obstáculos**: Plataformas básicas

#### Mecánicas Específicas
1. **Spawn de Frutas**: Posiciones fijas predefinidas
2. **Colisión de Recolección**: Radio de 30 unidades
3. **Contador de Frutas**: Display en tiempo real
4. **Sonido de Recolección**: `fruit_collect.wav`

#### Condiciones de Victoria
- Recolectar todas las frutas antes del tiempo límite

#### Condiciones de Derrota
- Agotar el tiempo sin recolectar todas las frutas

### Nivel 2: Rescate de Bulma

#### Objetivo Principal
Llegar a Bulma y rescatarla, evitando o derrotando al tigre enemigo.

#### Configuración
- **Tiempo límite**: Sin límite de tiempo
- **Enemigo principal**: Tigre con IA
- **Objetivo**: Bulma en posición fija
- **Obstáculos**: Plataformas y el tigre

#### Mecánicas Específicas

##### Comportamiento del Tigre
- **Movimiento**: Oscilatorio en forma de seno
- **Amplitud**: 100 unidades
- **Velocidad**: Configurable
- **Estados**: Patrullando, Atacando, Herido, Muerto

##### Sistema de Combate
- **Vida del tigre**: 5 impactos
- **Rango de ataque**: 150 unidades
- **Tipo de ataque**: Salto parabólico hacia el jugador
- **Cooldown de ataque**: 3-5 segundos

##### Rescate de Bulma
- **Posición inicial**: Estado "necesita rescate"
- **Trigger de rescate**: Contacto del jugador
- **Cambio de sprite**: A estado "rescatada"
- **Condición de victoria**: Bulma rescatada

#### Condiciones de Victoria
- Tocar a Bulma (rescate exitoso)

#### Condiciones de Derrota
- Ser golpeado por el tigre múltiples veces (opcional)

### Nivel 3: Supervivencia

#### Objetivo Principal
Sobrevivir a las balas enemigas durante el mayor tiempo posible.

#### Configuración
- **Tiempo límite**: Sin límite específico
- **Enemigos**: Balas automáticas
- **Obstáculos**: Plataformas y balas enemigas
- **Munición**: Limitada (5 bolas)

#### Mecánicas Específicas

##### Sistema de Balas Enemigas
- **Spawn automático**: Cada 2 segundos
- **Velocidad**: Configurable por bala
- **Dirección**: Hacia el jugador
- **Patrón**: Variable (directo, parabólico, etc.)

##### Gestión de Munición
- **Munición inicial**: 5 bolas
- **Recarga**: No disponible en este nivel
- **Uso estratégico**: Destruir balas enemigas críticas

##### Física de Balas
- **Movimiento**: Parabólico con gravedad
- **Colisiones**: Con jugador, plataformas y otras balas
- **Destrucción**: Al impactar o salir de pantalla

#### Condiciones de Victoria
- Sobrevivir durante un tiempo mínimo (configurable)

#### Condiciones de Derrota
- Ser golpeado por una bala enemiga

## ⚡ Sistema de Físicas

### Gravedad
- **Valor**: 0.5 unidades por frame
- **Aplicación**: A todos los objetos con masa
- **Excepciones**: Elementos estáticos (plataformas)

### Movimiento Parabólico
- **Fórmula**: `y = y0 + v0*t + 0.5*g*t²`
- **Aplicación**: Saltos, proyectiles, ataques del tigre
- **Variables**:
  - `y0`: Posición inicial Y
  - `v0`: Velocidad inicial Y
  - `g`: Aceleración gravitacional
  - `t`: Tiempo transcurrido

### Colisiones

#### Detección de Colisiones
- **Método**: Bounding box rectangular
- **Precisión**: Pixel-perfect para elementos críticos
- **Optimización**: Solo elementos cercanos

#### Tipos de Colisión

##### Jugador vs Fruta
- **Radio de detección**: 30 unidades
- **Efecto**: Recolección de fruta
- **Sonido**: `fruit_collect.wav`
- **Puntos**: +1 al contador

##### Jugador vs Tigre
- **Radio de detección**: 50 unidades
- **Efecto**: Daño al jugador (si implementado)
- **Estado**: Tigre en modo ataque

##### Bola de Energía vs Tigre
- **Radio de detección**: 40 unidades
- **Efecto**: Daño al tigre (+1 hit)
- **Destrucción**: Bola eliminada
- **Sonido**: Efecto de impacto

##### Jugador vs Bulma
- **Radio de detección**: 60 unidades
- **Efecto**: Rescate exitoso
- **Estado**: Bulma rescatada
- **Victoria**: Nivel completado

##### Jugador vs Bala Enemiga
- **Radio de detección**: 35 unidades
- **Efecto**: Daño al jugador
- **Destrucción**: Bala eliminada
- **Derrota**: Nivel fallido

## 🎵 Sistema de Audio

### Efectos de Sonido

#### Recolección de Fruta
- **Archivo**: `sounds/fruit_collect.wav`
- **Volumen**: 50%
- **Trigger**: Colisión jugador-fruta
- **Duración**: ~0.5 segundos

#### Disparo de Bola de Energía
- **Archivo**: `sounds/energy_ball.wav`
- **Volumen**: 70%
- **Trigger**: Presionar tecla de ataque
- **Duración**: ~1 segundo

### Configuración de Audio
- **Formato**: WAV (sin compresión)
- **Frecuencia**: 44.1 kHz
- **Canales**: Mono/Estéreo
- **Latencia**: < 50ms

## 🎨 Sistema de Animaciones

### Animación de Caminata del Jugador

#### Frames de Animación
- **Derecha**: `goku_right.png`, `goku_right1.png`, `goku_right2.png`
- **Izquierda**: `goku_left.png`, `goku_left1.png`, `goku_left2.png`
- **Velocidad**: 1 frame cada 3 movimientos
- **Loop**: Continuo mientras se mueve

### Animación del Tigre

#### Estados de Animación
- **Normal**: `Tigre.png`
- **Caminata**: `Tigre_Camina1.png`, `Tigre_Camina2.png`
- **Ataque**: `Tigre_Ataca.png`
- **Herido**: `Tigre_Herido.png`

#### Patrón de Movimiento
- **Oscilación**: Movimiento sinusoidal
- **Cambio de dirección**: Inversión automática
- **Velocidad de animación**: 5 frames por movimiento

### Animación de Bulma

#### Estados
- **Normal**: `Bulma.png` (necesita rescate)
- **Rescatada**: `Bulma_Salvar.png` (rescate exitoso)

## 📊 Sistema de Puntuación

### Puntos por Fruta
- **Valor**: 10 puntos por fruta
- **Bonus de tiempo**: +5 puntos por segundo restante
- **Multiplicador**: 1.5x si se completa en menos de 20 segundos

### Puntuación del Nivel 2
- **Base**: 100 puntos por completar
- **Bonus de salud**: +20 puntos por cada hit restante del tigre
- **Tiempo**: +1 punto por segundo de supervivencia

### Puntuación del Nivel 3
- **Base**: 50 puntos por completar
- **Bonus de supervivencia**: +10 puntos por segundo
- **Destrucción de balas**: +5 puntos por bala destruida

## 🔧 Configuración de Dificultad

### Nivel Fácil
- **Velocidad del tigre**: 0.8x
- **Frecuencia de balas**: 0.7x
- **Tiempo límite**: +10 segundos
- **Munición extra**: +2 bolas

### Nivel Normal
- **Configuración estándar**: Valores por defecto
- **Balance**: Diseñado para jugadores promedio

### Nivel Difícil
- **Velocidad del tigre**: 1.3x
- **Frecuencia de balas**: 1.5x
- **Tiempo límite**: -5 segundos
- **Munición reducida**: -1 bola

## 🎮 Estados del Juego

### Estado MENU
- **Pantalla**: Menú principal
- **Controles**: Solo navegación de menú
- **Transición**: Al presionar "Jugar"

### Estado PLAYING
- **Pantalla**: Nivel activo
- **Controles**: Todos los controles del jugador
- **Actualización**: Lógica de juego activa

### Estado PAUSED
- **Pantalla**: Nivel con overlay de pausa
- **Controles**: Solo salir de pausa
- **Actualización**: Pausada

### Estado GAME_OVER
- **Pantalla**: Pantalla de fin de juego
- **Controles**: Reiniciar o volver al menú
- **Datos**: Puntuación final mostrada

### Estado LEVEL_COMPLETE
- **Pantalla**: Pantalla de victoria del nivel
- **Controles**: Continuar al siguiente nivel
- **Datos**: Puntuación del nivel mostrada

## 🔄 Flujo de Juego

### Secuencia de Inicio
1. **Inicialización**: Carga de recursos y configuración
2. **Menú Principal**: Selección de nivel o configuración
3. **Carga de Nivel**: Setup del nivel seleccionado
4. **Inicio de Juego**: Activación de temporizadores y lógica

### Bucle Principal
1. **Input Processing**: Lectura de controles del usuario
2. **Game Logic Update**: Actualización de lógica del juego
3. **Physics Update**: Aplicación de físicas
4. **Collision Detection**: Detección y resolución de colisiones
5. **Animation Update**: Actualización de animaciones
6. **Audio Update**: Reproducción de efectos de sonido
7. **Render**: Dibujado de la escena

### Secuencia de Fin
1. **Condition Check**: Verificación de condiciones de victoria/derrota
2. **Score Calculation**: Cálculo de puntuación final
3. **State Transition**: Transición al siguiente estado
4. **Cleanup**: Limpieza de recursos del nivel

## 🎯 Objetivos de Diseño

### Jugabilidad
- **Accesibilidad**: Controles intuitivos y responsivos
- **Progresión**: Dificultad incremental entre niveles
- **Feedback**: Respuesta visual y auditiva inmediata
- **Balance**: Mecánicas equilibradas y justas

### Experiencia de Usuario
- **Fluidez**: 60 FPS constante
- **Responsividad**: Input lag < 16ms
- **Claridad**: Información clara y visible
- **Inmersión**: Audio y visuales cohesivos

### Técnico
- **Rendimiento**: Uso eficiente de recursos
- **Estabilidad**: Sin crashes o bugs críticos
- **Escalabilidad**: Fácil adición de contenido
- **Mantenibilidad**: Código limpio y documentado 