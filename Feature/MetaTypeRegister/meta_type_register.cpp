#include "meta_type_register.h"

#include <QLibrary>
#include <QDebug>

MetaTable* LocalMetaTable()
{
    static MetaTable theInstance;
    return &theInstance;
}

MetaTable* MetaTableForLibrary(const QString& fileName)
{
    typedef MetaTable* (*MetaObjectsGetter)();
    QLibrary library(fileName);
    MetaObjectsGetter getLibraryTable = (MetaObjectsGetter) library.resolve("LocalMetaTable");
    if (!getLibraryTable)
    {
        qWarning() << "Library " << fileName << " does not contains a MetaTable";
        return nullptr;
    }
    return getLibraryTable();
}
