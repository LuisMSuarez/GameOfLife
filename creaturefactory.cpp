#include "creaturefactory.h"
#include "fish.h"
#include "shark.h"
#include "creatureType.h"
#include <cstdlib> // rand()
#include <stdexcept> // std::runtime_error

using namespace GameOfLifeCore;

GameOfLifeCore::CreatureFactory::CreatureFactory()
{

}

Creature& GameOfLifeCore::CreatureFactory::Create(CreatureType type, World &world, Cell &cell, bool randomAge)
{
    Creature *newCreature = nullptr;
    switch(type)
    {
        case CreatureType::fish:
            newCreature = new Fish(world, cell, Fish::s_reproductionTicks, Fish::s_maxAge, Fish::getResource(), randomAge ? rand() % Fish::s_maxAge : 0);
        break;
        case CreatureType::shark:
             newCreature = new Shark(world, cell, Shark::s_reproductionTicks, Shark::s_maxAge, Shark::s_initialEnergy, Shark::getResource(), randomAge ? rand() % Shark::s_maxAge : 0);
        break;
        default:
            throw std::runtime_error("Invalid creature type for create operation.");
    }

    return *newCreature;
}
