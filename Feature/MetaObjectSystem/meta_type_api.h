#ifndef META_TYPE_API_H
#define META_TYPE_API_H

#include <QtCore/qglobal.h>

#if defined(METAOBJECT_SYSTEM_LIBRARY)
#  define META_TYPE_API Q_DECL_EXPORT
#else
#  define META_TYPE_API Q_DECL_IMPORT
#endif

#endif // META_TYPE_API_H
