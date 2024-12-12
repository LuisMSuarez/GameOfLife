#include "shark.h"

Shark::Shark(World *world, int reproductionAge, int maxAge)
    : Creature(world, reproductionAge, maxAge)
{

}

void Shark::tick()
{
    Creature::tick();
}
