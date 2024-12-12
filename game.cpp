#include "game.h"


Game::Game()
{

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
