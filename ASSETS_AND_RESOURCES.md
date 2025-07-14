# Assets y Recursos - GameDB

## 📁 Estructura de Directorios

```
GameDB-main/
├── Img/
│   ├── Goku/
│   │   ├── goku_stand.png
│   │   ├── goku_right.png
│   │   ├── goku_right1.png
│   │   ├── goku_right2.png
│   │   ├── goku_jump.png
│   │   ├── goku_left.png
│   │   ├── goku_left1.png
│   │   ├── goku_left2.png
│   │   └── Goku_Ataca.png
│   ├── Enemigos/
│   │   ├── Tigre.png
│   │   ├── Tigre_Derecha.png
│   │   ├── Tigre_Camina1.png
│   │   ├── Tigre_Camina2.png
│   │   ├── Tigre_Camina1_Derecha.png
│   │   ├── Tigre_Camina2_Derecha.png
│   │   ├── Tigre_Ataca.png
│   │   └── Tigre_Herido.png
│   ├── Bulma/
│   │   ├── Bulma.png
│   │   └── Bulma_Salvar.png
│   ├── Elementos/
│   │   ├── Fruta.png
│   │   └── Bala.png
│   └── Mapas/
│       └── 1/
│           ├── Inicio.jpg
│           ├── Fondo.jpg
│           └── Piso.jpg
├── sounds/
│   ├── fruit_collect.wav
│   └── energy_ball.wav
└── resources.qrc
```

## 🖼️ Assets Gráficos

### Sprites del Jugador (Goku)

#### Sprite de Reposo
- **Archivo**: `Img/Goku/goku_stand.png`
- **Dimensiones**: 64x64 píxeles
- **Formato**: PNG con transparencia
- **Uso**: Estado IDLE del jugador
- **Carga**: En constructor de `PlayerItem`

#### Sprites de Movimiento Derecha
- **Archivos**: 
  - `Img/Goku/goku_right.png` (frame principal)
  - `Img/Goku/goku_right1.png` (frame 1)
  - `Img/Goku/goku_right2.png` (frame 2)
- **Dimensiones**: 64x64 píxeles cada uno
- **Animación**: 3 frames para caminata
- **Velocidad**: 1 frame cada 3 movimientos
- **Uso**: Estado WALKING hacia la derecha

#### Sprites de Movimiento Izquierda
- **Archivos**:
  - `Img/Goku/goku_left.png` (frame principal)
  - `Img/Goku/goku_left1.png` (frame 1)
  - `Img/Goku/goku_left2.png` (frame 2)
- **Dimensiones**: 64x64 píxeles cada uno
- **Animación**: 3 frames para caminata
- **Uso**: Estado WALKING hacia la izquierda

#### Sprite de Salto
- **Archivo**: `Img/Goku/goku_jump.png`
- **Dimensiones**: 64x64 píxeles
- **Uso**: Estados JUMPING y FALLING
- **Física**: Aplicada independientemente del sprite

#### Sprite de Ataque
- **Archivo**: `Img/Goku/Goku_Ataca.png`
- **Dimensiones**: 64x64 píxeles
- **Uso**: Estado ATTACKING
- **Duración**: 500ms
- **Trigger**: Generación de `EnergyBallItem`

### Sprites del Enemigo (Tigre)

#### Sprite Normal
- **Archivo**: `Img/Enemigos/Tigre.png`
- **Dimensiones**: 80x60 píxeles
- **Uso**: Estado normal del tigre
- **Comportamiento**: Movimiento oscilatorio

#### Sprites de Caminata
- **Archivos**:
  - `Img/Enemigos/Tigre_Camina1.png`
  - `Img/Enemigos/Tigre_Camina2.png`
- **Dimensiones**: 80x60 píxeles cada uno
- **Animación**: 2 frames alternados
- **Velocidad**: 5 frames por movimiento

#### Sprites de Caminata Derecha
- **Archivos**:
  - `Img/Enemigos/Tigre_Camina1_Derecha.png`
  - `Img/Enemigos/Tigre_Camina2_Derecha.png`
