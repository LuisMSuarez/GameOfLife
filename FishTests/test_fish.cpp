#include <QtTest>
#include "../fish.h"

class TestFish : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void testGetResource();
private:
    World* world;
    Cell* cell;
    Fish* fish;
};

void TestFish::initTestCase()
{
    world = new World();
}

void TestFish::cleanupTestCase()
{
    delete world;
    // deletion of cells and associated creatures is orchestrated by the world itself
}

void TestFish::testGetResource()
{
    // Act
    QString resource = QString::fromStdString(Fish::getResource());

    // Assert
    QVERIFY(resource.contains("fish-default"));
}

void TestFish::test_case1()
{

}

QTEST_MAIN(TestFish)

#include "test_fish.moc"
