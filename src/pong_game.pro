#-------------------------------------------------
#
# Project created by QtCreator 2010-12-18T14:44:11
#
#-------------------------------------------------

QT       += core gui

TARGET = pong_game
TEMPLATE = app


SOURCES += main.cpp \
    element.cpp \
    ball.cpp \
    pong.cpp \
    bar.cpp \
    scene.cpp \
    player.cpp \
    bar_ai.cpp \
    bonus.cpp \
    bonus_bigbar.cpp \
    bonus_smallbar.cpp \
    loader.cpp \
    bonus_magnet.cpp

HEADERS  += \
    element.h \
    ball.h \
    pong.h \
    bar.h \
    scene.h \
    player.h \
    bar_ai.h \
    bonus.h \
    bonus_bigbar.h \
    bonus_smallbar.h \
    loader.h \
    bonus_magnet.h

FORMS    +=

RESOURCES +=

RC_FILE = myapp.icns
