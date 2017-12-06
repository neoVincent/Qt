#ifndef META_TYPE_REGISTER_H
#define META_TYPE_REGISTER_H

#include <QMap>
#include <QMetaObject>
#include <QtGlobal>
#include <QMetaType>

typedef QMap<int, const QMetaObject*> MetaTable;

Q_DECLARE_METATYPE(MetaTable)

/*! \brief Gets the QMetaObjec* map associated with this shared library.
 */
extern "C" Q_DECL_EXPORT MetaTable* LocalMetaTable();

// Use SFINAE to filter the qt container
// Link: https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
/*! \brief Register a new type with Qt.
 *  \returns the internal ID used by QMetaType.
 */
template <typename T>
int RegisterMetaTypeImpl(typename T::iterator*)
{
    return qRegisterMetaType<T>();
}

/*! \brief Register a new type with Qt and local table.
 *  \returns the internal ID used by QMetaType.
 */
template <typename T>
int RegisterMetaTypeImpl(T*)
{
    int typeId = qRegisterMetaType<T>();
    const QMetaObject* metaObject = &std::remove_pointer<T>::type::staticMetaObject;
    LocalMetaTable()->insert(typeId, metaObject);
    return typeId;
}

/*! \brief Register the type for the type T.
 *  \returns the internal ID used by QMetaType.
 */
template <typename T>
int RegisterMetaType()
{
    return RegisterMetaTypeImpl<T>(nullptr);
}

#endif // META_TYPE_REGISTER_H
