#include <QtTest/QtTest>
#include "../world.h"
#include "../cell.h"
#include "../fish.h"
#include "../shark.h"
#include "../creatureType.h"

class TestWorld : public QObject
{
    Q_OBJECT

private slots:
   void initTestCase();
   void cleanupTestCase();
   void testInitialize();
   void testTick();
    //void testGetFreeCellsShuffled();
   void testGetNeighboringCellsShuffled();
   void testAddCreatures();

private:
    World *world;
};

void TestWorld::initTestCase()
{
    world = new World();
}

void TestWorld::cleanupTestCase()
{
    delete world;
}

void TestWorld::testInitialize()
{
    world->initialize(10, 10);
    QCOMPARE(world->rowCount(), 10);
    QCOMPARE(world->colCount(), 10);
}

void TestWorld::testTick()
{
    world->initialize(10, 10);
    world->addCreatures(CreatureType::fish, 10, false);
    world->addCreatures(CreatureType::shark, 5, false);
    int creatureCount = 0;
    for (auto &cell : *world)
    {
        if (cell.getCreature() != nullptr)
        {
            creatureCount++;
        }
    }
    QCOMPARE(creatureCount, 15);
    world->tick();
    // Check if tick has been processed (difficult to check exact state due to randomness)
}

/*
void TestWorld::testGetFreeCellsShuffled()
{
    world->initialize(10, 10);
    auto freeCells = world->getFreeCellsShuffled();
    QCOMPARE(freeCells.size(), 100);
}
*/

void TestWorld::testGetNeighboringCellsShuffled()
{
    world->initialize(10, 10);
    Cell &cell = (*world)(5, 5);
    auto neighbors = world->getNeighboringCellsShuffled(cell);
    QCOMPARE(neighbors.size(), 8);
}

void TestWorld::testAddCreatures()
{
    world->initialize(10, 10);
    world->addCreatures(CreatureType::fish, 10, false);
    int fishCount = 0;
    for (auto &cell : *world)
    {
        if (cell.getCreature() && dynamic_cast<Fish*>(cell.getCreature()))
        {
            fishCount++;
        }
    }
    QCOMPARE(fishCount, 10);
}

QTEST_MAIN(TestWorld)
#include "testworld.moc"
