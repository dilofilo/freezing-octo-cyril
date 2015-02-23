#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T19:19:19
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../common/communications.cpp \
    server.cpp \
    ping.cpp

OTHER_FILES += \
    ../details.txt

HEADERS += \
    server.h \
    ../common/instructions.h \
    ../common/communications.h
