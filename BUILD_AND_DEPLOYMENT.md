# Compilación y Despliegue - GameDB

## 🛠️ Requisitos del Sistema

### Requisitos Mínimos
- **Sistema Operativo**: Windows 10, macOS 10.14+, Ubuntu 18.04+
- **Procesador**: Intel Core i3 o AMD equivalente
- **Memoria RAM**: 4 GB
- **Espacio en Disco**: 500 MB
- **Tarjeta Gráfica**: Compatible con OpenGL 3.3

### Requisitos Recomendados
- **Sistema Operativo**: Windows 11, macOS 12+, Ubuntu 20.04+
- **Procesador**: Intel Core i5 o AMD Ryzen 5
- **Memoria RAM**: 8 GB
- **Espacio en Disco**: 1 GB
- **Tarjeta Gráfica**: Compatible con OpenGL 4.0

### Dependencias de Desarrollo

#### Qt Framework
- **Versión**: Qt 5.12+ o Qt 6.x
- **Módulos**: Core, Gui, Widgets, Multimedia
- **Descarga**: https://www.qt.io/download

#### Compiladores Soportados
- **Windows**: MSVC 2019+, MinGW-w64
- **macOS**: Xcode 12+, Clang
- **Linux**: GCC 7+, Clang 10+

#### Herramientas Adicionales
- **CMake**: 3.16+ (opcional)
- **Git**: Para control de versiones
- **IDE**: Qt Creator, Visual Studio, CLion

## 🔧 Configuración del Entorno

### Instalación de Qt

#### Windows
```bash
# Descargar Qt Online Installer
# Ejecutar: qt-unified-windows-x86-online.exe

# Seleccionar componentes:
# - Qt 6.5.0 (o versión estable más reciente)
# - MSVC 2019 64-bit
# - Qt Creator
# - Qt Debug Information Files
```

#### macOS
```bash
# Usando Homebrew
brew install qt

# O descargar Qt Online Installer
# Ejecutar: qt-unified-mac-x64-online.dmg
```

#### Linux (Ubuntu/Debian)
```bash
# Instalar dependencias
sudo apt update
sudo apt install build-essential cmake git

# Instalar Qt
sudo apt install qt6-base-dev qt6-multimedia-dev qt6-tools-dev

# O usar Qt Online Installer
wget https://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
chmod +x qt-unified-linux-x64-online.run
./qt-unified-linux-x64-online.run
```

### Configuración de Variables de Entorno

#### Windows
```batch
# Añadir al PATH
set PATH=%PATH%;C:\Qt\6.5.0\msvc2019_64\bin
set PATH=%PATH%;C:\Qt\Tools\CMake_64\bin

# Variables de entorno
set QTDIR=C:\Qt\6.5.0\msvc2019_64
set QT_QPA_PLATFORM_PLUGIN_PATH=%QTDIR%\plugins
```

#### macOS/Linux
```bash
# Añadir al ~/.bashrc o ~/.zshrc
export PATH="/usr/local/Qt-6.5.0/bin:$PATH"
export QTDIR="/usr/local/Qt-6.5.0"
export QT_QPA_PLATFORM_PLUGIN_PATH="$QTDIR/plugins"
```

## 📦 Compilación del Proyecto

### Método 1: Usando qmake (Recomendado)

#### Configuración del Proyecto
```bash
# Navegar al directorio del proyecto
cd GameDB-main

# Generar archivos de proyecto
qmake GameDB.pro

# Compilar (Windows)
nmake
# O
mingw32-make

# Compilar (macOS/Linux)
make
```

