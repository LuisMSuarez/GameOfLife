#pragma once

#include "creature.h"

class Shark : public Creature
{
    public:
        Shark(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge = 0);
        ~Shark();
        void tick() override;
        static uint32_t s_reproductionTicks;
        static uint32_t s_maxAge;
        static std::string getResource();
};
