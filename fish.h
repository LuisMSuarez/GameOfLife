#pragma once

#include "creature.h"

class Fish : public Creature
{
    public:
        Fish(World *world, uint32_t reproductionAge, uint32_t maxAge);
        void tick() override;
        static uint32_t s_reproductionAge;
        static uint32_t s_maxAge;
};
