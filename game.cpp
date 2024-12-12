#include "game.h"
#include "fish.h"
#include "shark.h"

Game::Game()
{

}

void Game::newWorld(uint32_t rowCount, uint32_t colCount)
{
    m_world.initialize(rowCount, colCount);
}

void Game::addFish(uint32_t numFish)
{
    for (int i= 1; i<= numFish; i++)
    {
        Fish *f = new Fish(&m_world, Fish::s_reproductionAge, Fish::s_maxAge);
    }
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
