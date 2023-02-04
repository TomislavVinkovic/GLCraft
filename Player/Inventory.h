#pragma once

#include <vector>
#include <iostream>
#include <cstdint>
#include <map>

#include "ChunkBlockData.h"

class Inventory {
    private:
        const int MAX_INVENTORY_SIZE = 10;
        std::map<unsigned int, std::pair<ChunkBlockType, unsigned int>> inventory;
        std::map<unsigned int, std::pair<ChunkBlockType, unsigned int>>::iterator selectedSlot;
        //void logInventory();

    public:
        Inventory();
        const std::map<unsigned int, std::pair<ChunkBlockType, unsigned int>>& getInventory() const;
        bool addBlock(const ChunkBlockData& block);
        const ChunkBlockData& removeBlock(const ChunkBlockType &block);

        //getters
        const ChunkBlockType& getCurrentBlock() const;
        unsigned int getSelectedSlot();

        //setters
        void setSelectedSlot(unsigned int slot);
};
