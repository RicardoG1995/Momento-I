# Guía de Desarrollo - GameDB

## 👨‍💻 Introducción para Desarrolladores

Esta guía está diseñada para desarrolladores que quieren contribuir al proyecto GameDB. Incluye estándares de código, mejores prácticas, flujo de trabajo y herramientas recomendadas.

## 🏗️ Estructura del Proyecto

### Organización de Archivos
```
GameDB-main/
├── src/                    # Código fuente principal
│   ├── core/              # Lógica del juego
│   ├── graphics/          # Sistema de gráficos
│   ├── physics/           # Motor de físicas
│   ├── audio/             # Sistema de audio
│   └── ui/                # Interfaz de usuario
├── assets/                # Recursos del juego
│   ├── images/            # Sprites y texturas
│   ├── sounds/            # Efectos de sonido
│   └── levels/            # Datos de niveles
├── docs/                  # Documentación
├── tests/                 # Tests unitarios
├── build/                 # Archivos de compilación
└── scripts/               # Scripts de automatización
```

### Convenciones de Nomenclatura

#### Archivos
- **Headers**: `PascalCase.h` (ej: `PlayerItem.h`)
- **Sources**: `PascalCase.cpp` (ej: `PlayerItem.cpp`)
- **Resources**: `snake_case.ext` (ej: `goku_stand.png`)

#### Clases
- **PascalCase**: `PlayerItem`, `TigerItem`, `EnergyBallItem`
- **Prefijos descriptivos**: `QGraphicsPixmapItem` para elementos Qt

#### Métodos y Variables
- **camelCase**: `moveLeft()`, `velocityY`, `isAttacking`
- **Constantes**: `UPPER_SNAKE_CASE`: `GAME_TIMER_INTERVAL`

## 📝 Estándares de Código

### Estilo de Código

#### Indentación y Formato
```cpp
// Usar 4 espacios para indentación
class PlayerItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    PlayerItem();
    ~PlayerItem();

    // Métodos públicos primero
    void moveLeft();
    void moveRight();
    void jump();

private:
    // Atributos privados después
    QPixmap standPixmap;
    qreal velocityY;
    bool onGround;
};
```

#### Comentarios
```cpp
/**
 * @brief Representa al jugador (Goku) en el juego
 * 
 * Esta clase maneja la lógica de movimiento, animación
 * y física del personaje principal.
 */
class PlayerItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    /**
     * @brief Constructor que inicializa el jugador
     * 
     * Carga los sprites necesarios y configura el estado inicial.
     */
    PlayerItem();

    /**
     * @brief Mueve el jugador hacia la izquierda
     * 
     * Aplica física de movimiento y actualiza la animación.
     * La velocidad se limita a MOVE_SPEED.
     */
    void moveLeft();
};
```

#### Manejo de Errores
```cpp
// Usar excepciones para errores críticos
void loadSprite(const QString& path) {
    QPixmap sprite(path);
    if (sprite.isNull()) {
        throw std::runtime_error("No se pudo cargar el sprite: " + path.toStdString());
    }
    setPixmap(sprite);
}

// Usar valores de retorno para errores no críticos
bool tryLoadSprite(const QString& path) {
    QPixmap sprite(path);
    if (sprite.isNull()) {
        qWarning() << "No se pudo cargar el sprite:" << path;
        return false;
    }
    setPixmap(sprite);
    return true;
}
```

### Patrones de Diseño

#### Singleton (Para Game Manager)
```cpp
class GameManager {
private:
    static GameManager* instance;
    GameManager() = default;

public:
    static GameManager* getInstance() {
        if (instance == nullptr) {
            instance = new GameManager();
        }
        return instance;
    }

    void initialize();
    void update();
    void cleanup();
};
```

