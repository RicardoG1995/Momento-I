# Sistema de Audio - GameDB

## 🔊 Visión General del Sistema

El sistema de audio de GameDB utiliza Qt Multimedia para proporcionar efectos de sonido inmersivos y responsivos. El sistema está diseñado para ser eficiente, con baja latencia y gestión automática de recursos.

## 🎵 Arquitectura del Sistema

### Componentes Principales

```
┌─────────────────────────────────────────────────────────┐
│                    Audio System                         │
├─────────────────────────────────────────────────────────┤
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐     │
│  │ QMediaPlayer│  │QAudioOutput │  │ Audio Cache │     │
│  └─────────────┘  └─────────────┘  └─────────────┘     │
├─────────────────────────────────────────────────────────┤
│                 Sound Effects                           │
│  ┌─────────────┐  ┌─────────────┐                      │
│  │ Fruit Sound │  │ Shoot Sound │                      │
│  └─────────────┘  └─────────────┘                      │
├─────────────────────────────────────────────────────────┤
│                 Event Triggers                          │
│  ┌─────────────┐  ┌─────────────┐                      │
│  │ Collision   │  │ User Input  │                      │
│  └─────────────┘  └─────────────┘                      │
└─────────────────────────────────────────────────────────┘
```

### Dependencias Qt
```cpp
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
```

## 🎧 Efectos de Sonido

### Sonido de Recolección de Fruta

#### Configuración
- **Archivo**: `sounds/fruit_collect.wav`
- **Formato**: WAV (PCM sin compresión)
- **Frecuencia**: 44.1 kHz
- **Resolución**: 16-bit
- **Canales**: Mono
- **Duración**: ~0.5 segundos
- **Tamaño**: ~35 KB

#### Implementación
```cpp
// En MainWindow constructor
fruitSound = new QMediaPlayer();
fruitSound->setSource(QUrl("qrc:/sounds/fruit_collect.wav"));

QAudioOutput* fruitAudioOutput = new QAudioOutput();
fruitAudioOutput->setVolume(0.5);  // 50%
fruitSound->setAudioOutput(fruitAudioOutput);
```

#### Reproducción
```cpp
void MainWindow::playFruitSound() {
    if (fruitSound->mediaStatus() == QMediaPlayer::LoadedMedia) {
        fruitSound->setPosition(0);  // Reiniciar al inicio
        fruitSound->play();
    }
}
```

#### Trigger
```cpp
// En checkCollisions() cuando se recolecta una fruta
if (checkDistanceCollision(player->pos(), fruit->pos(), 30.0)) {
    fruitsCollected++;
    playFruitSound();  // Reproducir sonido
    // ... resto de la lógica
}
```

### Sonido de Disparo de Bola de Energía

#### Configuración
- **Archivo**: `sounds/energy_ball.wav`
- **Formato**: WAV (PCM sin compresión)
- **Frecuencia**: 44.1 kHz
- **Resolución**: 16-bit
- **Canales**: Mono
- **Duración**: ~1 segundo
- **Tamaño**: ~266 KB

#### Implementación
```cpp
// En PlayerItem constructor
shootSound = new QMediaPlayer();
shootSound->setSource(QUrl("qrc:/sounds/energy_ball.wav"));

shootAudioOutput = new QAudioOutput();
shootAudioOutput->setVolume(0.7);  // 70%
shootSound->setAudioOutput(shootAudioOutput);
```

#### Reproducción
```cpp
void PlayerItem::shootEnergyBall() {
    if (!isAttacking && bulletsFired < maxBullets) {
        isAttacking = true;
        
        // Reproducir sonido
        if (shootSound->mediaStatus() == QMediaPlayer::LoadedMedia) {
            shootSound->setPosition(0);
            shootSound->play();
        }
        
        // Crear bola de energía
        EnergyBallItem* ball = new EnergyBallItem(pos().x(), pos().y(), 0, 10);
        emit energyBallFired(ball);
        
        // Programar fin de animación
        QTimer::singleShot(500, this, &PlayerItem::finishAttackAnimation);
    }
}
```

#### Señal de Sonido
```cpp
// En PlayerItem.h
signals:
    void playShootSound();

// En MainWindow
connect(player, &PlayerItem::playShootSound, this, &MainWindow::playShootSound);
```

## 🎛️ Gestión de Audio

### Configuración de Volumen

