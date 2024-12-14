#pragma once

#include "world.h"
#include "cell.h"

class World; // Forward declaration
class Cell;

class Creature
{
    public:
        Creature(World *world, Cell *cell, uint32_t reproductionAge, uint32_t maxAge);
        ~Creature();
        virtual void tick();
        bool reachedMaxAge();
    protected:
        bool reachedTimeToReproduce();
        void resetTimeToReproduce();
    private:
        uint32_t m_reproduction_age;
        uint32_t m_age;
        uint32_t m_max_age;
        uint32_t m_timeToReproduce;
        World *m_world;
        Cell *m_cell;

        std::vector<Cell*> getNeighboringCellsShuffled();
};

