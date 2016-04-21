include(MetaObjectSystemTest.pri)

QT       += testlib

QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    meta_object_system_test.cpp

HEADERS += \
    meta_object_system_test.h

