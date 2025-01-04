#pragma once

#include "creatureType.h"
#include "creature.h"
#include "world.h"
#include "cell.h"

class World;
class Creature;
class Cell;

class CreatureFactory
{
    public:
        CreatureFactory();
        static Creature& Create(CreatureType type, World &world, Cell &cell, bool randomAge = false);
};
