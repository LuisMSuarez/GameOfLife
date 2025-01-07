#include <QtTest/QtTest>
#include "../fish.h"
#include "../world.h"
#include "../cell.h"

class TestFish : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testGetResource();
    void testTick();

private:
    World *world;
    Cell *cell;
    Fish *fish;
};

void TestFish::initTestCase()
{
    world = new World();
    world->initialize(10, 10);
    cell = &(*world)(5, 5);
    fish = new Fish(*world, *cell, 10, 35, "/path/to/resource", 0);
}

void TestFish::cleanupTestCase()
{
    delete fish;
    delete world;
}

void TestFish::testGetResource()
{
    QString resource = QString::fromStdString(fish->getResource());
    QVERIFY(resource.endsWith("fish.jpg"));
}

void TestFish::testTick()
{
    Cell &newCell = (*world)(4, 5);
    QVERIFY(newCell.isEmpty());

    fish->tick();

    QVERIFY(newCell.getCreature() == fish);
    QVERIFY(cell->isEmpty());
    // QVERIFY(fish->reachedTimeToReproduce() == false); // Reset reproduction time
}

//QTEST_MAIN(TestFish)
#include "testfish.moc"
