#include "shark.h"
#include "fish.h"

using namespace GameOfLifeCore;

GameOfLifeCore::Shark::Shark(World &world, Cell &cell, uint32_t reproductionTimer, uint32_t maxAge, uint32_t initialEnergy, std::string resourcePath, uint32_t startingAge) noexcept
    : Creature(world, cell, reproductionTimer, maxAge, resourcePath, startingAge), m_energy(initialEnergy)
{
}

std::string GameOfLifeCore::Shark::getResource() noexcept
{
    std::array<std::string, 1> resources
    {
        ":/sharks/shark-default",
        // uncomment as many lines from below as different variations of the creature is desired
        //":/sharks/shark1",
        //":/sharks/shark2",
        //":/sharks/shark3",
        //":/sharks/shark4",
    };

    // Generate a random number between 0 and 3
    int index = rand() % resources.size();
    return resources[index];
}

uint32_t Shark::s_reproductionTicks = 15;
uint32_t Shark::s_maxAge = 50;
uint32_t Shark::s_initialEnergy = 10;
uint32_t Shark::s_energyPerFish = 10;

void GameOfLifeCore::Shark::tick() noexcept
{
    Creature::tick();

    if (isTaggedForDeletion())
    {
        return;
    }

    loseEnergy(1); // Lose energy every tick

    auto *oldPosition = m_cell;
    auto neighboringCells = m_world.getNeighboringCellsShuffled(*m_cell);

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
                gainEnergy(s_energyPerFish); // Gain energy when eating a fish
                break;
            }
        }
    }

    // if the shark didn't eat a fish,
    // fallback to default behavior to move to an empty neighboring cell
    if (oldPosition == m_cell)
    {
        for (const auto cell: neighboringCells)
        {
            if (cell->isEmpty())
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

    checkEnergy(); // Check if the shark runs out of energy
}

void GameOfLifeCore::Shark::gainEnergy(int amount) noexcept
{
    m_energy += amount;
}

void GameOfLifeCore::Shark::loseEnergy(int amount) noexcept
{
    m_energy -= amount;
}

void GameOfLifeCore::Shark::checkEnergy() noexcept
{
    if (m_energy <= 0)
    {
        tagForDeletion(); // The shark dies if it runs out of energy
    }
}
