#ifndef TYPE_TRANSFORMER_H
#define TYPE_TRANSFORMER_H

#include <QObject>
#include <QVariant>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "meta_type_api.h"

namespace feature {
namespace metasystem {

/**
 * @brief This class is used to do the type conversion between QVariant and QJsonObject
 */
class META_TYPE_API TypeTransformer : public QObject
{
    Q_OBJECT

public:
    explicit TypeTransformer(QObject* parent = 0);
    virtual ~TypeTransformer();

    QVariant fromJson(QJsonValue jsonValue, QVariant defaultVal);

    QVariant fromJson(QJsonArray jsonArray, QVariant defaultVal);

    QVariant fromJson(QJsonObject jsonObject, QVariant defaultVal);

    QJsonValue toJson(QVariant variant);

    QJsonArray toJson(QVariantList& variantList);

    QJsonValue toJson(const QMetaObject* metaObject, QVariant& gadgetVal);

private:

    bool supportedType(QVariant var);
};

} // metasystem

} // feature


#endif // TYPE_TRANSFORMER_H
