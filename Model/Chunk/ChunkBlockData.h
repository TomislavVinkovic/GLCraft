#pragma once

#include "ChunkBlockType.h"
#include "glm.hpp"
#include "string"

struct ChunkBlockData {

    ChunkBlockData(ChunkBlockType type, const std::string& name) : name(name), blockType(type){}
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
            const glm::vec2& backFaceTextureMax
    ) : blockType(type), name(name), topFaceTextureMax(topFaceTextureMax), topFaceTextureMin(topFaceTextureMin),
    bottomFaceTextureMax(bottomFaceTextureMax), bottomFaceTextureMin(bottomFaceTextureMin),
    leftFaceTextureMax(leftFaceTextureMax), leftFaceTextureMin(leftFaceTextureMin),
    rightFaceTextureMax(rightFaceTextureMax), rightFaceTextureMin(rightFaceTextureMin),
    frontFaceTextureMax(frontFaceTextureMax), frontFaceTextureMin(frontFaceTextureMin),
    backFaceTextureMax(backFaceTextureMax), backFaceTextureMin(backFaceTextureMin){}


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
};

namespace block_type {
    const ChunkBlockData AirBlock= ChunkBlockData(ChunkBlockType::Air, "Air");

    const ChunkBlockData GrassBlock = ChunkBlockData(
        ChunkBlockType::Grass, "Grass", {0,240}, {16, 256},
        {32,240}, {48,256},
        {16,240},{32,256},{16,240},
        {32,256},{16,240},
        {32,256},{16,240},{32,256}
    );
    //have to add other blocks too

};