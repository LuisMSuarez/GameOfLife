#include "shark.h"
#include "fish.h"

Shark::Shark(World &world, Cell &cell, uint32_t reproductionAge, uint32_t maxAge)
    : Creature(world, cell, reproductionAge, maxAge)
{
}

Shark::~Shark()
{
}

uint32_t Shark::s_reproductionAge = 15;
uint32_t Shark::s_maxAge = 50;

void Shark::tick()
{
    m_age++;
    bool movedByEating = false;

    auto neighboringCells = m_world.getNeighboringCellsShuffled(*m_cell);
    for (const auto cell: neighboringCells)
    {
        if (auto creature = cell->getCreature(); creature != nullptr)
        {
            if (auto fish = dynamic_cast<Fish*>(creature); fish != nullptr)
            {
                cell->getCreature()->tagForDeletion();
                moveTo(*cell);
                movedByEating = true;
                break;
            }
        }
    }

    if (!movedByEating)
    {
        // fallback to default behavior
        Creature::tick();
    }
}
