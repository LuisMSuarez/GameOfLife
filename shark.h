#pragma once

#include "creature.h"

/**
 * @class Shark
 * @brief Represents a shark in the simulation.
 *
 * The Shark class is a derived class from Creature, representing shark entities
 * in the Wa-Tor simulation. It includes properties and behaviors specific to sharks.
 */
class Shark : public Creature
{
    public:
        /**
         * @brief Constructs a Shark object.
         * @param world Reference to the world where the shark lives.
         * @param cell Reference to the cell where the shark is located.
         * @param reproductionTicks Number of ticks required for reproduction.
         * @param maxAge Maximum age of the shark.
         * @param resourcePath Path to the resource file associated with the shark.
         * @param startingAge Optional parameter to set the starting age of the shark. Default is 0.
         */
        Shark(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge = 0);

        /**
         * @brief Destructor for the Shark class.
         */
        ~Shark();

        /**
         * @brief Performs actions for each tick of the simulation.
         *
         * This function is called every tick to update the state of the shark,
         * including movement, aging, energy management, and reproduction.
         */
        void tick() override;

        /** Static member variable representing the number of ticks required for reproduction. */
        static uint32_t s_reproductionTicks;

        /** Static member variable representing the maximum age of the shark. */
        static uint32_t s_maxAge;

        /** Static member variable representing the initial energy of the shark. */
        static uint32_t s_initialEnergy;

        /** Static member variable representing the energy gained per fish eaten. */
        static uint32_t s_energyPerFish;

        /**
         * @brief Gets the resource path associated with the shark.
         * @return The resource path as a string.
         */
        static std::string getResource();

    private:
        int m_energy; /**< Current energy of the shark. */

        /**
         * @brief Increases the shark's energy.
         * @param amount The amount of energy to gain.
         */
        void gainEnergy(int amount);

        /**
         * @brief Decreases the shark's energy.
         * @param amount The amount of energy to lose.
         */
        void loseEnergy(int amount);

        /**
         * @brief Checks the shark's energy and updates its state accordingly.
         */
        void checkEnergy();
};
