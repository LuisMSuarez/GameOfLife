#pragma once

#include "world.h"

namespace GameOfLifeCore
{
class Utils
{
    public:
        static int countCreatures(World &world) noexcept;
};
}