#### Volúmenes por Efecto
```cpp
// Configuración de volúmenes
const qreal FRUIT_SOUND_VOLUME = 0.5;    // 50%
const qreal SHOOT_SOUND_VOLUME = 0.7;    // 70%
const qreal MASTER_VOLUME = 1.0;         // 100%

// Aplicar volúmenes
fruitAudioOutput->setVolume(FRUIT_SOUND_VOLUME * MASTER_VOLUME);
shootAudioOutput->setVolume(SHOOT_SOUND_VOLUME * MASTER_VOLUME);
```

#### Control de Volumen Dinámico
```cpp
void MainWindow::setMasterVolume(qreal volume) {
    masterVolume = qBound(0.0, volume, 1.0);  // Limitar entre 0 y 1
    
    // Actualizar todos los reproductores
    if (fruitSound && fruitSound->audioOutput()) {
        fruitSound->audioOutput()->setVolume(FRUIT_SOUND_VOLUME * masterVolume);
    }
    
    if (shootSound && shootSound->audioOutput()) {
        shootSound->audioOutput()->setVolume(SHOOT_SOUND_VOLUME * masterVolume);
    }
}
```

### Gestión de Recursos

#### Inicialización de Audio
```cpp
void MainWindow::initializeAudio() {
    // Crear reproductores
    fruitSound = new QMediaPlayer(this);
    shootSound = new QMediaPlayer(this);
    
    // Crear salidas de audio
    QAudioOutput* fruitOutput = new QAudioOutput(this);
    QAudioOutput* shootOutput = new QAudioOutput(this);
    
    // Configurar volúmenes
    fruitOutput->setVolume(0.5);
    shootOutput->setVolume(0.7);
    
    // Conectar reproductores con salidas
    fruitSound->setAudioOutput(fruitOutput);
    shootSound->setAudioOutput(shootOutput);
    
    // Cargar archivos
    fruitSound->setSource(QUrl("qrc:/sounds/fruit_collect.wav"));
    shootSound->setSource(QUrl("qrc:/sounds/energy_ball.wav"));
}
```

#### Limpieza de Recursos
```cpp
MainWindow::~MainWindow() {
    // Detener reproducción
    if (fruitSound) {
        fruitSound->stop();
    }
    if (shootSound) {
        shootSound->stop();
    }
    
    // Los objetos se eliminan automáticamente por parent-child
}
```

## 📊 Especificaciones Técnicas

### Formatos de Audio Soportados

#### WAV (Waveform Audio File Format)
- **Compresión**: Sin compresión (PCM)
- **Frecuencias**: 44.1 kHz, 48 kHz
- **Resoluciones**: 16-bit, 24-bit
- **Canales**: Mono, Estéreo
- **Ventajas**: Sin pérdida, compatibilidad universal
- **Desventajas**: Tamaño de archivo grande

#### Configuración Recomendada
```cpp
// Configuración óptima para efectos de sonido
const QString AUDIO_FORMAT = "WAV";
const int SAMPLE_RATE = 44100;      // 44.1 kHz
const int BIT_DEPTH = 16;           // 16-bit
const int CHANNELS = 1;             // Mono
const qreal DURATION = 0.5;         // 500ms máximo
```

### Latencia y Rendimiento

#### Objetivos de Latencia
- **Latencia objetivo**: < 50ms
- **Buffer size**: 512 samples
- **Sample rate**: 44.1 kHz
- **Frame time**: ~11.6ms por buffer

#### Configuración de Bajo Latencia
```cpp
void configureLowLatency(QAudioOutput* output) {
    // Configurar para baja latencia
    output->setVolume(1.0);
    
    // Configuraciones específicas de Qt
    QAudioDevice device = output->device();
    if (device.isValid()) {
        // Intentar configurar buffer pequeño
        // (Nota: Qt no expone directamente estas configuraciones)
    }
}
```

## 🔧 Debugging y Monitoreo

### Verificación de Estado de Audio

#### Verificación de Carga
```cpp
void MainWindow::verifyAudioSetup() {
    // Verificar fruit sound
    if (fruitSound->mediaStatus() == QMediaPlayer::NoMedia) {
        qDebug() << "Error: Fruit sound not loaded";
    } else if (fruitSound->mediaStatus() == QMediaPlayer::LoadedMedia) {
        qDebug() << "Fruit sound loaded successfully";
    }
    
    // Verificar shoot sound
    if (shootSound->mediaStatus() == QMediaPlayer::NoMedia) {
        qDebug() << "Error: Shoot sound not loaded";
    } else if (shootSound->mediaStatus() == QMediaPlayer::LoadedMedia) {
        qDebug() << "Shoot sound loaded successfully";
    }
}
```

