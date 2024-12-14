#include "fish.h"


Fish::Fish(World *world, Cell *cell, uint32_t reproductionAge, uint32_t maxAge)
    : Creature(world, cell, reproductionAge, maxAge)
{

}

Fish::~Fish()
{

}

uint32_t Fish::s_reproductionAge = 10;
uint32_t Fish::s_maxAge = 35;

void Fish::tick()
{
    Creature::tick();
}
