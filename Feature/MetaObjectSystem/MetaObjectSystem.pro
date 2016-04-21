include (MetaObjectSystem.pri)

QT       -= gui

TARGET = MetaObjectSystem

TEMPLATE = lib

DEFINES += METAOBJECT_SYSTEM_LIBRARY

SOURCES += type_transformer.cpp

HEADERS += type_transformer.h \
    meta_type_api.h
