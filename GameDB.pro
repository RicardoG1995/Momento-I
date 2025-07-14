QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameDB
TEMPLATE = app

SOURCES += \
    EnergyBallItem.cpp \
    FruitItem.cpp \
    Vector2D.cpp \
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
    TigerItem.cpp

HEADERS += \
    EnergyBallItem.h \
    FruitItem.h \
    Vector2D.h \
    mainwindow.h \
    Game.h \
    Player.h \
    Enemy.h \
    PhysicsEngine.h \
    Level.h \
    PhysicsModel.h \
    Objective.h \
    PlayerItem.h \
    TigerItem.h

FORMS += \
    mainwindow.ui

RESOURCES += resources.qrc 
