#include "world.h"

World::World()
{

}

World::~World()
{
}

[[nodiscard]] constexpr std::size_t World::IX(const uint32_t row, const uint32_t col) const noexcept
{
    return static_cast<std::size_t>(col) + static_cast<std::size_t>(m_cols) * static_cast<std::size_t>(row) -1;
}
