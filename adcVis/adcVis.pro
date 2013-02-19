#-------------------------------------------------
#
# Project created by QtCreator 2013-02-19T08:44:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adcVis
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h \
    Shaders/GLShader.h

FORMS    += MainWindow.ui
