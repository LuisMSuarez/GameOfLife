#pragma once

#include "creatureType.h"
#include "creature.h"
#include "world.h"
#include "cell.h"

namespace GameOfLifeCore
{
class World;
class Creature;
class Cell;

/**
 * @class CreatureFactory
 * @brief Factory class for creating creatures.
 */
class CreatureFactory
{
    public:
        /**
         * @brief Creates a creature of the specified type.
         * @param type The type of the creature to create (fish or shark).
         * @param world Reference to the world where the creature will be placed.
         * @param cell Reference to the cell where the creature will be placed.
         * @param randomInitialization Optional parameter to randomize initial values for the creature so that not all creatures are initialized the same. Default is false.
         * @return A reference to the created creature.
         */
        static Creature& Create(CreatureType type, World &world, Cell &cell, bool randomInitialization = false);
};
}
