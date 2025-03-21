#include "utils.h"
#include "cell.h"

int Utils::countCreatures(World &world)
{
    int count = 0;
    for (Cell &cell : world)
    {
        if (cell.getCreature() != nullptr)
        {
            count++;
        }
    }

    return count;
}
