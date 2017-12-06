#include <QJsonObject>
#include <QDebug>
#include <QVector>

#include "meta_type_register_test.h"
#include "my_class.h"
#include "meta_type_register.h"

void feature::test::MetaTypeRegisterTest::initTestCast()
{

}

void feature::test::MetaTypeRegisterTest::customeClassTest()
{
    QVERIFY(RegisterMetaType<MyClass*>() >= 0);
    QVERIFY(RegisterMetaType<QVector<MyClass*>>() >= 0);
}

void feature::test::MetaTypeRegisterTest::cleanupTestCase()
{

}

#include "meta_type_register.h"
