TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()
LIBS += -L"/usr/local/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"



CONFIG += c++11

HEADERS += \
    Game.h \
    Creature.h \
    Graph_Control.h \
    Creature_Graphic_Info.h \
    A_star.h \
    Portal.h \
    Search_Node.h

