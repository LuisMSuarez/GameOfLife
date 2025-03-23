#include "cell.h"

using namespace GameOfLifeCore;

GameOfLifeCore::Cell::Cell()
{
    m_creature = nullptr;
}

GameOfLifeCore::Cell::~Cell()
{
    destroyCreature();
}

// We need a separate method to this, outside of the constructor
// given that we use the vector::resize method that requires a default constructor
void GameOfLifeCore::Cell::setCoordinates(uint32_t row, uint32_t col)
{
    m_row = row;
    m_col = col;
}

uint32_t GameOfLifeCore::Cell::getRow() const
{
    return m_row;
}

uint32_t GameOfLifeCore::Cell::getCol() const
{
    return m_col;
}

void GameOfLifeCore::Cell::addCreature(Creature *creature)
{
    m_creature = creature;
}

Creature* GameOfLifeCore::Cell::getCreature()
{
    return m_creature;
}

bool GameOfLifeCore::Cell::isEmpty()
{
    return m_creature == nullptr;
}

void GameOfLifeCore::Cell::removeCreature()
{
    m_creature = nullptr;
}

void GameOfLifeCore::Cell::destroyCreature()
{
    if (m_creature != nullptr)
    {
        delete m_creature;
        m_creature = nullptr;
    }
}