#### Archivo .pro Detallado
```qmake
# GameDB.pro
QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameDB
TEMPLATE = app

# Configuración de compilación
CONFIG += c++17
CONFIG += release

# Flags de compilación
QMAKE_CXXFLAGS += -O2
QMAKE_CXXFLAGS += -Wall -Wextra

# Archivos fuente
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Game.cpp \
    Player.cpp \
    Enemy.cpp \
    PhysicsEngine.cpp \
    Level.cpp \
    PhysicsModel.cpp \
    Objective.cpp \
    PlayerItem.cpp \
    TigerItem.cpp \
    EnergyBallItem.cpp \
    FruitItem.cpp \
    Vector2D.cpp

# Archivos de cabecera
HEADERS += \
    mainwindow.h \
    Game.h \
    Player.h \
    Enemy.h \
    PhysicsEngine.h \
    Level.h \
    PhysicsModel.h \
    Objective.h \
    PlayerItem.h \
    TigerItem.h \
    EnergyBallItem.h \
    FruitItem.h \
    Vector2D.h

# Archivos de interfaz
FORMS += \
    mainwindow.ui

# Recursos
RESOURCES += resources.qrc

# Configuración específica por plataforma
win32 {
    RC_ICONS = Img/Goku/Goku.ico
    VERSION = 1.0.0.0
    QMAKE_TARGET_COMPANY = "GameDB Team"
    QMAKE_TARGET_PRODUCT = "GameDB"
    QMAKE_TARGET_DESCRIPTION = "Dragon Ball Platform Game"
    QMAKE_TARGET_COPYRIGHT = "Copyright 2024"
}

macx {
    ICON = Img/Goku/Goku.icns
    VERSION = 1.0.0
    QMAKE_TARGET_COMPANY = "GameDB Team"
    QMAKE_TARGET_PRODUCT = "GameDB"
    QMAKE_TARGET_DESCRIPTION = "Dragon Ball Platform Game"
    QMAKE_TARGET_COPYRIGHT = "Copyright 2024"
}

unix:!macx {
    VERSION = 1.0.0
    QMAKE_TARGET_COMPANY = "GameDB Team"
    QMAKE_TARGET_PRODUCT = "GameDB"
    QMAKE_TARGET_DESCRIPTION = "Dragon Ball Platform Game"
    QMAKE_TARGET_COPYRIGHT = "Copyright 2024"
}
```

### Método 2: Usando CMake

#### CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.16)
project(GameDB VERSION 1.0.0 LANGUAGES CXX)

# Configuración de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Multimedia)

# Configuración de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra")

# Archivos fuente
set(SOURCES
    main.cpp
    mainwindow.cpp
    Game.cpp
    Player.cpp
    Enemy.cpp
    PhysicsEngine.cpp
    Level.cpp
    PhysicsModel.cpp
    Objective.cpp
    PlayerItem.cpp
    TigerItem.cpp
    EnergyBallItem.cpp
    FruitItem.cpp
    Vector2D.cpp
)

# Archivos de cabecera
set(HEADERS
    mainwindow.h
    Game.h
    Player.h
    Enemy.h
    PhysicsEngine.h
    Level.h
    PhysicsModel.h
    Objective.h
    PlayerItem.h
    TigerItem.h
    EnergyBallItem.h
    FruitItem.h
    Vector2D.h
)

# Archivos de recursos
set(RESOURCES
    resources.qrc
)

# Archivos de interfaz
set(FORMS
    mainwindow.ui
)

# Crear ejecutable
add_executable(GameDB ${SOURCES} ${HEADERS} ${RESOURCES} ${FORMS})

# Enlazar con Qt
target_link_libraries(GameDB
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
)

# Configuración específica por plataforma
if(WIN32)
    set_target_properties(GameDB PROPERTIES
        WIN32_EXECUTABLE TRUE
        VERSION 1.0.0.0
    )
    set_target_properties(GameDB PROPERTIES
        OUTPUT_NAME "GameDB"
    )
endif()

if(APPLE)
    set_target_properties(GameDB PROPERTIES
        MACOSX_BUNDLE TRUE
        VERSION 1.0.0
    )
    set_target_properties(GameDB PROPERTIES
        OUTPUT_NAME "GameDB"
    )
endif()
```

#### Compilación con CMake
```bash
# Crear directorio de build
mkdir build
cd build

# Configurar proyecto
cmake ..

# Compilar
cmake --build . --config Release

# O usar make directamente
make
```

### Método 3: Usando Qt Creator

#### Configuración en Qt Creator
1. **Abrir Proyecto**: File → Open File or Project → GameDB.pro
2. **Configurar Kit**: Seleccionar kit de compilación apropiado
3. **Configurar Build**: Build → Build Project "GameDB"
4. **Ejecutar**: Run → Run

#### Configuración de Debug
```qmake
# En GameDB.pro
CONFIG += debug
QMAKE_CXXFLAGS_DEBUG += -g -O0
```

## 🔍 Solución de Problemas de Compilación

### Errores Comunes

#### Error: Qt no encontrado
```bash
# Verificar instalación de Qt
qmake --version

