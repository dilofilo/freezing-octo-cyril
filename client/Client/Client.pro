#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T20:24:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    ../../common/communications.cpp \
    loginpage.cpp \
    registerpage.cpp \
    dropbox.cpp \
    clientping.cpp

HEADERS  += client.h \
    ../../common/instructions.h \
    ../../common/communications.h \
    loginpage.h \
    registerpage.h \
    dropbox.h

FORMS    += client.ui \
    loginpage.ui \
    registerpage.ui \
    dropbox.ui
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11