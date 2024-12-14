#include "world.h"
#include <algorithm>
#include <random>
#include "fish.h"
#include "shark.h"

World::World()
{

}

World::~World()
{
    for (auto &cell: m_map)
    {
        cell.destroyCreature();
    }
}

void World::initialize(uint32_t rowCount, uint32_t colCount)
{
    for (auto &cell : m_map)
    {
        cell.destroyCreature();
    }
    m_rows = rowCount;
    m_cols = colCount;
    m_map.resize(m_rows*m_cols);

    for (uint32_t row; row < m_rows; row++)
    {
        for (uint32_t col; col < m_cols; col++)
        {
            this->operator()(row,col).setCoordinates(row, col);
        }
    }
}

Cell& World::operator()(const uint32_t row, const uint32_t col)
{
    return m_map[IX(row,col)];
}

std::int32_t World::rowCount() const noexcept
{
    return m_rows;
}

std::int32_t World::colCount() const noexcept
{
    return m_cols;
}

void World::tick()
{
    for (auto &cell : m_map)
    {
        if (auto creature = cell.getCreature(); creature != nullptr)
        {
            if (creature->reachedMaxAge())
            {
               cell.destroyCreature();
            }
            else
            {
                creature->tick();
            }
        }
    }
}

std::vector<Cell*> World::getFreeCellsShuffled()
{
    std::vector<Cell*> freeCells;
    for (auto &cell : m_map)
    {
        if (auto creature = cell.getCreature(); creature == nullptr)
        {
            freeCells.push_back(&cell);
        }
    }

    // Create a random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector
    std::shuffle(freeCells.begin(), freeCells.end(), g);

    return freeCells;
}

void World::checkMapCoordinatesAndAdd(uint32_t row, uint32_t col, Cell &cell, std::vector<Cell*> &list)
{
    if( (row >= 0) && (col >= 0) & (row < m_rows) && (col < m_cols) )
    {
        list.push_back(&cell);
    }
}

std::vector<Cell*> World::getNeighboringCellsShuffled(const Cell &position)
{
    uint32_t row = position.getRow();
    uint32_t col = position.getCol();
    std::vector<Cell*> neighboringCells;

    checkMapCoordinatesAndAdd(row-1, col-1, this->operator()(row-1, col-1), neighboringCells);
    checkMapCoordinatesAndAdd(row-1, col, this->operator()(row-1, col), neighboringCells);
    checkMapCoordinatesAndAdd(row-1, col+1, this->operator()(row-1, col+1), neighboringCells);
    checkMapCoordinatesAndAdd(row, col+1, this->operator()(row, col+1), neighboringCells);
    checkMapCoordinatesAndAdd(row+1, col+1, this->operator()(row+1, col+1), neighboringCells);
    checkMapCoordinatesAndAdd(row+1, col, this->operator()(row+1, col), neighboringCells);
    checkMapCoordinatesAndAdd(row-1, col-1, this->operator()(row-1, col-1), neighboringCells);
    checkMapCoordinatesAndAdd(row, col-1, this->operator()(row, col-1), neighboringCells);

    // Create a random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector
    std::shuffle(neighboringCells.begin(), neighboringCells.end(), g);

    return neighboringCells;
}

void World::addCreatures(CreatureType type, uint32_t count)
{
    Creature *newCreature = nullptr;
    auto freeCells = getFreeCellsShuffled();

    for (int i= 1; i<= count; i++)
    {
        if (freeCells.size() < 1)
        {
            break;
        }

        auto cell = freeCells.back();
        switch(type)
        {
            case CreatureType::fish:
                newCreature = new Fish(this, cell, Fish::s_reproductionAge, Fish::s_maxAge);
            break;
            case CreatureType::shark:
                newCreature = new Shark(this, cell, Shark::s_reproductionAge, Shark::s_maxAge);
            break;
        }
        cell->addCreature(newCreature);
        freeCells.pop_back();
    }
}

std::vector<Cell>::iterator World::begin() noexcept
{
    return m_map.begin();
}

std::vector<Cell>::iterator World::end() noexcept
{
    return m_map.end();
}

std::vector<Cell>::const_iterator World::cbegin()
{
    return m_map.cbegin();
}

std::vector<Cell>::const_iterator World::cend()
{
    return m_map.cend();
}

[[nodiscard]] constexpr std::size_t World::IX(const uint32_t row, const uint32_t col) const noexcept
{
    return static_cast<std::size_t>(col) + static_cast<std::size_t>(m_cols) * static_cast<std::size_t>(row);
}
