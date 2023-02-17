#include "ChunkBlockData.h"

namespace block_type {
    const ChunkBlockData& getBlockDataByType(const ChunkBlockType& blockType) {
        if(blockType == ChunkBlockType::Air) {
            return AirBlock;
        }
        if(blockType == ChunkBlockType::Sand) {
            return SandBlock;
        }
        if(blockType == ChunkBlockType::Cobblestone) {
            return CobblestoneBlock;
        }
        if(blockType == ChunkBlockType::Water) {
            return WaterBlock;
        }
        if(blockType == ChunkBlockType::Wood) {
            return WoodBlock;
        }
        if(blockType == ChunkBlockType::Dirt) {
            return DirtBlock;
        }
        if(blockType == ChunkBlockType::Grass) {
            return GrassBlock;
        }
        if(blockType == ChunkBlockType::Cactus) {
            return CactusBlock;
        }
        if(blockType == ChunkBlockType::Bush) {
            return BushBlock;
        }
        else return GrassBlock;
    }
}