#include "world.h"
#include <algorithm>
#include <random>
#include "fish.h"

World::World()
{

}

World::~World()
{
    for (auto& cell: m_map)
    {
        cell.destroyCreature();
    }
}

void World::initialize(uint32_t rowCount, uint32_t colCount)
{
    for (auto cellIterator = m_map.begin(); cellIterator != m_map.end(); cellIterator++)
    {
        cellIterator->destroyCreature();
    }
    m_map.resize(rowCount*colCount);
    m_rows = rowCount;
    m_cols = colCount;
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
    for (auto cellIterator = m_map.begin(); cellIterator != m_map.end(); cellIterator++)
    {
        if (auto creature = cellIterator->getCreature(); creature != nullptr)
        {
            if (creature->reachedMaxAge())
            {
               cellIterator->destroyCreature();
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
    for (auto cellIterator= m_map.begin(); cellIterator!=m_map.end(); cellIterator++)
    {
        if (auto creature = cellIterator->getCreature(); creature == nullptr)
        {
            freeCells.push_back(&(*cellIterator));
        }
    }

    // Create a random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector
    std::shuffle(freeCells.begin(), freeCells.end(), g);

    return freeCells;
}

void World::addFish(uint32_t numFish)
{
    auto freeCells = getFreeCellsShuffled();

    for (int i= 1; i<= numFish; i++)
    {
        Fish *f = new Fish(this, Fish::s_reproductionAge, Fish::s_maxAge);
        auto cell = freeCells.back();
        cell->addCreature(f);
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
