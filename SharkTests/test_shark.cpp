#include <QtTest/QtTest>
#include "../shark.h"
#include "../world.h"
#include "../cell.h"

class TestShark : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetResource();
    void testTick();
    //void testGainEnergy();
    //void testLoseEnergy();
    //void testCheckEnergy();

private:
    World* world;
    Cell* cell;
    Shark* shark;
};

void TestShark::initTestCase()
{
    world = new World();
    cell = new Cell();
    shark = new Shark(*world, *cell, 15, 50, "/resources/shark.jpg", 0);
}

void TestShark::testGetResource()
{
    QString resource = QString::fromStdString(shark->getResource());
    QVERIFY(resource.contains("shark.jpg"));
}

void TestShark::testTick()
{
    // Initial energy should be s_initialEnergy
    // QCOMPARE(shark->getEnergy(), Shark::s_initialEnergy);

    // Mock neighboring cells and creatures
    // Add test logic for movement and energy loss
    shark->tick();
    // QCOMPARE(shark->getEnergy(), Shark::s_initialEnergy - 1);

    // Add more test cases for various tick scenarios
}

/*
void TestShark::testGainEnergy()
{
    // int initialEnergy = shark->getEnergy();
    shark->gainEnergy(10);
    QCOMPARE(shark->getEnergy(), initialEnergy + 10);
}

void TestShark::testLoseEnergy()
{
    // int initialEnergy = shark->getEnergy();
    shark->loseEnergy(5);
    QCOMPARE(shark->getEnergy(), initialEnergy - 5);
}

void TestShark::testCheckEnergy()
{
    // shark->loseEnergy(shark->getEnergy()); // Deplete energy
    shark->checkEnergy();
    QVERIFY(shark->isTaggedForDeletion());
}
*/

QTEST_MAIN(TestShark)
#include "test_shark.moc"
