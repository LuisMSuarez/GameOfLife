#pragma once

#include <vector>    // std::vector
#include <cstddef>   // std::size_t
#include <cstdint>   // std::int*_t
#include "cell.h"
#include "creatureType.h"
#include "creaturefactory.h"

class Cell;

class World
{
    public:
        World();
        ~World();
        void initialize(uint32_t rowCount, uint32_t colCount);
        Cell& operator()(const uint32_t row, const uint32_t col);

        void tick();
        void newWorld(uint32_t rowCount, uint32_t colCount);
        void addCreatures(CreatureType type, uint32_t count, bool randomAge = false);
        std::int32_t rowCount() const noexcept;
        std::int32_t colCount() const noexcept;

        // iterator access
        std::vector<Cell>::iterator begin() noexcept;
        std::vector<Cell>::iterator end() noexcept;
        std::vector<Cell>::const_iterator cbegin();
        std::vector<Cell>::const_iterator cend();
        std::vector<Cell*> getNeighboringCellsShuffled(const Cell &position);
    private:
        // variables
        uint32_t m_cols;
        uint32_t m_rows;
        std::vector<Cell> m_map;

        // methods
        [[nodiscard]] constexpr std::size_t IX(const uint32_t row, const uint32_t col) const noexcept;
        std::vector<Cell*> getFreeCellsShuffled();
        void checkMapCoordinatesAndAdd(uint32_t row, uint32_t col, Cell &cell, std::vector<Cell*> &list);
};
