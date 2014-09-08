TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-graphics -lsfml-window -lsfml-system

QMAKE_CXXFLAGS *= -Wall -Wextra -pedantic -g

SOURCES += main.cpp \
    jeu.cpp \
    moteur.cpp \
    moteurgraphique.cpp \
    niveau.cpp \
    tableau2d.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    jeu.hpp \
    moteur.hpp \
    moteurgraphique.hpp \
    niveau.hpp \
    tableau2d.hpp \
    constantes.hpp

OTHER_FILES += \
    Ressources/niveau0.txt

