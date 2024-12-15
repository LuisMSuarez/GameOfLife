#include "fish.h"


Fish::Fish(World &world, Cell &cell, uint32_t reproductionAge, uint32_t maxAge)
    : Creature(world, cell, reproductionAge, maxAge)
{

}

Fish::~Fish()
{

}

uint32_t Fish::s_reproductionAge = 10;
uint32_t Fish::s_maxAge = 35;

void Fish::tick()
{
    m_age++;
    auto neighboringCells = m_world.getNeighboringCellsShuffled(*m_cell);
    for (const auto cell: neighboringCells)
    {
        if (cell->getCreature() == nullptr)
        {
            Cell *currentCell = m_cell;
            moveTo(*cell);
            // if (reachedTimeToReproduce())
            // {
            //     CreatureFactory::Create(CreatureType::fish, m_world, *currentCell);
            //}

            break;
        }
    }
}
