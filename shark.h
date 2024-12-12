#pragma once

#include "creature.h"

class Shark : public Creature
{
    public:
        Shark(World *world, int reproductionAge, int maxAge);
        void tick() override;
};