- **Dimensiones**: 80x60 píxeles cada uno
- **Uso**: Movimiento hacia la derecha

#### Sprite de Ataque
- **Archivo**: `Img/Enemigos/Tigre_Ataca.png`
- **Dimensiones**: 80x60 píxeles
- **Uso**: Estado ATTACKING del tigre
- **Trigger**: Proximidad del jugador

#### Sprite Herido
- **Archivo**: `Img/Enemigos/Tigre_Herido.png`
- **Dimensiones**: 80x60 píxeles
- **Uso**: Estado después de recibir daño
- **Duración**: 500ms

### Sprites de Bulma

#### Bulma Normal
- **Archivo**: `Img/Bulma/Bulma.png`
- **Dimensiones**: 48x48 píxeles
- **Uso**: Estado "necesita rescate"
- **Posición**: Fija en el nivel 2

#### Bulma Rescatada
- **Archivo**: `Img/Bulma/Bulma_Salvar.png`
- **Dimensiones**: 48x48 píxeles
- **Uso**: Estado "rescatada"
- **Trigger**: Contacto con el jugador

### Elementos del Juego

#### Fruta
- **Archivo**: `Img/Elementos/Fruta.png`
- **Dimensiones**: 32x32 píxeles
- **Uso**: Objeto recolectable
- **Colisión**: Radio de 30 unidades
- **Sonido**: `fruit_collect.wav`

#### Bala de Energía
- **Archivo**: `Img/Elementos/Bala.png`
- **Dimensiones**: 24x24 píxeles
- **Uso**: Proyectil del jugador
- **Física**: Movimiento parabólico
- **Sonido**: `energy_ball.wav`

### Fondos y Mapas

#### Pantalla de Inicio
- **Archivo**: `Img/Mapas/1/Inicio.jpg`
- **Dimensiones**: 800x600 píxeles
- **Formato**: JPEG
- **Uso**: Menú principal del juego

#### Fondo del Nivel
- **Archivo**: `Img/Mapas/1/Fondo.jpg`
- **Dimensiones**: 800x600 píxeles
- **Formato**: JPEG
- **Uso**: Fondo de todos los niveles

#### Plataforma/Suelo
- **Archivo**: `Img/Mapas/1/Piso.jpg`
- **Dimensiones**: 800x100 píxeles
- **Formato**: JPEG
- **Uso**: Plataformas y suelo del juego

## 🔊 Assets de Audio

### Efectos de Sonido

#### Sonido de Recolección de Fruta
- **Archivo**: `sounds/fruit_collect.wav`
- **Formato**: WAV (sin compresión)
- **Frecuencia**: 44.1 kHz
- **Canales**: Mono
- **Duración**: ~0.5 segundos
- **Volumen**: 50%
- **Trigger**: Colisión jugador-fruta
- **Carga**: En constructor de `MainWindow`

#### Sonido de Disparo de Bola de Energía
- **Archivo**: `sounds/energy_ball.wav`
- **Formato**: WAV (sin compresión)
- **Frecuencia**: 44.1 kHz
- **Canales**: Mono
- **Duración**: ~1 segundo
- **Volumen**: 70%
- **Trigger**: Presionar tecla de ataque
- **Carga**: En constructor de `PlayerItem`

## 📦 Gestión de Recursos

### Archivo de Recursos (resources.qrc)

