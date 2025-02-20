#include <QtTest/QtTest>
#include "../shark.h"
#include "../world.h"
#include "../cell.h"
#include "../creaturefactory.h"
#include "../creatureType.h"

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
    void cleanupTestCase();
private:
    World* world;
    Cell* cell;
    Shark* shark;
};

// Run once before any of the tests in the class executes.
// This ensures that each test run starts with a clean slate and avoids interference between tests.
void TestShark::initTestCase()
{
    world = new World();
    cell = new Cell();
    shark = static_cast<Shark*>(&CreatureFactory::Create(CreatureType::shark, *world, *cell));
}

// special function within a test class that is executed once after all test functions in that class have completed.
// It serves the purpose of cleaning up resources or states that were set up in the
void TestShark::cleanupTestCase()
{
    delete cell;  // internally will destroy the creature
    delete world;
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
