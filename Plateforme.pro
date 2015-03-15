TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../LibECS/Header/

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lECS -L../LibECS/

QMAKE_CXXFLAGS *= -Wall -Wextra -pedantic -g -std=c++14

SOURCES += main.cpp \
    jeu.cpp \
    moteur.cpp \
    moteurgraphique.cpp \
    niveau.cpp \
    tableau2d.cpp \
    moteurphysique.cpp \
    gestionnairesol.cpp \
    sol.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    jeu.hpp \
    moteur.hpp \
    moteurgraphique.hpp \
    niveau.hpp \
    tableau2d.hpp \
    constantes.hpp \
    moteurphysique.hpp \
    gestionnairesol.hpp \
    sol.hpp

OTHER_FILES += \
    Ressources/niveau0.txt

