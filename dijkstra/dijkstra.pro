#-------------------------------------------------
#
# Project created by QtCreator 2015-05-30T19:14:59
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = dijkstra
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    cgraph.cpp

HEADERS += \
    cgraph.h \
    typedef.h

OTHER_FILES += \
    test.xgml
