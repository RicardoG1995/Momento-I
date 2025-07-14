# GameDB - Juego de Plataformas con Temática Dragon Ball

## 📋 Descripción General

GameDB es un juego de plataformas 2D desarrollado en C++ utilizando el framework Qt. El juego presenta una temática inspirada en Dragon Ball, donde el jugador controla a Goku y debe completar diversos objetivos a través de múltiples niveles.

## 🎮 Características Principales

- **3 Niveles únicos** con mecánicas diferentes
- **Sistema de física** con gravedad y colisiones
- **Animaciones fluidas** para personajes y enemigos
- **Sistema de sonido** con efectos de audio
- **Interfaz gráfica** moderna y responsiva
- **Mecánicas de combate** con bolas de energía
- **Sistema de colección** de frutas y objetos

## 🏗️ Arquitectura del Proyecto

El proyecto está estructurado en módulos bien definidos:

- **Core Game Logic**: Lógica principal del juego
- **Graphics Engine**: Sistema de renderizado con Qt Graphics
- **Physics Engine**: Motor de físicas personalizado
- **Audio System**: Sistema de sonido integrado
- **Level Management**: Gestión de niveles y objetivos

## 📁 Estructura de Documentación

Esta documentación está organizada en los siguientes archivos:

1. **[ARCHITECTURE.md](ARCHITECTURE.md)** - Arquitectura del sistema y diseño de clases
2. **[API_REFERENCE.md](API_REFERENCE.md)** - Referencia completa de la API
3. **[GAMEPLAY_MECHANICS.md](GAMEPLAY_MECHANICS.md)** - Mecánicas de juego detalladas
4. **[ASSETS_AND_RESOURCES.md](ASSETS_AND_RESOURCES.md)** - Gestión de recursos y assets
5. **[PHYSICS_SYSTEM.md](PHYSICS_SYSTEM.md)** - Sistema de físicas y colisiones
6. **[AUDIO_SYSTEM.md](AUDIO_SYSTEM.md)** - Sistema de audio y efectos de sonido
7. **[LEVEL_DESIGN.md](LEVEL_DESIGN.md)** - Diseño y estructura de niveles
8. **[BUILD_AND_DEPLOYMENT.md](BUILD_AND_DEPLOYMENT.md)** - Compilación y despliegue
9. **[DEVELOPMENT_GUIDE.md](DEVELOPMENT_GUIDE.md)** - Guía para desarrolladores

## 🚀 Inicio Rápido

### Requisitos del Sistema

- **Qt 5.12+** o **Qt 6.x**
- **Compilador C++** compatible (GCC, MSVC, Clang)
- **CMake** o **qmake**
- **Sistema operativo**: Windows, Linux, macOS

### Compilación

```bash
# Clonar el repositorio
git clone <repository-url>
cd GameDB-main

# Compilar con qmake
qmake GameDB.pro
make

# O con CMake
mkdir build && cd build
cmake ..
make
```

### Ejecución

```bash
./GameDB
```

## 🎯 Objetivos del Juego

### Nivel 1: Recolección de Frutas
- **Objetivo**: Recolectar todas las frutas en 30 segundos
- **Mecánicas**: Movimiento básico, salto, colección de objetos

### Nivel 2: Rescate de Bulma
- **Objetivo**: Llegar a Bulma y rescatarla
- **Mecánicas**: Combate con tigre, movimiento avanzado

### Nivel 3: Supervivencia
- **Objetivo**: Sobrevivir a las balas enemigas
- **Mecánicas**: Disparos de energía, evasión, combate

## 🛠️ Tecnologías Utilizadas

- **C++17/20**: Lenguaje principal
- **Qt 6**: Framework de interfaz gráfica
- **Qt Graphics Scene**: Sistema de renderizado 2D
- **Qt Multimedia**: Sistema de audio
- **OpenGL**: Aceleración por hardware (opcional)

## 📊 Métricas del Proyecto

- **Líneas de código**: ~2,500+
- **Clases principales**: 15+
- **Archivos de recursos**: 25+
- **Efectos de sonido**: 2
- **Niveles**: 3

## 🤝 Contribución

Para contribuir al proyecto:

1. Fork el repositorio
2. Crea una rama para tu feature (`git checkout -b feature/nueva-funcionalidad`)
3. Commit tus cambios (`git commit -am 'Añadir nueva funcionalidad'`)
4. Push a la rama (`git push origin feature/nueva-funcionalidad`)
5. Crea un Pull Request

## 📄 Licencia

Este proyecto está bajo la Licencia MIT. Ver el archivo `LICENSE` para más detalles.

## 👥 Autores

- **Desarrollador Principal**:Ricardo Gómez
- **Fecha de Creación**: 2025
- **Versión Actual**: 1.0


- **Email**: [tu-email@ejemplo.com]
- **GitHub**: [tu-usuario-github]
- **Issues**: [Link al repositorio de issues]

---

**Nota**: Esta documentación está en constante actualización. Para la versión más reciente, consulta la rama `main` del repositorio. 
