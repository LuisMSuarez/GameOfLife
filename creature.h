#pragma once

#include "world.h"

class World; // Forward declaration

class Creature
{
    public:
        Creature(World *world, int reproductionTime);
    private:
        int m_reproductionTime;
        World *m_world;
};

