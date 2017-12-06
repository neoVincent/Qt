TEMPLATE = subdirs

SUBDIRS += \
    MetaObjectSystem \
    MetaObjectSystemTest \
    MetaTypeRegister \
    MetaTypeRegisterTest

MetaObjectSystemTest.depend = MetaObjectSystem
MetaTypeRegisterTest.depend = MetaTypeRegister
