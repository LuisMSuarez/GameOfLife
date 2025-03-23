#include <cassert>    // assert
#include "creature.h"

using namespace gameOfLifeCore;

gameOfLifeCore::Creature::Creature(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge) :
    m_world(world), m_cell(&cell), m_reproductionTicks(reproductionTicks), m_max_age(maxAge), m_resourcePath(resourcePath), m_age(startingAge)
{
    m_reproductionTimer = reproductionTicks;
    m_taggedForDeletion = false;
    cell.addCreature(this);
}

gameOfLifeCore::Creature::~Creature()
{
}

void gameOfLifeCore::Creature::moveTo(Cell &cell)
{
    assert(cell.getCreature() == nullptr); // the destination cell must not already be occupied by another creature
    m_cell->removeCreature();
    cell.addCreature(this);
    m_cell = &cell;
}

Cell& gameOfLifeCore::Creature::getCell()
{
    return *m_cell;
}

void gameOfLifeCore::Creature::tagForDeletion()
{
    m_cell->removeCreature();
    m_taggedForDeletion = true;
    m_cell = nullptr;
}

bool gameOfLifeCore::Creature::isTaggedForDeletion()
{
    return m_taggedForDeletion;
}

std::string gameOfLifeCore::Creature::getResourcePath()
{
    return m_resourcePath;
}

void gameOfLifeCore::Creature::tick()
{
    m_age++;
    if (m_reproductionTimer > 0)
    {
        m_reproductionTimer--;
    }
}

bool gameOfLifeCore::Creature::reachedMaxAge()
{
    return m_age >= m_max_age;
}

bool gameOfLifeCore::Creature::reachedTimeToReproduce()
{
    return m_reproductionTimer <= 0;
}

void gameOfLifeCore::Creature::resetTimeToReproduce()
{
    m_reproductionTimer = m_reproductionTicks;
}
