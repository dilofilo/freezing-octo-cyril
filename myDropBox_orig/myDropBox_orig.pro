#-------------------------------------------------
#
# Project created by QtCreator 2015-02-18T15:01:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myDropBox_orig
TEMPLATE = app


SOURCES += main.cpp\
        client.cpp \
    loginform.cpp

HEADERS  += client.h \
    loginform.h

FORMS    += client.ui \
    loginform.ui
