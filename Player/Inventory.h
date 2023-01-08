#pragma once

#include <vector>
#include <unordered_map>
#include "ChunkBlockData.h"

class Inventory {
    private:
        const static inline std::unordered_map<std::string, const ChunkBlockData*> NameDataMapper = {
                {"Air", &block_type::AirBlock},
                {"Grass", &block_type::GrassBlock}
        };
        const int MAX_INVENTORY_SIZE = 10;
        std::unordered_map<std::string, int> blocks;

    public:
        Inventory() = default;
        const std::unordered_map<std::string, int>& getBlocks() const;
        bool addBlock(const ChunkBlockData& block);
        const ChunkBlockData& removeBlock(const std::string& name);
};
