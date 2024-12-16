#pragma once

#include "creature.h"

class Fish : public Creature
{
    public:
        Fish(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge);
        ~Fish();
        void tick() override;
        static uint32_t s_reproductionTicks;
        static uint32_t s_maxAge;
};
