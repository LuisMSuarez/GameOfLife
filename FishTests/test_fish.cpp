#include <QtTest>
#include "../fish.h"

class TestFish : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
};

void TestFish::initTestCase() {}

void TestFish::cleanupTestCase() {}

void TestFish::test_case1() {}

QTEST_MAIN(TestFish)

#include "test_fish.moc"
