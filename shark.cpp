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
    auto neighboringCells = m_world.getNeighboringCellsShuffled(*m_cell);

    // default movement behavior for sharks is to move by eating a neighboring fish
    for (const auto cell: neighboringCells)
    {
        if (auto creature = cell->getCreature(); creature != nullptr)
        {
            if (auto fish = dynamic_cast<Fish*>(creature); fish != nullptr)
            {
                cell->getCreature()->tagForDeletion();
                moveTo(*cell);
                m_age++;
                return;
            }
        }
    }

    // fallback to default behavior to move to an empty neighboring cell
    for (const auto cell: neighboringCells)
    {
        if (cell->getCreature() == nullptr)
        {
            moveTo(*cell);
            break;
        }
    }
}