#### Observer (Para eventos del juego)
```cpp
class GameEvent {
public:
    enum Type { COLLISION, SCORE_CHANGE, LEVEL_COMPLETE };
    Type type;
    QVariant data;
};

class GameObserver {
public:
    virtual void onGameEvent(const GameEvent& event) = 0;
};

class GameSubject {
private:
    QList<GameObserver*> observers;

public:
    void addObserver(GameObserver* observer) {
        observers.append(observer);
    }

    void notifyObservers(const GameEvent& event) {
        for (GameObserver* observer : observers) {
            observer->onGameEvent(event);
        }
    }
};
```

#### Factory (Para creación de objetos)
```cpp
class GameObjectFactory {
public:
    static PlayerItem* createPlayer(const QPointF& position) {
        PlayerItem* player = new PlayerItem();
        player->setPos(position);
        return player;
    }

    static TigerItem* createTiger(const QPointF& position) {
        TigerItem* tiger = new TigerItem();
        tiger->setPos(position);
        return tiger;
    }

    static FruitItem* createFruit(const QPointF& position) {
        return new FruitItem(position.x(), position.y());
    }
};
```

## 🔧 Herramientas de Desarrollo

### IDE Recomendado: Qt Creator

#### Configuración
1. **Abrir Proyecto**: File → Open File or Project → GameDB.pro
2. **Configurar Kit**: 
   - Compiler: MSVC 2019 64-bit (Windows) / GCC (Linux)
   - Qt version: 6.5.0
   - Debugger: GDB/CDB
3. **Configurar Build**: 
   - Build directory: `build/`
   - Shadow build: Enabled

#### Configuración de Debug
```qmake
# En GameDB.pro
CONFIG += debug
QMAKE_CXXFLAGS_DEBUG += -g -O0 -Wall -Wextra
```

#### Configuración de Release
```qmake
# En GameDB.pro
CONFIG += release
QMAKE_CXXFLAGS_RELEASE += -O2 -DNDEBUG
```

### Herramientas de Análisis

#### Clang-Tidy
```bash
# Configurar clang-tidy
# En .clang-tidy
---
Checks: '-*,readability-*,performance-*,modernize-*'
WarningsAsErrors: ''
HeaderFilterRegex: ''
AnalyzeTemporaryDtors: false
FormatStyle: none
CheckOptions:
  - key: readability-identifier-naming.ClassCase
    value: CamelCase
  - key: readability-identifier-naming.FunctionCase
    value: camelBack
```

#### Valgrind (Linux/macOS)
```bash
# Detectar memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./GameDB

# Detectar errores de memoria
valgrind --tool=memcheck ./GameDB
```

#### AddressSanitizer
```bash
# Compilar con AddressSanitizer
qmake GameDB.pro CONFIG+=sanitizer
make

# Ejecutar
./GameDB
```

### Herramientas de Testing

#### Framework de Testing: Google Test
```cpp
// tests/player_test.cpp
#include <gtest/gtest.h>
#include "PlayerItem.h"

class PlayerItemTest : public ::testing::Test {
protected:
    void SetUp() override {
        player = new PlayerItem();
    }

    void TearDown() override {
        delete player;
    }

    PlayerItem* player;
};

TEST_F(PlayerItemTest, InitialPosition) {
    EXPECT_EQ(player->pos(), QPointF(0, 0));
}

TEST_F(PlayerItemTest, Movement) {
    QPointF initialPos = player->pos();
    player->moveLeft();
    EXPECT_LT(player->pos().x(), initialPos.x());
}
```

#### Configuración de Tests
```qmake
# tests/tests.pro
QT += testlib
CONFIG += testcase

TARGET = GameDBTests
TEMPLATE = app

SOURCES += \
    main.cpp \
    player_test.cpp \
    tiger_test.cpp \
    physics_test.cpp

HEADERS += \
    player_test.h \
    tiger_test.h \
    physics_test.h
```

## 🔄 Flujo de Trabajo

### Git Workflow

#### Configuración Inicial
```bash
# Clonar repositorio
git clone https://github.com/username/GameDB.git
cd GameDB

# Configurar usuario
git config user.name "Tu Nombre"
git config user.email "tu.email@ejemplo.com"

# Crear rama de desarrollo
git checkout -b develop
```

