#include <QDebug>

#include "customclass.h"
#include "type_transformer.h"
#include "meta_object_system_test.h"

using namespace feature::test;
using namespace feature::metasystem;

void MetaObjectSystemTest::initTestCast()
{
    qDebug() << "Init the test case";
    qDebug() << "Register MetaType: ";
    qDebug() << "CustomClass " << qRegisterMetaType<CustomClass>();
}

void MetaObjectSystemTest::customeClassTest()
{
    TypeTransformer transformer;
    CustomClass myClass{23,"abc"};
    QJsonValue jsonObject = transformer.toJson(QVariant::fromValue(myClass));
    qDebug() << jsonObject;
}

void MetaObjectSystemTest::cleanupTestCase()
{
    qDebug() << "Clean up test case";
}
