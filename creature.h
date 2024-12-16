#pragma once

#include "world.h"
#include "cell.h"

class World; // Forward declaration
class Cell;

class Creature
{
    public:
        Creature(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, uint32_t age = 0);
        ~Creature();
        virtual void tick();
        bool reachedMaxAge();
        Cell& getCell();
        void tagForDeletion();
        bool isTaggedForDeletion();
    protected:
        bool reachedTimeToReproduce();
        void resetTimeToReproduce();
        void moveTo(Cell &cell);
        uint32_t m_age;
        uint32_t m_reproductionTimer;
        uint32_t m_reproductionTicks;
        World &m_world;
        Cell *m_cell;
    private:
        uint32_t m_max_age;
        bool m_taggedForDeletion;
};

