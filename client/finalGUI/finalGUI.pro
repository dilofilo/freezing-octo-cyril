#-------------------------------------------------
#
# Project created by QtCreator 2015-02-22T15:11:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = finalGUI
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    register.cpp \
    mydropbox.cpp

HEADERS  += login.h \
    register.h \
    mydropbox.h

FORMS    += login.ui \
    register.ui \
    mydropbox.ui

QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11
