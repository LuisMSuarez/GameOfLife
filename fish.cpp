#include "fish.h"

Fish::Fish(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge)
    : Creature(world, cell, reproductionTicks, maxAge, resourcePath, startingAge)
{

}

Fish::~Fish()
{

}

std::string Fish::getResource()
{
    std::array<std::string, 1> resources
        {
            "/home/luismi/Documents/repos/GameOfLife/resources/fish.jpg",
            //"/home/luismi/Documents/repos/GameOfLife/resources/fish1.jpg",
            // "/home/luismi/Documents/repos/GameOfLife/resources/fish2.jpg",
            // "/home/luismi/Documents/repos/GameOfLife/resources/fish3.jpg",
            // "/home/luismi/Documents/repos/GameOfLife/resources/fish4.jpg"
        };

    // Generate a random number between 0 and 3
    int index = rand() % resources.size();
    return resources[index];
}

uint32_t Fish::s_reproductionTicks = 10;
uint32_t Fish::s_maxAge = 35;

void Fish::tick()
{
    Creature::tick();

    auto neighboringCells = m_world.getNeighboringCellsShuffled(*m_cell);
    for (const auto cell: neighboringCells)
    {
        if (cell->isEmpty())
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
