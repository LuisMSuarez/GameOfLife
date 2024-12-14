#include "cell.h"


Cell::Cell()
{
    m_creature = nullptr;
}

Cell::~Cell()
{
    destroyCreature();
}

// We need a separate method to this, outside of the constructor
// given that we use the vector::resize method that requires a default constructor
void Cell::setCoordinates(uint32_t row, uint32_t col)
{
    m_row = row;
    m_col = col;
}

uint32_t Cell::getRow() const
{
    return m_row;
}

uint32_t Cell::getCol() const
{
    return m_col;
}

void Cell::addCreature(Creature *creature)
{
    m_creature = creature;
}

Creature* Cell::getCreature()
{
    return m_creature;
}

void Cell::removeCreature()
{
    m_creature = nullptr;
}

void Cell::destroyCreature()
{
    if (m_creature != nullptr)
    {
        delete m_creature;
        m_creature = nullptr;
    }
}

