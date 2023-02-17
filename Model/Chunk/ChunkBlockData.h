#pragma once

#include "ChunkBlockType.h"
#include "glm.hpp"
#include "string"

struct ChunkBlockData {

    ChunkBlockData(ChunkBlockType type, const std::string& name, bool breakable = true)
        : name(name), blockType(type), breakable(breakable){}
    ChunkBlockData(
            ChunkBlockType type,
            const std::string& name,
            const glm::vec2& topFaceTextureMin,
            const glm::vec2& topFaceTextureMax,
            const glm::vec2& bottomFaceTextureMin,
            const glm::vec2& bottomFaceTextureMax,
            const glm::vec2& leftFaceTextureMin,
            const glm::vec2& leftFaceTextureMax,
            const glm::vec2& rightFaceTextureMin,
            const glm::vec2& rightFaceTextureMax,
            const glm::vec2& frontFaceTextureMin,
            const glm::vec2& frontFaceTextureMax,
            const glm::vec2& backFaceTextureMin,
            const glm::vec2& backFaceTextureMax,
            bool breakable = true
    ) : blockType(type), name(name), topFaceTextureMax(topFaceTextureMax), topFaceTextureMin(topFaceTextureMin),
    bottomFaceTextureMax(bottomFaceTextureMax), bottomFaceTextureMin(bottomFaceTextureMin),
    leftFaceTextureMax(leftFaceTextureMax), leftFaceTextureMin(leftFaceTextureMin),
    rightFaceTextureMax(rightFaceTextureMax), rightFaceTextureMin(rightFaceTextureMin),
    frontFaceTextureMax(frontFaceTextureMax), frontFaceTextureMin(frontFaceTextureMin),
    backFaceTextureMax(backFaceTextureMax), backFaceTextureMin(backFaceTextureMin), breakable(breakable){}


    ChunkBlockType blockType{ChunkBlockType::Air};
    std::string name;
    glm::vec2 topFaceTextureMin{-1,-1};
    glm::vec2 topFaceTextureMax{-1,-1};
    glm::vec2 bottomFaceTextureMin{-1,-1};
    glm::vec2 bottomFaceTextureMax{-1,-1};
    glm::vec2 leftFaceTextureMin{-1,-1};
    glm::vec2 leftFaceTextureMax{-1,-1};
    glm::vec2 rightFaceTextureMin{-1,-1};
    glm::vec2 rightFaceTextureMax{-1,-1};
    glm::vec2 frontFaceTextureMin{-1,-1};
    glm::vec2 frontFaceTextureMax{-1,-1};
    glm::vec2 backFaceTextureMin{-1,-1};
    glm::vec2 backFaceTextureMax{-1,-1};
    bool breakable = true;
};

namespace block_type {
    const ChunkBlockData AirBlock= ChunkBlockData(ChunkBlockType::Air, "Air", false);

    const ChunkBlockData GrassBlock = ChunkBlockData(
        ChunkBlockType::Grass, "Grass", {0,240}, {16, 256},
        {32,240}, {48,256},
        {16,240},{32,256},{16,240},
        {32,256},{16,240},
        {32,256},{16,240},{32,256}
    );
    const ChunkBlockData SandBlock = ChunkBlockData(
            ChunkBlockType::Sand, "Sand",
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256},
            {112,240}, {128,256}
    );
    const ChunkBlockData DirtBlock = ChunkBlockData(
            ChunkBlockType::Dirt, "Dirt",
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256},
            {32,240}, {48,256}
    );
    const ChunkBlockData CobblestoneBlock = ChunkBlockData(
            ChunkBlockType::Cobblestone, "Cobblestone",
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256},
            {48,240}, {64,256}
    );
    const ChunkBlockData WoodBlock = ChunkBlockData(
            ChunkBlockType::Wood, "Wood",
            {80,240}, {96,256},
            {80,240}, {96,256},
            {64,240}, {80,256},
            {64,240}, {80,256},
            {64,240}, {80,256},
            {64,240}, {80,256}
    );
    const ChunkBlockData CactusBlock = ChunkBlockData(
            ChunkBlockType::Cactus, "Cactus",
            {144,224}, {160,240},
            {144,224}, {160,240},
            {144,240}, {160,256},
            {144,240}, {160,256},
            {144,240}, {160,256},
            {144,240}, {160,256}
    );
    const ChunkBlockData BushBlock = ChunkBlockData(
            ChunkBlockType::Bush, "Bush",
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256},
            {96,240}, {112,256}
    );
    const ChunkBlockData WaterBlock = ChunkBlockData(
            ChunkBlockType::Water, "Water",
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            {128,240}, {144,256},
            false
    );
    const ChunkBlockData& getBlockDataByType(const ChunkBlockType& blockType);
};