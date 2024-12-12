#pragma once

#include "creature.h"

class Fish : public Creature
{
    public:
        Fish(World *world, int reproductionAge, int maxAge);
        void tick() override;
};
