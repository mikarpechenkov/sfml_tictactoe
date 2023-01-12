TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#WINDOWS
# put SFML file in the same location as project
LIBS += -L"..\SFML\lib" #change this
LIBS += -L"..\SFML\bin" #change this

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#WINDOWS
INCLUDEPATH += "..\SFML\include" #change this
DEPENDPATH += "..\SFML\include" #change this

SOURCES += \
        bot.cpp \
        game.cpp \
        main.cpp \
        player.cpp

HEADERS += \
    bot.h \
    game.h \
    player.h
