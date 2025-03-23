#include "cell.h"

using namespace gameOfLifeCore;

gameOfLifeCore::Cell::Cell()
{
    m_creature = nullptr;
}

gameOfLifeCore::Cell::~Cell()
{
    destroyCreature();
}

// We need a separate method to this, outside of the constructor
// given that we use the vector::resize method that requires a default constructor
void gameOfLifeCore::Cell::setCoordinates(uint32_t row, uint32_t col)
{
    m_row = row;
    m_col = col;
}

uint32_t gameOfLifeCore::Cell::getRow() const
{
    return m_row;
}

uint32_t gameOfLifeCore::Cell::getCol() const
{
    return m_col;
}

void gameOfLifeCore::Cell::addCreature(Creature *creature)
{
    m_creature = creature;
}

Creature* gameOfLifeCore::Cell::getCreature()
{
    return m_creature;
}

bool gameOfLifeCore::Cell::isEmpty()
{
    return m_creature == nullptr;
}

void gameOfLifeCore::Cell::removeCreature()
{
    m_creature = nullptr;
}

void gameOfLifeCore::Cell::destroyCreature()
{
    if (m_creature != nullptr)
    {
        delete m_creature;
        m_creature = nullptr;
    }
}

