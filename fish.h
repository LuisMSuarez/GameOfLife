#pragma once

#include "creature.h"

class Fish : public Creature
{
    public:
        Fish(World *world, int reproductionTime);
};
