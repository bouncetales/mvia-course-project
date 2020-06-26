#-------------------------------------------------
#
# Project created by QtCreator 2020-03-21T18:26:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MVProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    imageviewer.cpp

HEADERS  += mainwindow.h \
    imageviewer.h \
    asmOpenCV.h

FORMS    += mainwindow.ui

DISTFILES += \
    CMakeLists.txt
