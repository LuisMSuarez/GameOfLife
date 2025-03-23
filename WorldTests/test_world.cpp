#include <QtTest>
#include "../world.h"
#include "../cell.h"
#include "../fish.h"
#include "../shark.h"
#include "../creatureType.h"
#include "../utils.h"

using namespace gameOfLifeCore;

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
void TestWorld::initTestCase()
{
    world = new World();
}

// Run once after all tests in the class have completed.
// It serves the purpose of cleaning up resources or states that were set up in the initTestCase function.
void TestWorld::cleanupTestCase()
{
    delete world;
    // deletion of cells and associated creatures is orchestrated by the world itself
}

void TestWorld::testInitialize()
{
    // Act
    world->initialize(10, 10);

    // Assert
    QCOMPARE(world->rowCount(), 10);
    QCOMPARE(world->colCount(), 10);
}

void TestWorld::testTick()
{
    // Arrange
    world->initialize(10, 10);
    world->addCreatures(CreatureType::fish, 10, false);
    world->addCreatures(CreatureType::shark, 5, false);
    QCOMPARE(Utils::countCreatures(*world), 15);

    // Act
    world->tick();

    // Assert
    // Diffucult to have specific checks to see if the tick has been processed (difficult to check exact state due to randomness of moves)
    // however this should not crash the test.
    // at minimum, we should have less or equal than the original number of creatures (some fish may be eaten)
    QVERIFY(Utils::countCreatures(*world) <= 15);
}

void TestWorld::testGetNeighboringCellsShuffled()
{
    // Arrange
    world->initialize(10, 10);
    Cell &cell = (*world)(5, 5);

    // Act
    auto neighbors = world->getNeighboringCellsShuffled(cell);

    // Assert
    QCOMPARE(neighbors.size(), 8);
}

void TestWorld::testAddCreatures()
{
    // Arrange
    world->initialize(10, 10);

    // Act
    world->addCreatures(CreatureType::fish, 10);
    world->addCreatures(CreatureType::fish, 2);

    // Assert
    QCOMPARE(Utils::countCreatures(*world), 12);
}

QTEST_MAIN(TestWorld)

#include "test_world.moc"