#### Flujo de Desarrollo
```bash
# 1. Crear rama para feature
git checkout -b feature/nueva-mecanica

# 2. Hacer cambios
# ... editar archivos ...

# 3. Añadir cambios
git add .

# 4. Commit con mensaje descriptivo
git commit -m "feat: añadir sistema de power-ups

- Implementar clase PowerUpItem
- Añadir lógica de recolección
- Integrar con sistema de puntuación"

# 5. Push a rama remota
git push origin feature/nueva-mecanica

# 6. Crear Pull Request
# Ir a GitHub/GitLab y crear PR
```

#### Convenciones de Commits
```bash
# Formato: tipo(alcance): descripción

# Tipos:
feat:     nueva funcionalidad
fix:      corrección de bug
docs:     documentación
style:    formato, punto y coma, etc.
refactor: refactorización de código
test:     añadir tests
chore:    tareas de mantenimiento

# Ejemplos:
feat(player): añadir animación de salto
fix(collision): corregir detección de colisiones
docs(api): actualizar documentación de PlayerItem
style: formatear código según estándares
```

### Code Review

#### Checklist de Review
- [ ] **Funcionalidad**: ¿El código hace lo que debe?
- [ ] **Estilo**: ¿Sigue las convenciones del proyecto?
- [ ] **Performance**: ¿Es eficiente?
- [ ] **Seguridad**: ¿Hay vulnerabilidades?
- [ ] **Tests**: ¿Hay tests para la nueva funcionalidad?
- [ ] **Documentación**: ¿Está documentado?

#### Proceso de Review
```bash
# 1. Crear Pull Request
# 2. Asignar reviewers
# 3. Revisar código
# 4. Añadir comentarios
# 5. Aprobar o solicitar cambios
# 6. Merge a develop
```

## 🧪 Testing

### Testing Unitario

#### Estructura de Tests
```cpp
// tests/player_test.cpp
#include <gtest/gtest.h>
#include <QApplication>
#include "PlayerItem.h"

class PlayerItemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Inicializar QApplication para tests
        int argc = 1;
        char* argv[] = {"test"};
        app = new QApplication(argc, argv);
        
        player = new PlayerItem();
    }

    void TearDown() override {
        delete player;
        delete app;
    }

    QApplication* app;
    PlayerItem* player;
};

TEST_F(PlayerItemTest, Constructor) {
    EXPECT_EQ(player->pos(), QPointF(0, 0));
    EXPECT_EQ(player->velocityY, 0.0);
    EXPECT_TRUE(player->onGround);
}

TEST_F(PlayerItemTest, Movement) {
    QPointF initialPos = player->pos();
    
    player->moveLeft();
    EXPECT_LT(player->pos().x(), initialPos.x());
    
    player->moveRight();
    EXPECT_GT(player->pos().x(), initialPos.x());
}

TEST_F(PlayerItemTest, Jump) {
    EXPECT_TRUE(player->onGround);
    
    player->jump();
    EXPECT_FALSE(player->onGround);
    EXPECT_LT(player->velocityY, 0.0);
}
```

#### Ejecutar Tests
```bash
# Compilar tests
cd tests
qmake tests.pro
make

# Ejecutar tests
./GameDBTests

# Con coverage
gcov -r . GameDBTests
```

### Testing de Integración

#### Tests de Nivel
```cpp
// tests/level_integration_test.cpp
class LevelIntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        mainWindow = new MainWindow();
        mainWindow->setupLevel1();
    }

    void TearDown() override {
        delete mainWindow;
    }

    MainWindow* mainWindow;
};

TEST_F(LevelIntegrationTest, Level1Completion) {
    // Simular recolección de todas las frutas
    for (FruitItem* fruit : mainWindow->getFruits()) {
        mainWindow->simulateFruitCollection(fruit);
    }
    
    EXPECT_TRUE(mainWindow->isLevelComplete());
    EXPECT_EQ(mainWindow->getFruitsCollected(), mainWindow->getTotalFruits());
}
```

