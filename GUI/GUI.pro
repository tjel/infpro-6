#-------------------------------------------------
#
# Project created by QtCreator 2016-01-17T11:02:12
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chatwidget.cpp \
    chat.cpp \
    database.cpp \
    archivewindow.cpp

HEADERS  += mainwindow.h \
    chatwidget.h \
    chat.h \
    database.h \
    archivewindow.h

FORMS    += mainwindow.ui \
    chatwidget.ui \
    archivewindow.ui
