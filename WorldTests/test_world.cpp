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
       void testGetNeighboringCellsShuffled();
       void testAddCreatures();

    private:
        World *world;
};

// Run once before any of the tests in the class executes.
// This ensures that each test run starts with a clean slate and avoids interference between tests.
void TestWorld::initTestCase()
{
    world = new World();
}

// special function within a test class that is executed once after all test functions in that class have completed.
// It serves the purpose of cleaning up resources or states that were set up in the
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

#include "test_world.moc"