# Verificar variables de entorno
echo $QTDIR
echo $PATH

# Reinstalar Qt si es necesario
```

#### Error: Módulos Qt faltantes
```bash
# Instalar módulos adicionales
# Windows: Qt Maintenance Tool
# Linux: sudo apt install qt6-multimedia-dev
# macOS: brew install qt6
```

#### Error: Compilador no compatible
```bash
# Verificar versión del compilador
gcc --version
clang --version

# Actualizar compilador si es necesario
```

### Logs de Compilación
```bash
# Compilación con logs detallados
qmake -r
make VERBOSE=1

# O con CMake
cmake --build . --verbose
```

## 📦 Empaquetado y Distribución

### Windows

#### Creación de Ejecutable Standalone
```bash
# Usando windeployqt
windeployqt --release --qmldir . GameDB.exe

# O usando Qt Installer Framework
# Crear installer con QtIFW
```

#### Script de Empaquetado (Windows)
```batch
@echo off
set BUILD_DIR=build
set DEPLOY_DIR=deploy
set APP_NAME=GameDB

REM Compilar
qmake GameDB.pro
nmake release

REM Crear directorio de despliegue
if not exist %DEPLOY_DIR% mkdir %DEPLOY_DIR%

REM Copiar ejecutable
copy %BUILD_DIR%\release\%APP_NAME%.exe %DEPLOY_DIR%\

REM Desplegar dependencias Qt
windeployqt --release --qmldir . %DEPLOY_DIR%\%APP_NAME%.exe

REM Crear ZIP
powershell Compress-Archive -Path %DEPLOY_DIR%\* -DestinationPath %APP_NAME%-Windows.zip

echo Empaquetado completado: %APP_NAME%-Windows.zip
```

### macOS

#### Creación de Bundle
```bash
# Usando macdeployqt
macdeployqt GameDB.app -dmg

# O manualmente
mkdir GameDB.app/Contents/MacOS
cp GameDB GameDB.app/Contents/MacOS/
```

#### Script de Empaquetado (macOS)
```bash
#!/bin/bash
BUILD_DIR="build"
DEPLOY_DIR="deploy"
APP_NAME="GameDB"

# Compilar
qmake GameDB.pro
make release

# Crear directorio de despliegue
mkdir -p "$DEPLOY_DIR"

# Crear bundle
mkdir -p "$APP_NAME.app/Contents/MacOS"
mkdir -p "$APP_NAME.app/Contents/Resources"
mkdir -p "$APP_NAME.app/Contents/Frameworks"

# Copiar ejecutable
cp "$BUILD_DIR/GameDB" "$APP_NAME.app/Contents/MacOS/"

# Crear Info.plist
cat > "$APP_NAME.app/Contents/Info.plist" << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>GameDB</string>
    <key>CFBundleIdentifier</key>
    <string>com.gamedb.game</string>
    <key>CFBundleName</key>
    <string>GameDB</string>
    <key>CFBundleVersion</key>
    <string>1.0.0</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0.0</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>CFBundleSignature</key>
    <string>????</string>
    <key>LSMinimumSystemVersion</key>
    <string>10.14</string>
</dict>
</plist>
EOF

# Desplegar dependencias Qt
macdeployqt "$APP_NAME.app" -dmg

echo "Empaquetado completado: $APP_NAME.dmg"
```

### Linux

#### Creación de AppImage
```bash
# Usando linuxdeployqt
linuxdeployqt GameDB -appimage

# O crear .deb package
# Crear estructura de directorios
mkdir -p GameDB_1.0.0/usr/bin
mkdir -p GameDB_1.0.0/usr/share/applications
mkdir -p GameDB_1.0.0/usr/share/icons/hicolor/256x256/apps

# Copiar archivos
cp GameDB GameDB_1.0.0/usr/bin/
cp GameDB.desktop GameDB_1.0.0/usr/share/applications/
cp icon.png GameDB_1.0.0/usr/share/icons/hicolor/256x256/apps/GameDB.png

