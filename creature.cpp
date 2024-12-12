#include "creature.h"


Creature::Creature(World *world, int reproductionAge, int maxAge) :
    m_world(world), m_reproduction_age(reproductionAge), m_max_age(maxAge)
{

}

void Creature::tick()
{
    m_age++;
}

bool Creature::reachedMaxAge()
{
    return m_age >= m_max_age;
}

bool Creature::reachedTimeToReproduce()
{
    return m_timeToReproduce <= 0;
}
void Creature::resetTimeToReproduce()
{
    m_timeToReproduce = m_reproduction_age;
}
