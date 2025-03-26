#pragma once
#include "creature.h"

namespace GameOfLifeCore
{
class Creature; //Forward declaration

class Cell
{
    public:
        Cell() noexcept;
        ~Cell();
        void addCreature(Creature& creature);
        Creature* getCreature() const noexcept;
        bool isEmpty() const noexcept;
        void removeCreature() noexcept;
        void destroyCreature() noexcept;
        void setCoordinates(uint32_t row, uint32_t col) noexcept;
        uint32_t getRow() const noexcept;
        uint32_t getCol() const noexcept;
    private:
        Creature *m_creature;
        uint32_t m_row;
        uint32_t m_col;
};
}
