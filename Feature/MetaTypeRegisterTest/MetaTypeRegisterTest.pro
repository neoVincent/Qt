include (MetaTypeRegisterTest.pri)

QT       += testlib

QT       -= gui

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    meta_type_register_test.cpp \
    my_class.cpp \
    main.cpp

HEADERS += \
    my_class.h \
    meta_type_register_test.h

LIBS += -lMetaTypeRegister

