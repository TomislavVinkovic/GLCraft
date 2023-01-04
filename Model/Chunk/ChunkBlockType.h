#pragma once

#include <cstdint>
using Block_t = uint8_t;

enum class ChunkBlockType :  Block_t
{
    Air = 0,
    Grass,
    Dirt,
    Stone,
    Sand
};
