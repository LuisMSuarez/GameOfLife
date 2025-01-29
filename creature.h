#pragma once

#include "world.h"
#include "cell.h"
#include <string>
#include <array>

class World; // Forward declaration
class Cell;

/**
 * @brief The Creature class represents a creature in the simulation.
 */
class Creature
{
    public:
        /**
         * @brief Constructor for the Creature class.
         *
         * @param world Reference to the World object.
         * @param cell Reference to the Cell object.
         * @param reproductionTicks Number of ticks required for reproduction.
         * @param maxAge Maximum age of the creature.
         * @param resourcePath Path to the resource file.
         * @param startingAge Initial age of the creature.
         */
        Creature(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge = 0);

        /**
         * @brief Destructor for the Creature class.
         */
        ~Creature();

        /**
         * @brief Advances the state of the creature by one tick.
         */
        virtual void tick();

        /**
         * @brief Checks if the creature has reached its maximum age.
         *
         * @return True if the creature has reached its maximum age, false otherwise.
         */
        bool reachedMaxAge();

        /**
         * @brief Gets the current cell of the creature.
         *
         * @return Reference to the current Cell object.
         */
        Cell& getCell();

        /**
         * @brief Tags the creature for deletion.
         */
        void tagForDeletion();

        /**
         * @brief Checks if the creature is tagged for deletion.
         *
         * @return True if tagged for deletion, false otherwise.
         */
        bool isTaggedForDeletion();

        /**
         * @brief Gets the resource path of the creature.
         *
         * @return The resource path as a string.
         */
        std::string getResourcePath();

    protected:
        /**
         * @brief Checks if the creature has reached the time to reproduce.
         *
         * @return True if the creature has reached the time to reproduce, false otherwise.
         */
        bool reachedTimeToReproduce();

        /**
         * @brief Resets the reproduction timer of the creature.
         */
        void resetTimeToReproduce();

        /**
         * @brief Moves the creature to a new cell.
         *
         * @param cell Reference to the new Cell object.
         */
        void moveTo(Cell &cell);

        uint32_t m_age;                 ///< Age of the creature.
        uint32_t m_reproductionTimer;   ///< Timer for reproduction.
        uint32_t m_reproductionTicks;   ///< Number of ticks required for reproduction.
        World &m_world;                 ///< Reference to the world the creature belongs to.
        Cell *m_cell;                   ///< Pointer to the current cell of the creature.

    private:
        uint32_t m_max_age;             ///< Maximum age of the creature.
        bool m_taggedForDeletion;       ///< Flag indicating if the creature is tagged for deletion.
        std::string m_resourcePath;     ///< Path to the resource file.
};
