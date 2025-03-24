#include <QtTest>
#include "../shark.h"
#include "../world.h"
#include "../cell.h"
#include "../creaturefactory.h"
#include "../creatureType.h"
#include "../utils.h"

using namespace GameOfLifeCore;

class TestShark : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testGetResource();
    void testEnergyDepletion();
    void testGainEnergy();
    void testEatFish();
    void testMove();
    void testReproduce();
    void testMaxAge();
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
    QString resource = QString::fromStdString(Shark::getResource());

    // Assert
    QVERIFY(resource.contains("shark"));
}

// We have a single shark in a world that contains no fish
// if we tick the world Shark::s_initialEnergy times, the shark should run
// out of energy and be destroyed
void TestShark::testEnergyDepletion()
{
    // Arrange
    world->initialize(2, 2);
    world->addCreatures(CreatureType::shark, 1);

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

    // one last tick and the shark should die
    world->tick();

    // Assert
    QCOMPARE(Utils::countCreatures(*world), initialCount-1);
}

// We place a single shark in the 2x2 world.
// just before the shark would run out of energy, we add a fish to the world
// and we verify that the shark can survive addidional ticks
void TestShark::testGainEnergy()
{
    // Arrange
    world->initialize(2, 2);
    world->addCreatures(CreatureType::shark, 1);

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

    // add a fish to the world so the shark can eat it and gain energy
    world->addCreatures(CreatureType::fish, 1);

    // one more tick and the shark should not die and the fish should have been eaten
    world->tick();

    // Assert
    QCOMPARE(Utils::countCreatures(*world), initialCount);
}

// We place a single shark and a single fish in the 2x2 world
// when a tick takes place, the shark should eat the fish
void TestShark::testEatFish()
{
    // Arrange
    world->initialize(2, 2);
    world->addCreatures(CreatureType::shark, 1);
    world->addCreatures(CreatureType::fish, 1);

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

// We place a single shark in the 2x2 world with no fish
// when a tick takes place, the shark should move to an adjacent cell
void TestShark::testMove()
{
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

// We place a single shark in the 2x2 world
// once the reproduction age is reached, we should now have 2 sharks
void TestShark::testReproduce()
{
    // Arrange
    world->initialize(2, 2);

    // custom create a new shark overriding default parameters such that it will reproduce before it runs out of energy or dies
    // and also not run out of energy
    int reproductionTicks = 5;
    shark = new Shark(*world, *cell, /* reproductionTicks */ 5, /* maxAge */ 999, /* initialEnergy */ 999, /* resourcePath */ "res");

    for (int tick=1; tick<reproductionTicks; tick++)
    {
        world->tick();
        // there should be 1 shark at this point
        QCOMPARE(Utils::countCreatures(*world), 1);
    }

    // one more tick and the fish should reproduce
    world->tick();

    // there should be 2 sharks at this point
    QCOMPARE(Utils::countCreatures(*world), 2);
}

// We place a single shark in the 2x2 world
// once the mag age is reached, we should now have 0 sharks
void TestShark::testMaxAge()
{
    // Arrange
    world->initialize(2, 2);
    cell = &(*world)(0,0);

    // custom create a new shark overriding default parameters such that it will reach max age before it reproduces
    // and also not run out of energy
    int maxAge = 5;
    shark = new Shark(*world, *cell, /* reproductionTicks */ 999, /* maxAge */ maxAge, /* initialEnergy */ 999, /* resourcePath */ "res");

    for (int tick=1; tick<maxAge; tick++)
    {
        world->tick();
        // there should be 1 shark at this point
        QCOMPARE(Utils::countCreatures(*world), 1);
    }

    // one more tick and the shark should die
    world->tick();

    // there should be 0 sharks at this point
    QCOMPARE(Utils::countCreatures(*world), 0);
}

QTEST_MAIN(TestShark)
#include "test_shark.moc"