```xml
<RCC>
  <qresource prefix="/">
    <!-- Mapas -->
    <file>Img/Mapas/1/Inicio.jpg</file>
    <file>Img/Mapas/1/Fondo.jpg</file>
    <file>Img/Mapas/1/Piso.jpg</file>
    
    <!-- Sprites de Goku -->
    <file>Img/Goku/goku_stand.png</file>
    <file>Img/Goku/goku_right.png</file>
    <file>Img/Goku/goku_right1.png</file>
    <file>Img/Goku/goku_right2.png</file>
    <file>Img/Goku/goku_jump.png</file>
    <file>Img/Goku/goku_left.png</file>
    <file>Img/Goku/goku_left1.png</file>
    <file>Img/Goku/goku_left2.png</file>
    <file>Img/Goku/Goku_Ataca.png</file>
    
    <!-- Elementos -->
    <file>Img/Elementos/Fruta.png</file>
    <file>Img/Elementos/Bala.png</file>
    
    <!-- Enemigos -->
    <file>Img/Enemigos/Tigre.png</file>
    <file>Img/Enemigos/Tigre_Derecha.png</file>
    <file>Img/Enemigos/Tigre_Camina1.png</file>
    <file>Img/Enemigos/Tigre_Camina2.png</file>
    <file>Img/Enemigos/Tigre_Camina1_Derecha.png</file>
    <file>Img/Enemigos/Tigre_Camina2_Derecha.png</file>
    <file>Img/Enemigos/Tigre_Ataca.png</file>
    <file>Img/Enemigos/Tigre_Herido.png</file>
    
    <!-- Bulma -->
    <file>Img/Bulma/Bulma.png</file>
    <file>Img/Bulma/Bulma_Salvar.png</file>
  </qresource>
  
  <qresource prefix="/">
    <!-- Sonidos -->
    <file>sounds/fruit_collect.wav</file>
    <file>sounds/energy_ball.wav</file>
  </qresource>
</RCC>
```

### Carga de Recursos

#### Carga de Imágenes
```cpp
// En PlayerItem constructor
standPixmap = QPixmap(":/Img/Goku/goku_stand.png");
jumpPixmap = QPixmap(":/Img/Goku/goku_jump.png");
attackPixmap = QPixmap(":/Img/Goku/Goku_Ataca.png");

// Carga de frames de animación
leftAnimationFrames.append(QPixmap(":/Img/Goku/goku_left.png"));
leftAnimationFrames.append(QPixmap(":/Img/Goku/goku_left1.png"));
leftAnimationFrames.append(QPixmap(":/Img/Goku/goku_left2.png"));
```

#### Carga de Sonidos
```cpp
// En MainWindow constructor
fruitSound = new QMediaPlayer();
fruitSound->setSource(QUrl("qrc:/sounds/fruit_collect.wav"));

shootSound = new QMediaPlayer();
shootSound->setSource(QUrl("qrc:/sounds/energy_ball.wav"));
```

## 🎨 Especificaciones Técnicas

### Formatos de Imagen

#### PNG (Sprites)
- **Transparencia**: Soporte completo para canal alpha
- **Compresión**: Sin pérdida
- **Paleta**: RGB 24-bit
- **Optimización**: Para sprites pequeños

#### JPEG (Fondos)
- **Compresión**: Con pérdida (calidad 85%)
- **Paleta**: RGB 24-bit
- **Uso**: Fondos y mapas grandes

### Formatos de Audio

#### WAV
- **Compresión**: Sin compresión (PCM)
- **Frecuencia**: 44.1 kHz
- **Resolución**: 16-bit
- **Canales**: Mono (efectos de sonido)

### Optimización de Recursos

#### Caching de Sprites
```cpp
// Los sprites se cargan una vez y se reutilizan
QPixmap cachedSprite = QPixmap(":/path/to/sprite.png");
// Uso múltiple sin recarga
```

#### Gestión de Memoria
- **Carga bajo demanda**: Solo cuando se necesita
- **Liberación automática**: Gestión de Qt
- **Pool de recursos**: Reutilización de objetos

## 🔧 Configuración de Assets

### Configuración de Sprites

#### Dimensiones Estándar
- **Jugador**: 64x64 píxeles
- **Enemigos**: 80x60 píxeles
- **Elementos**: 32x32 píxeles
- **UI**: Variables según necesidad

#### Escalado
```cpp
// Escalado automático según resolución
QPixmap scaledSprite = originalSprite.scaled(
    targetWidth, 
    targetHeight, 
    Qt::KeepAspectRatio, 
    Qt::SmoothTransformation
);
```

