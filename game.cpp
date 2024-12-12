#include "game.h"
#include "fish.h"
#include "shark.h"
#include <algorithm>
#include <random>

Game::Game()
{

}

void Game::newWorld(uint32_t rowCount, uint32_t colCount)
{
    m_world.initialize(rowCount, colCount);
}

void Game::addFish(uint32_t numFish)
{
    auto freeCells = getFreeCellsShuffled();

    for (int i= 1; i<= numFish; i++)
    {
        Fish *f = new Fish(&m_world, Fish::s_reproductionAge, Fish::s_maxAge);
        auto cell = freeCells.back();
        cell->addCreature(f);
        freeCells.pop_back();
    }
}

std::vector<Cell*> Game::getFreeCellsShuffled()
{
    std::vector<Cell*> freeCells;
    for (auto cellIterator= m_world.begin(); cellIterator!=m_world.end(); cellIterator++)
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

World* Game::getWorld()
{
    return &m_world;
}

void Game::tick()
{
    for (auto cellIterator = m_world.begin(); cellIterator != m_world.end(); cellIterator++)
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
