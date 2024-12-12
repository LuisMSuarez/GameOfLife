#pragma once

#include "creature.h"

class Shark : public Creature
{
    public:
        Shark(World *world, uint32_t reproductionAge, uint32_t maxAge);
        void tick() override;
        static uint32_t reproductionAge;
        static uint32_t s_maxAge;
};
