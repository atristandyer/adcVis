#-------------------------------------------------
#
# Project created by QtCreator 2013-02-19T08:44:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lGLEW -lGLU -lGL

TARGET = adcVis
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Shaders/GLShader.cpp \
    OpenGL/GLCamera.cpp \
    OpenGL/glew.c

HEADERS  += MainWindow.h \
    Shaders/GLShader.h \
    adcData.h \
    OpenGL/GLCamera.h \
    GLData.h \
    OpenGL/wglew.h \
    OpenGL/glxew.h \
    OpenGL/glew.h

FORMS    += MainWindow.ui

OTHER_FILES += \
    docConfig
