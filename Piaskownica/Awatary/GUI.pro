#-------------------------------------------------
#
# Project created by QtCreator 2016-01-17T11:02:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatwidget.cpp \
    chat.cpp \
    avatar.cpp

HEADERS  += mainwindow.h \
    chatwidget.h \
    chat.h \
    avatar.h

FORMS    += mainwindow.ui \
    chatwidget.ui