# Crear package
dpkg-deb --build GameDB_1.0.0
```

#### Script de Empaquetado (Linux)
```bash
#!/bin/bash
BUILD_DIR="build"
DEPLOY_DIR="deploy"
APP_NAME="GameDB"
VERSION="1.0.0"

# Compilar
qmake GameDB.pro
make release

# Crear directorio de despliegue
mkdir -p "$DEPLOY_DIR"

# Copiar ejecutable
cp "$BUILD_DIR/GameDB" "$DEPLOY_DIR/"

# Crear AppDir
mkdir -p "$APP_NAME.AppDir/usr/bin"
mkdir -p "$APP_NAME.AppDir/usr/share/applications"
mkdir -p "$APP_NAME.AppDir/usr/share/icons/hicolor/256x256/apps"

# Copiar archivos
cp "$DEPLOY_DIR/GameDB" "$APP_NAME.AppDir/usr/bin/"

# Crear .desktop file
cat > "$APP_NAME.AppDir/usr/share/applications/GameDB.desktop" << EOF
[Desktop Entry]
Name=GameDB
Comment=Dragon Ball Platform Game
Exec=GameDB
Icon=GameDB
Terminal=false
Type=Application
Categories=Game;
EOF

# Crear AppImage
appimagetool "$APP_NAME.AppDir" "$APP_NAME-$VERSION-x86_64.AppImage"

echo "Empaquetado completado: $APP_NAME-$VERSION-x86_64.AppImage"
```

## 🚀 Despliegue en Diferentes Plataformas

### Steam (Conceptual)
```bash
# Preparar para Steam
# 1. Crear Steam App ID
# 2. Configurar Steamworks SDK
# 3. Crear build compatible con Steam

# Script de build para Steam
steam_build.sh:
#!/bin/bash
VERSION="1.0.0"
STEAM_APP_ID="1234567890"

# Compilar
qmake GameDB.pro
make release

# Crear estructura para Steam
mkdir -p "steam_build/GameDB"
cp GameDB "steam_build/GameDB/"
cp -r Img "steam_build/GameDB/"
cp -r sounds "steam_build/GameDB/"

# Crear manifest
cat > "steam_build/GameDB.vdf" << EOF
"appbuild"
{
    "appid" "$STEAM_APP_ID"
    "desc" "GameDB v$VERSION"
    "buildoutput" "steam_build/output"
    "contentroot" "steam_build/GameDB"
    "setlive" "beta"
    "preview" "0"
    "local" ""
}
EOF

echo "Build para Steam completado"
```

### GOG Galaxy (Conceptual)
```bash
# Preparar para GOG Galaxy
# 1. Crear cuenta de desarrollador en GOG
# 2. Configurar Galaxy SDK
# 3. Crear build compatible

# Script de build para GOG
gog_build.sh:
#!/bin/bash
VERSION="1.0.0"
GOG_APP_ID="1234567890"

# Compilar
qmake GameDB.pro
make release

# Crear estructura para GOG
mkdir -p "gog_build/GameDB"
cp GameDB "gog_build/GameDB/"
cp -r Img "gog_build/GameDB/"
cp -r sounds "gog_build/GameDB/"

# Crear installer
# Usar herramienta de GOG para crear installer

echo "Build para GOG completado"
```

## 📊 Testing y Validación

### Testing de Compilación
```bash
# Script de testing automático
test_build.sh:
#!/bin/bash

echo "Iniciando tests de compilación..."

# Test 1: Compilación básica
echo "Test 1: Compilación básica"
qmake GameDB.pro
make clean
make
if [ $? -eq 0 ]; then
    echo "✓ Compilación básica exitosa"
else
    echo "✗ Error en compilación básica"
    exit 1
fi

# Test 2: Compilación en modo debug
echo "Test 2: Compilación debug"
qmake GameDB.pro CONFIG+=debug
make clean
make
if [ $? -eq 0 ]; then
    echo "✓ Compilación debug exitosa"
else
    echo "✗ Error en compilación debug"
    exit 1
fi

# Test 3: Compilación en modo release
echo "Test 3: Compilación release"
qmake GameDB.pro CONFIG+=release
make clean
make
if [ $? -eq 0 ]; then
    echo "✓ Compilación release exitosa"
