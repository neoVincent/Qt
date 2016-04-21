#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>
#include <QDebug>

#include "type_transformer.h"

using namespace feature::metasystem;

TypeTransformer::TypeTransformer(QObject* parent)
    : QObject(parent)
{
}

TypeTransformer::~TypeTransformer()
{

}

QVariant TypeTransformer::fromJson(QJsonValue jsonObject, QVariant defaultVal)
{
    return QVariant();
}

QVariant TypeTransformer::fromJson(QJsonArray jsonObject, QVariant defaultVal)
{
    return QVariant();
}

QVariant TypeTransformer::fromJson(QJsonObject jsonObject, QVariant defaultVal)
{
    return QVariant();
}

QJsonValue TypeTransformer::toJson(QVariant& variant)
{
    switch (variant.type())
    {
    case QMetaType::User:
    {
        QMetaType metaType(variant.userType());
        return toJson(metaType.metaObject(), variant);
    }
    case QMetaType::QJsonValue:
        return variant.value<QJsonValue>();
    case QMetaType::QJsonObject:
        return variant.value<QJsonObject>();
    case QMetaType::QJsonArray:
        return variant.value<QJsonArray>();
    default:
    {
        QJsonValue value = QJsonValue::fromVariant(variant);
        if (value.isString() && (variant.type() != QMetaType::QString) )
        {
            qWarning() << "conversion to Json is not supported for the type " << variant.type();
            return QJsonValue();
        }
        else
        {
            return value;
        }
    }
    }
}

QJsonArray TypeTransformer::toJson(QVariantList& variantList)
{
    return QJsonArray{};
}

/**
 * @brief TypeTransformer::toJson
 * @param metaObject Used to get the property name as the key value for jsonobject
 * @param gadgetVal Used to get the actual value as the data value for jsonobject
 * @return
 */
QJsonValue TypeTransformer::toJson(const QMetaObject* metaObject, QVariant& gadgetVal)
{
    QJsonObject jsonObject;
    for (int i = 0 ; i < metaObject->propertyCount(); i++)
    {
        QMetaProperty property = metaObject->property(i);
        jsonObject.insert(property.name(), toJson(property.readOnGadget(gadgetVal.data())));
    }
    return jsonObject;
}
