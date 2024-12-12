#include "shark.h"

Shark::Shark(World *world, uint32_t reproductionAge, uint32_t maxAge)
    : Creature(world, reproductionAge, maxAge)
{

}

void Shark::tick()
{
    Creature::tick();
}
