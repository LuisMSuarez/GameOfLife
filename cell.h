#pragma once
#include "creature.h"

class Creature; //Forward declaration

class Cell
{
    public:
        Cell();
        ~Cell();
        void addCreature(Creature *creature);
        Creature* getCreature();
        void removeCreature();
        void destroyCreature();
        void setCoordinates(uint32_t row, uint32_t col);
        uint32_t getRow() const;
        uint32_t getCol() const;
    private:
        Creature *m_creature;
        uint32_t m_row;
        uint32_t m_col;
};
