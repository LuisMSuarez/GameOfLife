#include "creaturefactory.h"
#include "fish.h"
#include "shark.h"
#include "creatureType.h"


CreatureFactory::CreatureFactory()
{

}

Creature& CreatureFactory::Create(CreatureType type, World &world, Cell &cell)
{
    Creature *newCreature = nullptr;

    switch(type)
    {
        case CreatureType::fish:
            newCreature = new Fish(world, cell, Fish::s_reproductionAge, Fish::s_maxAge);
        break;
        case CreatureType::shark:
            newCreature = new Shark(world, cell, Shark::s_reproductionAge, Shark::s_maxAge);
        break;
    }

    return *newCreature;
}