#### Monitoreo de Reproducción
```cpp
void MainWindow::monitorAudioPlayback() {
    // Conectar señales para monitoreo
    connect(fruitSound, &QMediaPlayer::playingChanged, [this](bool playing) {
        if (playing) {
            qDebug() << "Fruit sound started playing";
        } else {
            qDebug() << "Fruit sound stopped playing";
        }
    });
    
    connect(shootSound, &QMediaPlayer::playingChanged, [this](bool playing) {
        if (playing) {
            qDebug() << "Shoot sound started playing";
        } else {
            qDebug() << "Shoot sound stopped playing";
        }
    });
}
```

### Logging de Audio
```cpp
void MainWindow::logAudioEvent(const QString& event, const QString& sound) {
    qDebug() << "Audio Event:" << event << "Sound:" << sound 
             << "Time:" << QTime::currentTime().toString("hh:mm:ss.zzz");
}

// Uso
logAudioEvent("Play", "fruit_collect");
logAudioEvent("Stop", "energy_ball");
```

## 🎮 Integración con el Juego

### Eventos de Audio

#### Eventos de Colisión
```cpp
void MainWindow::checkCollisions() {
    // Colisión jugador-fruta
    for (FruitItem* fruit : fruits) {
        if (checkDistanceCollision(player->pos(), fruit->pos(), 30.0)) {
            playFruitSound();  // Trigger de audio
            // ... resto de la lógica
        }
    }
    
    // Colisión bola-tigre
    for (EnergyBallItem* bullet : bullets) {
        if (tiger && checkDistanceCollision(bullet->pos(), tiger->pos(), 40.0)) {
            // Aquí se podría añadir un sonido de impacto
            // ... lógica de daño
        }
    }
}
```

#### Eventos de Input
```cpp
void MainWindow::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        case Qt::Key_S:
        case Qt::Key_Down:
            // El sonido se reproduce en PlayerItem::shootEnergyBall()
            player->shootEnergyBall();
            break;
        // ... otros casos
    }
}
```

### Sincronización de Audio

#### Sincronización con Animaciones
```cpp
void PlayerItem::shootEnergyBall() {
    if (!isAttacking) {
        isAttacking = true;
        
        // Reproducir sonido inmediatamente
        if (shootSound->mediaStatus() == QMediaPlayer::LoadedMedia) {
            shootSound->setPosition(0);
            shootSound->play();
        }
        
        // Cambiar sprite de ataque
        setPixmap(attackPixmap);
        
        // Crear proyectil
        EnergyBallItem* ball = new EnergyBallItem(pos().x(), pos().y(), 0, 10);
        emit energyBallFired(ball);
        
        // Programar fin de animación
        QTimer::singleShot(500, this, &PlayerItem::finishAttackAnimation);
    }
}
```

## 📈 Optimización de Audio

### Optimizaciones Implementadas

#### Precarga de Audio
```cpp
void MainWindow::preloadAudio() {
    // Precargar todos los sonidos al inicio
    fruitSound->setSource(QUrl("qrc:/sounds/fruit_collect.wav"));
    shootSound->setSource(QUrl("qrc:/sounds/energy_ball.wav"));
    
    // Esperar a que se carguen
    while (fruitSound->mediaStatus() != QMediaPlayer::LoadedMedia ||
           shootSound->mediaStatus() != QMediaPlayer::LoadedMedia) {
        QApplication::processEvents();
    }
}
```

#### Pool de Reproductores
```cpp
class AudioPool {
private:
    QList<QMediaPlayer*> availablePlayers;
    QList<QMediaPlayer*> activePlayers;
    
public:
    QMediaPlayer* getPlayer() {
        if (availablePlayers.isEmpty()) {
            QMediaPlayer* player = new QMediaPlayer();
            player->setSource(QUrl("qrc:/sounds/fruit_collect.wav"));
            availablePlayers.append(player);
        }
        
        QMediaPlayer* player = availablePlayers.takeFirst();
        activePlayers.append(player);
        return player;
    }
    
    void releasePlayer(QMediaPlayer* player) {
        if (activePlayers.removeOne(player)) {
            player->stop();
            player->setPosition(0);
            availablePlayers.append(player);
        }
    }
};
```

