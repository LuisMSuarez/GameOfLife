#include <QtTest>
#include "../shark.h"
#include "../world.h"
#include "../cell.h"
#include "../creaturefactory.h"
#include "../creatureType.h"
#include "../utils.h"

class TestShark : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetResource();
    void testEnergyDepletion();
    void testEatFish();
    void testMove();
    void cleanupTestCase();
private:
    World* world;
    Cell* cell;
    Shark* shark;
};

// Run once before any of the tests in the class executes.
void TestShark::initTestCase()
{
    world = new World();
}

// Run once after all tests in the class have completed.
// It serves the purpose of cleaning up resources or states that were set up in the initTestCase function.
void TestShark::cleanupTestCase()
{
    delete world;
    // deletion of cells and associated creatures is orchestrated by the world itself
}

void TestShark::testGetResource()
{
    // Act
    QString resource = QString::fromStdString(shark->getResource());

    // Assert
    QVERIFY(resource.contains("shark-default"));
}

void TestShark::testEnergyDepletion()
{
    // We have a single shark in a world that contains no fish
    // if we tick the world Shark::s_initialEnergy times, the shark should run
    // out of energy and be destroyed
    // Arrange
    world->initialize(2, 2);
    cell = &(*world)(0,0);
    shark = static_cast<Shark*>(&CreatureFactory::Create(CreatureType::shark, *world, *cell));

    // ensure that the energy depletion event happens before the max age event where the shark inevitably dies
    QVERIFY(Shark::s_initialEnergy < Shark::s_maxAge);

    // ensure that the energy depletion event happens before the reproduction age event where the shark will spawn a new child
    QVERIFY(Shark::s_initialEnergy < Shark::s_reproductionTicks);

    // Act
    int initialCount = Utils::countCreatures(*world);
    for (int i=1; i<= Shark::s_initialEnergy-1; i++)
    {
        world->tick();

        // for each tick before the shark runs out of energy, the creature should still exist
        QCOMPARE(Utils::countCreatures(*world), initialCount);
    }

    // one last tick and the shark should die, increasing the number of free cells by 1
    world->tick();

    // Assert
    QCOMPARE(Utils::countCreatures(*world), initialCount-1);
}

void TestShark::testEatFish()
{
    // We place a single shark and a single fish in the 2x2 world
    // when a tick takes place, the shark should eat the fish

    // Arrange
    world->initialize(2, 2);
    cell = &(*world)(0,0);
    shark = static_cast<Shark*>(&CreatureFactory::Create(CreatureType::shark, *world, *cell));

    auto fishCell = &(*world)(0,1);
    CreatureFactory::Create(CreatureType::fish, *world, *fishCell);

    // ensure that the energy depletion event will not happen upon a single tick
    QVERIFY(Shark::s_initialEnergy > 1);

    // ensure that the max age event will not happen upon a single tick
    QVERIFY(Shark::s_maxAge > 1);

    // ensure that the fish will not reproduce upon a single tick
    QVERIFY(Shark::s_reproductionTicks > 1);

    // there should be 2 creatures (a fish and a shark) at this point
    QCOMPARE(Utils::countCreatures(*world), 2);

    // Act
    world->tick();

    // the shark should have eaten the fish as they were placed adjacent in a 2x2
    // Assert
    QCOMPARE(Utils::countCreatures(*world), 1);
}

void TestShark::testMove()
{
    // We place a single shark in the 2x2 world with no fish
    // when a tick takes place, the shark should move to an adjacent cell
    // Arrange
    world->initialize(2, 2);
    cell = &(*world)(0,0);
    shark = static_cast<Shark*>(&CreatureFactory::Create(CreatureType::shark, *world, *cell));

    // ensure that the energy depletion event will not happen upon a single tick
    QVERIFY(Shark::s_initialEnergy > 1);

    // ensure that the max age event will not happen upon a single tick
    QVERIFY(Shark::s_maxAge > 1);

    // ensure that the fish will not reproduce upon a single tick
    QVERIFY(Shark::s_reproductionTicks > 1);

    // there should be 1 creature at this point
    QCOMPARE(Utils::countCreatures(*world), 1);

    // Act
    world->tick();

    // the shark should still be alive, and no longer in the original cell where it was created
    // Assert
    QCOMPARE(Utils::countCreatures(*world), 1);
    QVERIFY(cell->getCreature() == nullptr);
}

QTEST_MAIN(TestShark)
#include "test_shark.moc"
