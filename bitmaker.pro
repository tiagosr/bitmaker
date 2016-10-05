#-------------------------------------------------
#
# Project created by QtCreator 2016-10-03T21:20:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bitmaker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    emulatorview.cpp

HEADERS  += mainwindow.h \
    libretro.h \
    emulatorview.h

FORMS    += mainwindow.ui
