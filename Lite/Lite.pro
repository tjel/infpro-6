QT += core
QT += network
QT -= gui

TARGET = ThreadingTheNeedle
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    prompt.cpp \
    display.cpp

HEADERS += \
    display.h \
    prompt.h

