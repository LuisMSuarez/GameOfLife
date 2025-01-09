#pragma once

#include "creature.h"
#include <array>

/**
 * @class Fish
 * @brief Represents a fish in the simulation.
 *
 * The Fish class is a derived class from Creature, representing fish entities
 * in the Wa-Tor simulation. It includes properties and behaviors specific to fish.
 */
class Fish : public Creature
{
    public:
        /**
         * @brief Constructs a Fish object.
         * @param world Reference to the world where the fish lives.
         * @param cell Reference to the cell where the fish is located.
         * @param reproductionTicks Number of ticks required for reproduction.
         * @param maxAge Maximum age of the fish.
         * @param resourcePath Path to the resource file associated with the fish.
         * @param startingAge Optional parameter to set the starting age of the fish. Default is 0.
         */
        Fish(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge = 0);

        /**
         * @brief Destructor for the Fish class.
         */
        ~Fish();

        /**
         * @brief Performs actions for each tick of the simulation.
         *
         * This function is called every tick to update the state of the fish,
         * including movement, aging, and reproduction.
         */
        void tick() override;

        /** Static member variable representing the number of ticks required for reproduction. */
        static uint32_t s_reproductionTicks;

        /** Static member variable representing the maximum age of the fish. */
        static uint32_t s_maxAge;

        /**
         * @brief Gets the resource path associated with the fish.
         * @return The resource path as a string.
         */
        static std::string getResource();
};
