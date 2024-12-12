#include "fish.h"


Fish::Fish(World *world, int reproductionAge, int maxAge)
    : Creature(world, reproductionAge, maxAge)
{

}

void Fish::tick()
{
    Creature::tick();
}
