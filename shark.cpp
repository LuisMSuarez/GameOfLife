#include "shark.h"
#include "fish.h"

Shark::Shark(World &world, Cell &cell, uint32_t reproductionTimer, uint32_t maxAge)
    : Creature(world, cell, reproductionTimer, maxAge)
{
}

Shark::~Shark()
{
}

uint32_t Shark::s_reproductionTicks = 15;
uint32_t Shark::s_maxAge = 50;

void Shark::tick()
{
    m_age++;
    if (m_reproductionTimer > 0)
    {
        m_reproductionTimer--;
    }

    auto neighboringCells = m_world.getNeighboringCellsShuffled(*m_cell);
    Cell *oldPosition = m_cell;
    bool movedByEating = false;

    // default movement behavior for sharks is to move by eating a neighboring fish
    for (const auto cell: neighboringCells)
    {
        if (auto creature = cell->getCreature(); creature != nullptr)
        {
            if (auto fish = dynamic_cast<Fish*>(creature); fish != nullptr)
            {
                // we don't immediately destroy the fish object, as it may exist in a collection
                // governed by the world, which will orchestrate destruction of these objects
                // at the end of the tick.
                fish->tagForDeletion();
                moveTo(*cell);
                movedByEating = true;

                break;
            }
        }
    }

    // fallback to default behavior to move to an empty neighboring cell
    if (!movedByEating)
    {
        for (const auto cell: neighboringCells)
        {
            if (cell->getCreature() == nullptr)
            {
                moveTo(*cell);
                break;
            }
        }
    }

    // as the shark moves, we spawn a new shark in our old position
    if (reachedTimeToReproduce() && (oldPosition != m_cell))
    {
         CreatureFactory::Create(CreatureType::shark, m_world, *oldPosition);
         resetTimeToReproduce();
    }
}
