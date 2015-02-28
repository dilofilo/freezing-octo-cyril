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
    clientping.cpp \
    launcher.cpp \
    logintoreg.cpp \
    userRegistration.cpp \
    userLogin.cpp \
    fileUpload.cpp \
    fileDownload.cpp \
    fileRemove.cpp \
    sync.cpp \
    revert.cpp \
    share.cpp \
    search.cpp

HEADERS  += client.h \
    ../../common/instructions.h \
    ../../common/communications.h \
    loginpage.h \
    registerpage.h \
    dropbox.h \
    clientdefinitions.h
LIBS += -lssl -lcrypto -lboost_system -lboost_filesystem

FORMS    += client.ui \
    loginpage.ui \
    registerpage.ui \
    dropbox.ui
QMAKE_CXXFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11
