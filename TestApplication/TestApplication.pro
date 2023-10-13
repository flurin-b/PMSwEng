include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG += qt
QT += core

INCLUDEPATH += \
        ../PacMan

SOURCES += \
        main.cpp