### Testing de Performance

#### Benchmarks
```cpp
// tests/performance_test.cpp
#include <benchmark/benchmark.h>

static void BM_CollisionDetection(benchmark::State& state) {
    MainWindow mainWindow;
    mainWindow.setupLevel3(); // Nivel con más objetos
    
    for (auto _ : state) {
        mainWindow.checkCollisions();
    }
}

BENCHMARK(BM_CollisionDetection);

static void BM_PhysicsUpdate(benchmark::State& state) {
    PlayerItem player;
    
    for (auto _ : state) {
        player.advance(0);
    }
}

BENCHMARK(BM_PhysicsUpdate);
```

## 🐛 Debugging

### Debugging con Qt Creator

#### Configuración de Debug
1. **Build en modo Debug**: Build → Build Project "GameDB"
2. **Configurar breakpoints**: Click en el margen izquierdo
3. **Iniciar debug**: Debug → Start Debugging
4. **Inspeccionar variables**: Variables panel

#### Logging
```cpp
// Usar qDebug para logging
#include <QDebug>

void PlayerItem::moveLeft() {
    qDebug() << "Player moving left from position:" << pos();
    
    // ... lógica de movimiento ...
    
    qDebug() << "Player new position:" << pos();
}

// Logging condicional
#ifdef QT_DEBUG
    qDebug() << "Debug info:" << debugData;
#endif
```

### Debugging de Gráficos

#### Visualización de Bounding Boxes
```cpp
void PlayerItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    
    // Dibujar bounding box en modo debug
    if (QApplication::applicationName() == "GameDB_debug") {
        painter->setPen(QPen(Qt::red, 2, Qt::DashLine));
        painter->drawRect(boundingRect());
    }
}
```

#### Debug de Físicas
```cpp
void PlayerItem::advance(int phase) {
    if (phase == 0) {
        // Aplicar física
        if (!onGround) {
            velocityY += GRAVITY;
            setPos(pos().x(), pos().y() + velocityY);
        }
        
        // Debug info
        qDebug() << "Player physics - pos:" << pos() 
                 << "velY:" << velocityY 
                 << "onGround:" << onGround;
    }
}
```

## 📊 Análisis de Código

### Métricas de Código

#### Complejidad Ciclomática
```cpp
// Usar herramientas como cppcheck
cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck-report.xml

// O usar clang-tidy
clang-tidy *.cpp -checks=* -- -std=c++17
```

#### Coverage de Código
```bash
# Compilar con coverage
qmake GameDB.pro CONFIG+=coverage
make

# Ejecutar tests
./GameDBTests

# Generar reporte
gcov -r . GameDBTests
genhtml *.gcov -o coverage_report
```

### Análisis Estático

#### Configuración de SonarQube
```yaml
# sonar-project.properties
sonar.projectKey=GameDB
sonar.projectName=GameDB
sonar.projectVersion=1.0.0

sonar.sources=src
sonar.tests=tests
sonar.cfamily.build-wrapper-output=build-wrapper-output

sonar.cfamily.gcov.reportsPath=.
sonar.coverage.exclusions=tests/*
```

## 🔄 CI/CD

### GitHub Actions para Desarrollo

#### Workflow de Desarrollo
```yaml
# .github/workflows/development.yml
name: Development Checks

on:
  pull_request:
    branches: [ develop, main ]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Qt
      uses: jurplel/install-qt-action@v3
      with:
        version: '6.5.0'
        modules: qtcharts qtmultimedia
    
    - name: Build
      run: |
        qmake GameDB.pro
        make
    
    - name: Run Tests
      run: |
        cd tests
        qmake tests.pro
        make
        ./GameDBTests
    
    - name: Static Analysis
      run: |
        cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck-report.xml
    
    - name: Upload Test Results
      uses: actions/upload-artifact@v3
      with:
        name: test-results
        path: |
          cppcheck-report.xml
          test-results.xml
```

