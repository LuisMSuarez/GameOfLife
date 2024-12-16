#include "fish.h"


Fish::Fish(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge)
    : Creature(world, cell, reproductionTicks, maxAge)
{

}

Fish::~Fish()
{

}

uint32_t Fish::s_reproductionTicks = 10;
uint32_t Fish::s_maxAge = 35;

void Fish::tick()
{
    m_age++;
    if (m_reproductionTimer > 0)
    {
        m_reproductionTimer--;
    }

    auto neighboringCells = m_world.getNeighboringCellsShuffled(*m_cell);
    for (const auto cell: neighboringCells)
    {
        if (cell->getCreature() == nullptr)
        {
            Cell *oldPosition = m_cell;
            moveTo(*cell);

            // as we move, we spawn a new fish in our old position
            if (reachedTimeToReproduce())
            {
                 CreatureFactory::Create(CreatureType::fish, m_world, *oldPosition);
                 resetTimeToReproduce();
            }

            return;
        }
    }
}
