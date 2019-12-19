#-------------------------------------------------
#
# Project created by QtCreator 2019-10-26T17:09:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphic01
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dda.cpp \
    bresenham.cpp \
    ellipse.cpp \
    drawbycommands.cpp \
    graphs.cpp \
    polygon.cpp \
    bezier.cpp \
    bspline.cpp

HEADERS += \
        mainwindow.h \
    dda.h \
    bresenham.h \
    ellipse.h \
    drawbycommands.h \
    graphs.h \
    polygon.h \
    bezier.h \
    bspline.h

FORMS += \
        mainwindow.ui
RC_ICONS=paintico.ico
