#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaType>
#include <QDebug>
#include <QJsonDocument>

#include "type_transformer.h"

using namespace feature::metasystem;

TypeTransformer::TypeTransformer(QObject* parent)
    : QObject(parent)
{
}

TypeTransformer::~TypeTransformer()
{

}

/**
 * @brief TypeTransformer::fromJson the main entrance of the fromJson serial
 * @param jsonValue
 * @param defaultVal
 * @return
 */
QVariant TypeTransformer::fromJson(QJsonValue jsonValue, QVariant defaultVal)
{

    switch (jsonValue.type())
    {
    case QJsonValue::Object:
        return fromJson(jsonValue.toObject(), defaultVal);
    case QJsonValue::Array:
        return fromJson(jsonValue.toArray(), defaultVal);
    default:
        return jsonValue.toVariant();
    }
}

QVariant TypeTransformer::fromJson(QJsonArray jsonArray, QVariant defaultVal)
{
    QVariantList varList;

    if (!defaultVal.canConvert<QVariantList>())
    {
        qDebug() << "Response type is list, but the default value is not";
        return defaultVal;
    }

    QSequentialIterable iterable = defaultVal.value<QSequentialIterable>();
    if (iterable.size() != jsonArray.size())
    {
        qDebug() << "Default list value size is not the same as response's";
        return defaultVal;
    }

    for (int i = 0 ; i < jsonArray.size(); i++)
    {
        varList.append(fromJson(jsonArray.at(i), iterable.at(i)));
    }

    return varList;
}

/**
 * @brief TypeTransformer::fromJson
 *         write the value from jsonObject to the defaultVal
 *          0. QVariant.userType()--> QMetaType-->QMetaObject-->QMetaProperty
 *          1. use the QMetaProperty's name to get the value from jsonobject
 *          2. use QMetaProperty.writeOnGadget() to write the value
 * @param jsonObject
 * @param defaultVal
 * @return
 */
QVariant TypeTransformer::fromJson(QJsonObject jsonObject, QVariant defaultVal)
{
    if (supportedType(defaultVal))
    {
        QVariant supportVal = defaultVal;
        QMetaType metaType(defaultVal.userType());
        const QMetaObject* metaObject = metaType.metaObject();
        for (int i = 0 ; i < metaObject->propertyCount(); i++)
        {
            QMetaProperty property = metaObject->property(i);
            QJsonValue propertyVal = jsonObject[property.name()];
            QVariant variantVal = fromJson(propertyVal, QVariant(property.type(), nullptr));
            if (!variantVal.isValid() || !property.writeOnGadget(supportVal.data(), variantVal))
            {
                qWarning() << "Failed to write property" << property.name() << "to" << supportVal.typeName()
                           << "with value" << variantVal;
                qDebug() << " PropVar type " << property.type();
                qDebug() << "PropVar typename " << property.typeName();
            }
        }
        return supportVal;
    }
    else if (defaultVal.type() == QMetaType::QJsonObject)
    {
        return  QVariant::fromValue(jsonObject);
    }
    else if (defaultVal.type() == QMetaType::QJsonValue)
    {
        return QVariant::fromValue(QJsonValue(jsonObject));
    }
    else
    {
        //unsupport custom type
        qDebug() << "Unsupported type for json:" << QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    }

    return defaultVal;
}

/**
 * @brief TypeTransformer::toJson The main entrance of the toJson serial
 * @param variant
 * @return
 */
QJsonValue TypeTransformer::toJson(QVariant variant)
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
        if (value.isString() && (variant.type() != QMetaType::QString))
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
    QJsonArray jsonArray;
    for (int i = 0 ; i < variantList.size(); i++)
    {
        jsonArray.append(toJson(variantList.at(i)));
    }
    return jsonArray;
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

bool TypeTransformer::supportedType(QVariant var)
{
    if (var.type() >= QMetaType::User)
    {
        QMetaType metaType(var.type());
        if (metaType.flags().testFlag(QMetaType::IsGadget))
        {
            return true;
        }
        else
        {
            qDebug() << "The type is not supported";
        }

    }
    return false;
}
