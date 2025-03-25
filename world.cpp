#include "world.h"
#include <algorithm>
#include <random>
#include <stdexcept> // std::runtime_error
#include "fish.h"
#include "shark.h"

using namespace GameOfLifeCore;

GameOfLifeCore::World::World() noexcept
{
    m_map.clear();
}

GameOfLifeCore::World::~World()
{
    for (auto &cell: m_map)
    {
        cell.destroyCreature();
    }
}

void GameOfLifeCore::World::initialize(uint32_t rowCount, uint32_t colCount)
{
    if (rowCount <=0 || colCount <=0)
    {
        throw std::runtime_error("Row count and col count must be greater than zero.");
    }

    for (auto &cell : m_map)
    {
        cell.destroyCreature();
    }
    m_rows = rowCount;
    m_cols = colCount;
    m_map.resize(m_rows*m_cols);

    for (uint32_t row = 0; row < m_rows; row++)
    {
        for (uint32_t col = 0; col < m_cols; col++)
        {
            this->operator()(row,col).setCoordinates(row, col);
        }
    }

    m_creatures.clear();
}

Cell& GameOfLifeCore::World::operator()(const uint32_t row, const uint32_t col)
{
    if (row >= m_rows || col >= m_cols)
    {
        throw std::runtime_error("Row and col must be within wold size.");
    }

    return m_map[IX(row,col)];
}

std::int32_t GameOfLifeCore::World::rowCount() const noexcept
{
    return m_rows;
}

std::int32_t GameOfLifeCore::World::colCount() const noexcept
{
    return m_cols;
}

void GameOfLifeCore::World::tick() noexcept
{
    // Step 1:: enumerate all creatures
    // ensure we call tick() for each creature exactly once by forming
    // a collection with all the creatures in the map, instead of by iterating through the map
    // as we may be calling tick() on the same creature multiple times (due to movement) otherwise
    // this is achieved with m_creatures;

    // Step 2: call the tick function on all creature, keeping in mind that the creature may have already been
    // 'eaten' by the movement of a prior creature
    for (const auto creature: m_creatures)
    {
        if (!creature->isTaggedForDeletion())
        {
            creature->tick();
        }
    }

    // Step 3: cleanup creatures that have either been eaten or died by old age
    // we need to exercise special care when deleting creature in a loop that is iterating over the collection itself
    for (auto creature_iterator=m_creatures.begin(); creature_iterator != m_creatures.end();)
    {
        if ((*creature_iterator)->isTaggedForDeletion())
        {
            auto creature = *creature_iterator;
            auto cell = creature->getCell();
            if (cell != nullptr) // a creature that has been eaten by another creature no longer occupies its cell
            {
                cell->removeCreature();
            }
            creature_iterator = m_creatures.erase(creature_iterator); // erase and get the next valid iterator
            delete creature;
        }
        else
        {
            creature_iterator++;
        }
    }
}

std::vector<Cell*> GameOfLifeCore::World::getFreeCellsShuffled() noexcept
{
    std::vector<Cell*> freeCells;
    for (auto &cell : m_map)
    {
        if (cell.isEmpty())
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

void GameOfLifeCore::World::checkMapCoordinatesAndAdd(uint32_t row, uint32_t col, std::vector<Cell*> &list) noexcept
{
    if( (row >= 0) && (col >= 0) & (row < m_rows) && (col < m_cols) )
    {
        list.push_back(&(*this)(row, col));
    }
}

std::vector<Cell*> GameOfLifeCore::World::getNeighboringCellsShuffled(const Cell &position) noexcept
{
    uint32_t row = position.getRow();
    uint32_t col = position.getCol();
    std::vector<Cell*> neighboringCells;

    checkMapCoordinatesAndAdd(row-1, col-1, neighboringCells);
    checkMapCoordinatesAndAdd(row-1, col, neighboringCells);
    checkMapCoordinatesAndAdd(row-1, col+1, neighboringCells);
    checkMapCoordinatesAndAdd(row, col+1, neighboringCells);
    checkMapCoordinatesAndAdd(row+1, col+1, neighboringCells);
    checkMapCoordinatesAndAdd(row+1, col, neighboringCells);
    checkMapCoordinatesAndAdd(row+1, col-1, neighboringCells);
    checkMapCoordinatesAndAdd(row, col-1, neighboringCells);

    // Create a random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector
    std::shuffle(neighboringCells.begin(), neighboringCells.end(), g);

    return neighboringCells;
}

void GameOfLifeCore::World::addCreatures(CreatureType type, uint32_t count, bool randomAge) noexcept
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
        CreatureFactory::Create(type, *this, *cell, randomAge);
        freeCells.pop_back();
    }
}

void GameOfLifeCore::World::registerCreature(Creature& creature)
{
    m_creatures.insert(&creature);
}

std::vector<Cell>::iterator GameOfLifeCore::World::begin() noexcept
{
    return m_map.begin();
}

std::vector<Cell>::iterator GameOfLifeCore::World::end() noexcept
{
    return m_map.end();
}

std::vector<Cell>::const_iterator GameOfLifeCore::World::cbegin() noexcept
{
    return m_map.cbegin();
}

std::vector<Cell>::const_iterator GameOfLifeCore::World::cend() noexcept
{
    return m_map.cend();
}

[[nodiscard]] constexpr std::size_t GameOfLifeCore::World::IX(const uint32_t row, const uint32_t col) const noexcept
{
    return static_cast<std::size_t>(col) + static_cast<std::size_t>(m_cols) * static_cast<std::size_t>(row);
}
