#include "cell.h"


Cell::Cell()
{
    m_creature = nullptr;
}

Cell::~Cell()
{
    destroyCreature();
}

void Cell::addCreature(Creature *creature)
{
    m_creature = creature;
}

Creature* Cell::getCreature()
{
    return m_creature;
}

void Cell::destroyCreature()
{
    if (m_creature != nullptr)
    {
        delete m_creature;
        m_creature = nullptr;
    }
}

