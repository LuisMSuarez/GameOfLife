#pragma once

#include <vector>    // std::vector
#include <cstddef>   // std::size_t
#include <cstdint>   // std::int*_t
#include <unordered_set> // std::unordered_set
#include <random>
#include "cell.h"
#include "creatureType.h"
#include "creaturefactory.h"

namespace GameOfLifeCore
{

class Cell;

/**
 * @class World
 * @brief Represents the simulation world containing cells and creatures.
 */
class World
{
    public:
        /**
         * @brief Constructs a World object.
         */
        World() noexcept;

        /**
         * @brief Destructor for the World class.
         */
        ~World();

        /**
         * @brief Initializes the world with the specified number of rows and columns.
         * @param rowCount Number of rows.
         * @param colCount Number of columns.
         */
        void initialize(uint32_t rowCount, uint32_t colCount);

        /**
         * @brief Accesses a cell at the specified row and column.
         * @param row Row index.
         * @param col Column index.
         * @return Reference to the cell at the specified position.
         */
        Cell& operator()(const uint32_t row, const uint32_t col);

        /**
         * @brief Advances the simulation by one tick.
         */
        void tick() noexcept;

        /**
         * @brief Creates creatures of the specified type to the world.
         * @param type The type of creatures to add (fish or shark).
         * @param count The number of creatures to add.
         * @param randomAge Optional parameter to assign a random age to the creatures. Default is false.
         */
        void createCreatures(CreatureType type, uint32_t count, bool randomAge = false) noexcept;

        /**
         * @brief Adds a creature to the list of creatures that exist in the world.
         * @param creature The creature object.
         */
        void addCreature(Creature& creature);

        /**
         * @brief Gets neighboring cells of a given cell in a shuffled order.
         * @param position Reference to the cell whose neighbors are to be retrieved.
         * @return A vector of pointers to neighboring cells.
         */
        std::vector<Cell*> getNeighboringCellsShuffled(const Cell &position) noexcept;

        /**
         * @brief Gets the number of rows in the world.
         * @return Number of rows.
         */
        std::int32_t rowCount() const noexcept;

        /**
         * @brief Gets the number of columns in the world.
         * @return Number of columns.
         */
        std::int32_t colCount() const noexcept;

        // Iterator access

        /**
         * @brief Gets an iterator to the beginning of the cell map.
         * @return Iterator to the beginning of the cell map.
         */
        std::vector<Cell>::iterator begin() noexcept;

        /**
         * @brief Gets an iterator to the end of the cell map.
         * @return Iterator to the end of the cell map.
         */
        std::vector<Cell>::iterator end() noexcept;

        /**
         * @brief Gets a constant iterator to the beginning of the cell map.
         * @return Constant iterator to the beginning of the cell map.
         */
        std::vector<Cell>::const_iterator cbegin() noexcept;

        /**
         * @brief Gets a constant iterator to the end of the cell map.
         * @return Constant iterator to the end of the cell map.
         */
        std::vector<Cell>::const_iterator cend() noexcept;

    private:
        uint32_t m_cols; /**< Number of columns in the world. */
        uint32_t m_rows; /**< Number of rows in the world. */
        std::vector<Cell> m_map; /**< Map of cells in the world. */
        std::unordered_set<Creature*> m_creatures; /**< Set of creatures in the world. */
        std::mt19937 m_randomGenerator;

        /**
         * @brief Gets a shuffled list of free cells.
         * @return A vector of pointers to free cells.
         */
        std::vector<Cell*> getFreeCellsShuffled() noexcept;

        /**
         * @brief Gets the index of a cell given its row and column.
         * @param row Row index.
         * @param col Column index.
         * @return Index of the cell.
         */
        [[nodiscard]] constexpr std::size_t IX(const uint32_t row, const uint32_t col) const noexcept;

        /**
         * @brief Checks map coordinates and adds the cell to the list if valid.
         * @param row Row index.
         * @param col Column index.
         * @param list Reference to the list of cells.
         */
        void checkMapCoordinatesAndAdd(uint32_t row, uint32_t col, std::vector<Cell*> &list) noexcept;
};
}
