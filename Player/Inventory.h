#pragma once

#include <vector>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>

#include "ChunkBlockData.h"

class Inventory {
    private:
        const static inline std::unordered_map<ChunkBlockType, const ChunkBlockData*> NameDataMapper = {
                {block_type::AirBlock.blockType, &block_type::AirBlock},
                {block_type::GrassBlock.blockType, &block_type::GrassBlock},
                {block_type::SandBlock.blockType, &block_type::SandBlock},
                {block_type::DirtBlock.blockType, &block_type::DirtBlock},
                {block_type::CobblestoneBlock.blockType, &block_type::CobblestoneBlock},
                {block_type::WoodBlock.blockType, &block_type::WoodBlock},
        };
        const int MAX_INVENTORY_SIZE = 10;
        std::unordered_map<ChunkBlockType, int> blocks;
        std::unordered_map<ChunkBlockType, int>::iterator selectedSlot = blocks.end();
        std::map<unsigned int, ChunkBlockType> inventorySlots;
        void logInventory();

    public:
        Inventory();
        const std::unordered_map<ChunkBlockType, int>& getBlocks() const;
        bool addBlock(const ChunkBlockData& block);
        const ChunkBlockData& removeBlock(const ChunkBlockType& type);

        //getters
        std::unordered_map<ChunkBlockType, int>::iterator getSelectedSlot() const;
        const ChunkBlockData* getCurrentBlock();

        //setters
        void setSelectedSlot(unsigned int slot);
};
