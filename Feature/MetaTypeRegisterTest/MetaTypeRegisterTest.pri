isEmpty(PACKAGE_DESTIR) {
    PACKAGE_DESTIR = $$PWD/../../build
}

CONFIG(debug, debug|release) {
    PACKAGE_DESTIR = $$PACKAGE_DESTIR/debug
} else {
    PACKAGE_DESTIR = $$PACKAGE_DESTIR/release
}


DESTDIR = $$PACKAGE_DESTIR/MetaTypeRegisterTest

QMAKE_LIBDIR += $$PACKAGE_DESTIR/MetaTypeRegister

INCLUDEPATH += $$PWD/../MetaTypeRegister/

include($$PWD/../feature.pri)

copyLibrary($$PACKAGE_DESTIR/MetaTypeRegister, MetaTypeRegister, $$DESTDIR)
