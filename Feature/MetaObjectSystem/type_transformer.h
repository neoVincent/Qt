#ifndef TYPE_TRANSFORMER_H
#define TYPE_TRANSFORMER_H

#include <QObject>

#include "meta_type_api.h"

namespace feature {
namespace metasystem {

/**
 * @brief This class is used to bridage the data difference between custom type and json
 */
class META_TYPE_API TypeTransformer : public QObject
{
    Q_OBJECT

public:
    explicit TypeTransformer(QObject* parent = 0);
    virtual ~TypeTransformer();
};

} // metasystem

} // feature


#endif // TYPE_TRANSFORMER_H