else
    echo "✗ Error en compilación release"
    exit 1
fi

echo "Todos los tests de compilación pasaron ✓"
```

### Validación de Dependencias
```bash
# Script para verificar dependencias
check_dependencies.sh:
#!/bin/bash

echo "Verificando dependencias..."

# Verificar Qt
if command -v qmake &> /dev/null; then
    QT_VERSION=$(qmake -query QT_VERSION)
    echo "✓ Qt encontrado: $QT_VERSION"
else
    echo "✗ Qt no encontrado"
    exit 1
fi

# Verificar compilador
if command -v gcc &> /dev/null; then
    GCC_VERSION=$(gcc --version | head -n1)
    echo "✓ GCC encontrado: $GCC_VERSION"
elif command -v clang &> /dev/null; then
    CLANG_VERSION=$(clang --version | head -n1)
    echo "✓ Clang encontrado: $CLANG_VERSION"
else
    echo "✗ Compilador no encontrado"
    exit 1
fi

# Verificar CMake (opcional)
if command -v cmake &> /dev/null; then
    CMAKE_VERSION=$(cmake --version | head -n1)
    echo "✓ CMake encontrado: $CMAKE_VERSION"
else
    echo "⚠ CMake no encontrado (opcional)"
fi

echo "Verificación de dependencias completada ✓"
```

## 🔧 Configuración de CI/CD

### GitHub Actions
```yaml
# .github/workflows/build.yml
name: Build GameDB

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    runs-on: ${{ matrix.os }}
    
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        qt-version: ['6.5.0']
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Setup Qt
      uses: jurplel/install-qt-action@v3
      with:
        version: ${{ matrix.qt-version }}
        modules: qtcharts qtnetworkauth qtwebengine qtwebview qtlocation qtmultimedia
    
    - name: Build on Ubuntu
      if: matrix.os == 'ubuntu-latest'
      run: |
        sudo apt-get update
        sudo apt-get install -y build-essential
        qmake GameDB.pro
        make
    
    - name: Build on Windows
      if: matrix.os == 'windows-latest'
      run: |
        qmake GameDB.pro
        nmake
    
    - name: Build on macOS
      if: matrix.os == 'macos-latest'
      run: |
        qmake GameDB.pro
        make
    
    - name: Upload artifacts
      uses: actions/upload-artifact@v3
      with:
        name: GameDB-${{ matrix.os }}
        path: |
          GameDB.exe
          GameDB
          GameDB.app
```

### GitLab CI
```yaml
# .gitlab-ci.yml
stages:
  - build
  - test
  - package

variables:
  QT_VERSION: "6.5.0"

build_linux:
  stage: build
  image: ubuntu:20.04
  script:
    - apt-get update
    - apt-get install -y build-essential qt6-base-dev qt6-multimedia-dev
    - qmake GameDB.pro
    - make
  artifacts:
    paths:
      - GameDB
    expire_in: 1 week

build_windows:
  stage: build
  image: mcr.microsoft.com/windows/servercore:ltsc2019
  script:
    - qmake GameDB.pro
    - nmake
  artifacts:
    paths:
      - GameDB.exe
    expire_in: 1 week

test:
  stage: test
  script:
    - ./GameDB --test
  dependencies:
    - build_linux

package:
  stage: package
  script:
    - tar -czf GameDB-Linux.tar.gz GameDB
  artifacts:
    paths:
      - GameDB-Linux.tar.gz
    expire_in: 1 month
```

## 📋 Checklist de Despliegue

### Pre-Despliegue
- [ ] Compilación exitosa en todas las plataformas
- [ ] Tests unitarios pasando
- [ ] Tests de integración completados
- [ ] Documentación actualizada
- [ ] Assets optimizados
- [ ] Licencias verificadas

### Despliegue
- [ ] Crear builds para cada plataforma
- [ ] Empaquetar ejecutables
- [ ] Crear instaladores
- [ ] Subir a plataformas de distribución
- [ ] Configurar actualizaciones automáticas

### Post-Despliegue
- [ ] Monitorear crash reports
- [ ] Recopilar feedback de usuarios
- [ ] Planificar actualizaciones
- [ ] Mantener documentación 