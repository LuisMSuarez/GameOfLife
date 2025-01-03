#include "creature.h"

Creature::Creature(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge) :
    m_world(world), m_cell(&cell), m_reproductionTicks(reproductionTicks), m_max_age(maxAge), m_resourcePath(resourcePath), m_age(startingAge)
{
    m_reproductionTimer = reproductionTicks;
    m_taggedForDeletion = false;
}

Creature::~Creature()
{
}

void Creature::moveTo(Cell &cell)
{
    m_cell->removeCreature();
    cell.addCreature(this);
    m_cell = &cell;
}

Cell& Creature::getCell()
{
    return *m_cell;
}

void Creature::tagForDeletion()
{
    m_taggedForDeletion = true;
    m_cell = nullptr;
}

bool Creature::isTaggedForDeletion()
{
    return m_taggedForDeletion;
}

std::string Creature::getResourcePath()
{
    return m_resourcePath;
}

void Creature::tick()
{
    m_age++;
    if (m_reproductionTimer > 0)
    {
        m_reproductionTimer--;
    }
}

bool Creature::reachedMaxAge()
{
    return m_age >= m_max_age;
}

bool Creature::reachedTimeToReproduce()
{
    return m_reproductionTimer <= 0;
}

void Creature::resetTimeToReproduce()
{
    m_reproductionTimer = m_reproductionTicks;
}
