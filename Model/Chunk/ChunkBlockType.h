#pragma once

#include <cstdint>
#include <iostream>
using Block_t = uint8_t;

enum class ChunkBlockType :  Block_t
{
    Air = 0,
    Grass,
    Dirt,
    Cobblestone,
    Sand,
    Wood,
    Water
};