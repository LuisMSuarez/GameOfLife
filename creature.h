#pragma once

#include "world.h"
#include "cell.h"
#include <string>
#include <array>

class World; // Forward declaration
class Cell;

class Creature
{
    public:
        Creature(World &world, Cell &cell, uint32_t reproductionTicks, uint32_t maxAge, std::string resourcePath, uint32_t startingAge = 0);
        ~Creature();
        virtual void tick();
        bool reachedMaxAge();
        Cell& getCell();
        void tagForDeletion();
        bool isTaggedForDeletion();
        std::string getResourcePath();
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
        std::string m_resourcePath;
};
