QT += core
QT += network
QT -= gui

TARGET = Komtest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server_controls.cpp \
    thread_controls.cpp

HEADERS += \
    server_controls.h \
    thread_controls.h

