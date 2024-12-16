#pragma once

#include "creature.h"

class Shark : public Creature
{
    public:
        Shark(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge);
        ~Shark();
        void tick() override;
        static uint32_t s_reproductionTicks;
        static uint32_t s_maxAge;
};
