#pragma once
#include "creature.h"

class Creature; //Forward declaration

class Cell
{
    public:
        Cell();
        ~Cell();
        void addCreature(Creature *creature);
        Creature *getCreature();
        void destroyCreature();
    private:
        Creature *m_creature;
};
