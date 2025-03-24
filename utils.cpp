#include "utils.h"
#include "cell.h"

int GameOfLifeCore::Utils::countCreatures(World &world)
{
    int count = 0;
    for (auto &cell : world)
    {
        if (cell.getCreature() != nullptr)
        {
            count++;
        }
    }

    return count;
}
