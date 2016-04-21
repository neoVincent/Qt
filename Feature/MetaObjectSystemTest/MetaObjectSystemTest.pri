isEmpty(PACKAGE_DESTIR) {
    PACKAGE_DESTIR = $$PWD/../../build
}

CONFIG(debug, debug|release) {
    PACKAGE_DESTIR = $$PACKAGE_DESTIR/debug
} else {
    PACKAGE_DESTIR = $$PACKAGE_DESTIR/release
}


DESTDIR = $$PACKAGE_DESTIR/MetaObjectSystemTest

QMAKE_LIBDIR += $$PACKAGE_DESTIR/MetaObjectSystem

INCLUDEPATH += $$PWD/../MetaObjectSystem/

include($$PWD/../feature.pri)

copyLibrary($$PACKAGE_DESTIR/MetaObjectSystem, MetaObjectSystem, $$DESTDIR)
