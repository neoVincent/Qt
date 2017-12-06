#ifndef META_TYPE_REGISTER_TEST_H
#define META_TYPE_REGISTER_TEST_H

#include <QObject>
#include <QTest>

namespace feature {
namespace test {

class MetaTypeRegisterTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCast();
    void customeClassTest();
    void cleanupTestCase();
};


} // test
} // feature

#endif // META_TYPE_REGISTER_TEST_H
