#include "creaturefactory.h"
#include "fish.h"
#include "shark.h"
#include "creatureType.h"
#include <cstdlib> // rand()


CreatureFactory::CreatureFactory()
{

}

Creature& CreatureFactory::Create(CreatureType type, World &world, Cell &cell, bool randomAge)
{
    Creature *newCreature = nullptr;
    int startingAge = 0;
    switch(type)
    {
        case CreatureType::fish:            
            newCreature = new Fish(world, cell, Fish::s_reproductionTicks, Fish::s_maxAge, randomAge ? rand() % Fish::s_maxAge : 0);
        break;
        case CreatureType::shark:
             newCreature = new Shark(world, cell, Shark::s_reproductionTicks, Shark::s_maxAge, randomAge ? rand() % Shark::s_maxAge : 0);
        break;
    }

    cell.addCreature(newCreature);

    return *newCreature;
}
