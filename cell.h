#pragma once
#include "creature.h"

class Creature; //Forward declaration

class Cell
{
    public:
        Cell();
        ~Cell();
        Creature *getCreature();
        void destroyCreature();
    private:
        Creature *m_creature;
};
