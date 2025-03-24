#include <cassert>    // assert
#include "creature.h"

using namespace GameOfLifeCore;

GameOfLifeCore::Creature::Creature(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge) :
    m_world(world), m_cell(&cell), m_reproductionTicks(reproductionTicks), m_max_age(maxAge), m_resourcePath(resourcePath), m_age(startingAge)
{
    m_reproductionTimer = reproductionTicks;
    m_taggedForDeletion = false;
    cell.addCreature(this);
}

void GameOfLifeCore::Creature::moveTo(Cell &cell)
{
    assert(cell.getCreature() == nullptr); // the destination cell must not already be occupied by another creature
    m_cell->removeCreature();
    cell.addCreature(this);
    m_cell = &cell;
}

Cell& GameOfLifeCore::Creature::getCell()
{
    return *m_cell;
}

void GameOfLifeCore::Creature::tagForDeletion()
{
    m_cell->removeCreature();
    m_taggedForDeletion = true;
    m_cell = nullptr;
}

bool GameOfLifeCore::Creature::isTaggedForDeletion()
{
    return m_taggedForDeletion;
}

std::string GameOfLifeCore::Creature::getResourcePath()
{
    return m_resourcePath;
}

void GameOfLifeCore::Creature::tick()
{
    m_age++;
    if (m_reproductionTimer > 0)
    {
        m_reproductionTimer--;
    }
}

bool GameOfLifeCore::Creature::reachedMaxAge() const
{
    return m_age >= m_max_age;
}

bool GameOfLifeCore::Creature::reachedTimeToReproduce() const
{
    return m_reproductionTimer <= 0;
}

void GameOfLifeCore::Creature::resetTimeToReproduce()
{
    m_reproductionTimer = m_reproductionTicks;
}
