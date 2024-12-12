#pragma once

#include "world.h"
#include "creature.h"

class Game
{
public:
    Game();
    void tick();
    void newWorld(uint32_t rowCount, uint32_t colCount);
    void addFish(uint32_t numFish);
    void addSharks(uint32_t numSharks);
private:
    World m_world;
    void addCreature(Creature *creature);

};
