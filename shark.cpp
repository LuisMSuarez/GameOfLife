#include "shark.h"

Shark::Shark(World *world, uint32_t reproductionAge, uint32_t maxAge)
    : Creature(world, reproductionAge, maxAge)
{
}

Shark::~Shark()
{
}

uint32_t Shark::s_reproductionAge = 15;
uint32_t Shark::s_maxAge = 50;

void Shark::tick()
{
    Creature::tick();
}