### Optimizaciones Futuras

#### Compresión de Audio
- **Formato**: OGG Vorbis para efectos largos
- **Compresión**: MP3 para música de fondo
- **Calidad**: 128 kbps para efectos, 192 kbps para música

#### Streaming de Audio
```cpp
// Para música de fondo larga
QMediaPlayer* backgroundMusic = new QMediaPlayer();
backgroundMusic->setSource(QUrl("qrc:/music/background.ogg"));
backgroundMusic->setLoops(QMediaPlayer::Infinite);
```

## 🛠️ Herramientas de Desarrollo

### Herramientas de Edición de Audio

#### Audacity (Recomendado)
- **Uso**: Edición de efectos de sonido
- **Formato de exportación**: WAV 44.1kHz 16-bit Mono
- **Efectos útiles**: Normalización, Fade In/Out, Noise Reduction

#### LMMS
- **Uso**: Creación de música de fondo
- **Formato de exportación**: OGG Vorbis
- **Características**: Sintetizadores, efectos, secuenciador

#### FFmpeg
- **Uso**: Conversión y optimización de audio
- **Comandos útiles**:
```bash
# Convertir a WAV optimizado
ffmpeg -i input.mp3 -ar 44100 -ac 1 -acodec pcm_s16le output.wav

# Comprimir a OGG
ffmpeg -i input.wav -c:a libvorbis -b:a 128k output.ogg
```

### Workflow de Desarrollo de Audio

#### Creación de Efectos de Sonido
1. **Grabación**: Capturar sonido base
2. **Edición**: Limpiar y ajustar en Audacity
3. **Normalización**: Ajustar volumen a -12 dB
4. **Fade**: Añadir fade in/out de 10ms
5. **Exportación**: WAV 44.1kHz 16-bit Mono
6. **Testing**: Verificar en el juego

#### Optimización de Archivos
1. **Análisis**: Identificar frecuencias innecesarias
2. **Filtrado**: Aplicar filtros de paso alto/bajo
3. **Compresión**: Aplicar compresión dinámica
4. **Limitación**: Evitar clipping
5. **Exportación**: Formato final optimizado

## 🔍 Troubleshooting

### Problemas Comunes

#### Audio No Reproduce
```cpp
void debugAudioIssue(QMediaPlayer* player, const QString& name) {
    qDebug() << "Debugging" << name << "audio:";
    qDebug() << "  Media Status:" << player->mediaStatus();
    qDebug() << "  Playback State:" << player->playbackState();
    qDebug() << "  Error:" << player->error();
    qDebug() << "  Error String:" << player->errorString();
    
    if (player->audioOutput()) {
        qDebug() << "  Volume:" << player->audioOutput()->volume();
        qDebug() << "  Device:" << player->audioOutput()->device().description();
    }
}
```

#### Latencia Alta
```cpp
void optimizeLatency() {
    // Verificar configuración del sistema
    QAudioDevice defaultDevice = QMediaDevices::defaultAudioOutput();
    qDebug() << "Default device:" << defaultDevice.description();
    qDebug() << "Supported sample rates:" << defaultDevice.supportedSampleRates();
    
    // Configurar buffer pequeño
    // (Nota: Qt no expone directamente estas configuraciones)
}
```

#### Archivos No Encontrados
```cpp
void verifyAudioFiles() {
    QFile fruitFile(":/sounds/fruit_collect.wav");
    QFile shootFile(":/sounds/energy_ball.wav");
    
    if (!fruitFile.exists()) {
        qDebug() << "Error: fruit_collect.wav not found in resources";
    }
    
    if (!shootFile.exists()) {
        qDebug() << "Error: energy_ball.wav not found in resources";
    }
}
```

### Soluciones Recomendadas

#### Para Audio No Reproduce
1. Verificar que los archivos están en resources.qrc
2. Comprobar que Qt Multimedia está habilitado
3. Verificar permisos de audio del sistema
4. Revisar configuración de dispositivos de audio

#### Para Latencia Alta
1. Usar archivos de audio pequeños (< 1MB)
2. Configurar sample rate de 44.1kHz
3. Usar formato WAV sin compresión
4. Verificar configuración del sistema operativo

#### Para Archivos No Encontrados
1. Verificar rutas en resources.qrc
2. Comprobar que los archivos existen
3. Reconstruir el proyecto
4. Verificar permisos de archivos 