### Configuración de Audio

#### Volúmenes
```cpp
// Configuración de volumen por efecto
fruitSound->setVolume(50);  // 50%
shootSound->setVolume(70);  // 70%
```

#### Latencia
- **Objetivo**: < 50ms
- **Buffer**: 512 samples
- **Frecuencia**: 44.1 kHz

## 📊 Métricas de Recursos

### Tamaños de Archivos
- **Sprites totales**: ~25 archivos
- **Tamaño promedio sprite**: 2-5 KB
- **Tamaño total sprites**: ~100 KB
- **Sonidos**: 2 archivos (~300 KB total)
- **Fondos**: 3 archivos (~500 KB total)

### Uso de Memoria
- **Sprites en memoria**: ~200 KB
- **Audio buffers**: ~50 KB
- **Total estimado**: ~250 KB

### Rendimiento
- **Tiempo de carga**: < 1 segundo
- **Frame rate**: 60 FPS objetivo
- **Latencia de audio**: < 50ms

## 🛠️ Herramientas de Desarrollo

### Herramientas Recomendadas

#### Edición de Imágenes
- **GIMP**: Edición de sprites
- **Photoshop**: Edición profesional
- **Aseprite**: Animación de sprites
- **Piskel**: Editor online gratuito

#### Edición de Audio
- **Audacity**: Edición de efectos de sonido
- **LMMS**: Creación de música
- **FL Studio**: Producción profesional

#### Optimización
- **TinyPNG**: Compresión de imágenes
- **ImageOptim**: Optimización automática
- **FFmpeg**: Conversión de audio

### Workflow de Desarrollo

#### Creación de Sprites
1. **Diseño**: Crear sprite base
2. **Animación**: Generar frames adicionales
3. **Optimización**: Reducir tamaño y colores
4. **Testing**: Verificar en el juego
5. **Integración**: Añadir al resources.qrc

#### Creación de Sonidos
1. **Grabación**: Capturar efecto base
2. **Edición**: Limpiar y ajustar
3. **Normalización**: Ajustar volumen
4. **Exportación**: Convertir a WAV
5. **Testing**: Verificar en el juego

## 🔍 Debugging de Recursos

### Problemas Comunes

#### Imágenes No Cargadas
```cpp
// Verificar carga de imagen
QPixmap testPixmap(":/path/to/image.png");
if (testPixmap.isNull()) {
    qDebug() << "Error: No se pudo cargar la imagen";
}
```

#### Sonidos No Reproducidos
```cpp
// Verificar estado del reproductor
if (fruitSound->mediaStatus() == QMediaPlayer::NoMedia) {
    qDebug() << "Error: No hay archivo de audio cargado";
}
```

#### Recursos Faltantes
```cpp
// Verificar archivo de recursos
QFile resourceFile(":/path/to/resource");
if (!resourceFile.exists()) {
    qDebug() << "Error: Recurso no encontrado";
}
```

### Logging de Recursos
```cpp
// Log de carga de recursos
qDebug() << "Cargando sprite:" << spritePath;
qDebug() << "Tamaño del sprite:" << pixmap.size();
qDebug() << "Memoria utilizada:" << pixmap.sizeInBytes();
```

## 📈 Escalabilidad

### Adición de Nuevos Assets

#### Nuevos Sprites
1. Crear archivo de imagen
2. Añadir al resources.qrc
3. Cargar en la clase correspondiente
4. Implementar lógica de uso

#### Nuevos Sonidos
1. Crear archivo de audio
2. Añadir al resources.qrc
3. Crear QMediaPlayer
4. Conectar a eventos del juego

### Optimización Futura

#### Compresión de Texturas
- **Formato**: Considerar WebP para fondos
- **Atlas**: Combinar sprites en texturas
- **LOD**: Niveles de detalle para fondos

#### Streaming de Audio
- **Formato**: OGG para música de fondo
- **Compresión**: MP3 para efectos
- **Caching**: Precarga de audio crítico 