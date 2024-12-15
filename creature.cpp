#include "creature.h"

Creature::Creature(World &world, Cell &cell, uint32_t reproductionAge, uint32_t maxAge, uint32_t age) :
    m_world(world), m_cell(&cell), m_reproduction_age(reproductionAge), m_max_age(maxAge)
{
    m_age = age;
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
