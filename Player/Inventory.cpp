#include "Inventory.h"

const std::map<unsigned int, std::pair<ChunkBlockType, unsigned int>>& Inventory::getInventory() const {
    return inventory;
}

bool Inventory::addBlock(const ChunkBlockData &block) {
    //there are 10 inventory slots, so it really does not matter
    //that it is superlinear in complexity
    if(block.blockType != ChunkBlockType::Air) {
        std::vector<int> empty{};
        for(auto& it : inventory) {
            if(it.second.first == block.blockType) {
                it.second.second += 1;
                std::cout << it.second.second << std::endl;
                return true;
            }
            else if(it.second.first == ChunkBlockType::Air) {
                empty.push_back(it.first);
            }
        }
        if(!empty.empty()) {
            inventory[empty.front()].first = block.blockType;
            inventory[empty.front()].second = 1;
            return true;
        }
        return false;
    }

    else return false;
}

const ChunkBlockData& Inventory::removeBlock(const ChunkBlockType &blockType) {
    for(auto& it : inventory) {
        if(it.second.first == blockType) {
            it.second.second -= 1;
            if(it.second.second == 0) {
                it.second.first = ChunkBlockType::Air;
            }
            return block_type::getBlockDataByType(blockType);
        }
    }
    return block_type::AirBlock;
}

Inventory::Inventory() {
    for(int i = 0; i < 10; i++) {
        inventory.insert({i, {ChunkBlockType::Air, 0}}); //index, airblock
    }
    selectedSlot = inventory.begin();
}


void Inventory::setSelectedSlot(unsigned int slot) {
    if(slot > 9) return;
    selectedSlot = inventory.find(slot);
}

const ChunkBlockType& Inventory::getCurrentBlock() const {
    return selectedSlot->second.first;
}

unsigned int Inventory::getSelectedSlot() {
    return selectedSlot->first;
}
