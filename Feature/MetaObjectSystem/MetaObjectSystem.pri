isEmpty(PACKAGE_DESTIR) {
    PACKAGE_DESTIR = $$PWD/../../build
}

CONFIG(debug, debug|release) {
    PACKAGE_DESTIR = $$PACKAGE_DESTIR/debug
} else {
    PACKAGE_DESTIR = $$PACKAGE_DESTIR/release
}


DESTDIR = $$PACKAGE_DESTIR/MetaObjectSystem
