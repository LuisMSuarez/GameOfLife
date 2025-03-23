#include <QtTest>
#include "../fish.h"
#include "../utils.h"

using namespace gameOfLifeCore;

class TestFish : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testMove();
    void testReproduce();
    void testMaxAge();
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
    QVERIFY(resource.contains("fish"));
}

// We place a single fish in the 2x2 world
// when a tick takes place, the fish should move to an adjacent cell
void TestFish::testMove()
{
    // Arrange
    world->initialize(2, 2);
    cell = &(*world)(0,0);
    fish = static_cast<Fish*>(&CreatureFactory::Create(CreatureType::fish, *world, *cell));

    // ensure that the max age event will not happen upon a single tick
    QVERIFY(Fish::s_maxAge > 1);

    // ensure that the fish will not reproduce upon a single tick
    QVERIFY(Fish::s_reproductionTicks > 1);

    // there should be 1 creature at this point
    QCOMPARE(Utils::countCreatures(*world), 1);

    // Act
    world->tick();

    // the fish should still be alive, and no longer in the original cell where it was created
    // Assert
    QCOMPARE(Utils::countCreatures(*world), 1);
    QVERIFY(cell->getCreature() == nullptr);
}

// We place a single fish in the 2x2 world
// once the reproduction age is reached, we should now have 2 fish
void TestFish::testReproduce()
{
    // Arrange
    world->initialize(2, 2);
    world->addCreatures(CreatureType::fish, 1);

    // ensure that the fish will be able to reproduce before it dies due to max age
    QVERIFY(Fish::s_reproductionTicks < Fish::s_maxAge);

    for (int tick=1; tick<Fish::s_reproductionTicks; tick++)
    {
        world->tick();
        // there should be 1 fish at this point
        QCOMPARE(Utils::countCreatures(*world), 1);
    }

    // one more tick and the fish should reproduce
    world->tick();

    // there should be 2 fish at this point
    QCOMPARE(Utils::countCreatures(*world), 2);
}

// We place a single fish in the 2x2 world
// once the mag age is reached, we should now have 0 fish
void TestFish::testMaxAge()
{
    // Arrange
    world->initialize(2, 2);
    cell = &(*world)(0,0);

    // custom create a new fish overriding default parameters such that it will reach max age before it reproduces
    int maxAge = 5;
    fish = new Fish(*world, *cell, /* reproductionTicks */ 999, /* maxAge */ maxAge, /* resourcePath */ "res");

    for (int tick=1; tick<maxAge; tick++)
    {
        world->tick();
        // there should be 1 fish at this point
        QCOMPARE(Utils::countCreatures(*world), 1);
    }

    // one more tick and the fish should die
    world->tick();

    // there should be 0 fish at this point
    QCOMPARE(Utils::countCreatures(*world), 0);
}

QTEST_MAIN(TestFish)

#include "test_fish.moc"
