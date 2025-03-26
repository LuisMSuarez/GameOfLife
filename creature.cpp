#include <cassert>    // assert
#include "creature.h"

using namespace GameOfLifeCore;

GameOfLifeCore::Creature::Creature(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge, uint32_t startingReproductionTimer) noexcept :
    m_world(world), m_cell(&cell), m_reproductionTicks(reproductionTicks), m_reproductionTimer(startingReproductionTimer), m_max_age(maxAge), m_resourcePath(resourcePath), m_age(startingAge)
{
    m_taggedForDeletion = false;
    cell.addCreature(this);
    world.registerCreature(*this);
}

void GameOfLifeCore::Creature::moveTo(Cell &cell) noexcept
{
    assert(cell.getCreature() == nullptr); // the destination cell must not already be occupied by another creature
    m_cell->removeCreature();
    cell.addCreature(this);
    m_cell = &cell;
}

Cell* GameOfLifeCore::Creature::getCell() noexcept
{
    return m_cell;
}

void GameOfLifeCore::Creature::tagForDeletion() noexcept
{
    if (m_cell != nullptr)
    {
        // the creature may have already been evicted from its cell such as if it was eaten by another creature
        m_cell->removeCreature();
    }
    m_taggedForDeletion = true;
    m_cell = nullptr;
}

bool GameOfLifeCore::Creature::isTaggedForDeletion() noexcept
{
    return m_taggedForDeletion;
}

std::string GameOfLifeCore::Creature::getResourcePath() noexcept
{
    return m_resourcePath;
}

void GameOfLifeCore::Creature::tick() noexcept
{
    m_age++;
    if (reachedMaxAge())
    {
        tagForDeletion();
    }

    m_reproductionTimer++;
}

bool GameOfLifeCore::Creature::reachedMaxAge() const noexcept
{
    return m_age >= m_max_age;
}

bool GameOfLifeCore::Creature::reachedTimeToReproduce() const noexcept
{
    return m_reproductionTimer >= m_reproductionTicks;
}

void GameOfLifeCore::Creature::resetTimeToReproduce() noexcept
{
    m_reproductionTimer = 0;
}
