include (MetaTypeRegister.pri)

QT       -= gui

TARGET = MetaTypeRegister
TEMPLATE = lib

DEFINES += METATYPEREGISTER_LIBRARY

SOURCES += meta_type_register.cpp

HEADERS += meta_type_register.h \
    meta_type_register_api.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

