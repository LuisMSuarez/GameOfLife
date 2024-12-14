#include "creature.h"

Creature::Creature(World *world, Cell* cell, uint32_t reproductionAge, uint32_t maxAge) :
    m_world(world), m_cell(cell), m_reproduction_age(reproductionAge), m_max_age(maxAge)
{

}

Creature::~Creature()
{
}

void Creature::tick()
{
    m_age++;

    auto neighboringCells = m_world->getNeighboringCellsShuffled(*m_cell);
    for (auto cell: neighboringCells)
    {
        if (cell->getCreature() != nullptr)
        {
            cell->addCreature(this);
            m_cell->removeCreature();
            break;
        }
    }
}

bool Creature::reachedMaxAge()
{
    return m_age >= m_max_age;
}

bool Creature::reachedTimeToReproduce()
{
    return m_timeToReproduce <= 0;
}

void Creature::resetTimeToReproduce()
{
    m_timeToReproduce = m_reproduction_age;
}