### Pre-commit Hooks

#### Configuración de Hooks
```bash
# .git/hooks/pre-commit
#!/bin/bash

echo "Running pre-commit checks..."

# Formatear código
clang-format -i *.cpp *.h

# Verificar estilo
cppcheck --enable=style --error-exitcode=1 .

# Ejecutar tests básicos
cd tests && make && ./GameDBTests

if [ $? -ne 0 ]; then
    echo "Pre-commit checks failed!"
    exit 1
fi

echo "Pre-commit checks passed!"
```

## 📚 Recursos de Aprendizaje

### Documentación Qt
- **Qt Documentation**: https://doc.qt.io/
- **Qt Examples**: https://doc.qt.io/qt-6/examples.html
- **Qt Tutorials**: https://doc.qt.io/qt-6/tutorials.html

### C++ Moderno
- **C++ Core Guidelines**: https://isocpp.github.io/CppCoreGuidelines/
- **C++ Reference**: https://en.cppreference.com/
- **Effective Modern C++**: Scott Meyers

### Game Development
- **Game Programming Patterns**: Robert Nystrom
- **Real-Time Rendering**: Tomas Akenine-Möller
- **Game Engine Architecture**: Jason Gregory

### Herramientas
- **Qt Creator Manual**: https://doc.qt.io/qtcreator/
- **CMake Documentation**: https://cmake.org/documentation/
- **Git Documentation**: https://git-scm.com/doc

## 🤝 Contribución

### Cómo Contribuir

#### 1. Fork del Repositorio
```bash
# Fork en GitHub
# Clonar tu fork
git clone https://github.com/tu-usuario/GameDB.git
cd GameDB

# Añadir upstream
git remote add upstream https://github.com/original/GameDB.git
```

#### 2. Crear Feature Branch
```bash
git checkout -b feature/tu-feature
```

#### 3. Desarrollar
```bash
# Hacer cambios
# Escribir tests
# Actualizar documentación
```

#### 4. Commit y Push
```bash
git add .
git commit -m "feat: descripción de tu feature"
git push origin feature/tu-feature
```

#### 5. Crear Pull Request
- Ir a GitHub
- Crear Pull Request
- Describir cambios
- Asignar reviewers

### Guías de Contribución

#### Reportar Bugs
```markdown
**Descripción del Bug**
Descripción clara y concisa del problema.

**Pasos para Reproducir**
1. Ir a '...'
2. Hacer click en '...'
3. Ver error

**Comportamiento Esperado**
Descripción de lo que debería pasar.

**Screenshots**
Si aplica, añadir screenshots.

**Información del Sistema**
- OS: Windows 10
- Qt Version: 6.5.0
- Compiler: MSVC 2019

**Información Adicional**
Cualquier otra información relevante.
```

#### Solicitar Features
```markdown
**Descripción de la Feature**
Descripción clara de la funcionalidad deseada.

**Problema que Resuelve**
Explicar por qué esta feature es necesaria.

**Solución Propuesta**
Descripción de la implementación sugerida.

**Alternativas Consideradas**
Otras soluciones que se consideraron.

**Información Adicional**
Screenshots, mockups, etc.
```

## 📋 Checklist de Desarrollo

### Antes de Empezar
- [ ] Leer documentación del proyecto
- [ ] Configurar entorno de desarrollo
- [ ] Entender arquitectura del código
- [ ] Revisar issues existentes

### Durante el Desarrollo
- [ ] Seguir estándares de código
- [ ] Escribir tests para nueva funcionalidad
- [ ] Documentar cambios
- [ ] Commit frecuentemente con mensajes descriptivos

### Antes de Submit
- [ ] Ejecutar todos los tests
- [ ] Verificar que no hay warnings
- [ ] Actualizar documentación
- [ ] Revisar cambios con git diff
- [ ] Crear Pull Request descriptivo 