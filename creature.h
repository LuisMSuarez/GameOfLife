#pragma once

#include "world.h"
#include "cell.h"

class World; // Forward declaration
class Cell;

class Creature
{
    public:
        Creature(World *world, int reproductionAge, int maxAge);
        virtual void tick();
        bool reachedMaxAge();
    protected:
        bool reachedTimeToReproduce();
        void resetTimeToReproduce();
    private:
        int m_reproduction_age;
        int m_age;
        int m_max_age;
        int m_timeToReproduce;
        World *m_world;
        Cell *m_cell;
};

