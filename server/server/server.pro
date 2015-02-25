#-------------------------------------------------
#
# Project created by QtCreator 2015-02-24T22:49:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../common/communications.cpp \
    database.cpp \
    server.cpp \
    ping.cpp \
    login.cpp
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11

HEADERS += \
    ../../common/communications.h \
    ../../common/instructions.h \
    serverdefinitions.h \
    server.h