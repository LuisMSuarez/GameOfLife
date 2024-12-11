#pragma once
#include "creature.h"

class Creature; //Forward declaration

class Cell
{
    public:
        Cell();
        ~Cell();

    private:
        Creature *m_creature;
};
