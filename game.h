#pragma once

#include "world.h"

class Game
{
public:
    Game();
    void tick();
private:
    World m_world;
};
