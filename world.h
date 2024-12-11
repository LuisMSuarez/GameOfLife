#pragma once

#include <vector>    // std::vector
#include <cstddef>   // std::size_t
#include <cstdint>   // std::int*_t
#include "cell.h"

class Cell;

class World
{
    public:
        World();
        ~World();
    private:
        // variables
        uint32_t m_cols;
        uint32_t m_rows;
        std::vector<Cell> m_map;

        // methods
        [[nodiscard]] constexpr std::size_t IX(const uint32_t row, const uint32_t col) const noexcept;
};
