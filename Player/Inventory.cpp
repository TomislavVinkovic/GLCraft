#include "Inventory.h"

const std::unordered_map<ChunkBlockType, int> &Inventory::getBlocks() const {
    return blocks;
}

bool Inventory::addBlock(const ChunkBlockData &block) {
    auto it = blocks.find(block.blockType);
    if((it == blocks.end() && blocks.size() < MAX_INVENTORY_SIZE)) {
        //add a new block
        blocks.insert({block.blockType, 1});
        selectedSlot = blocks.find(block.blockType);

        for(auto& iterator : inventorySlots) {
            if(iterator.second == ChunkBlockType::Air) {
                iterator.second = block.blockType;
                break;
            }
        }
        logInventory();
        return true;
    }
    else if(it != blocks.end()) {
        it->second += 1;
        logInventory();
        return true;
    }
    logInventory();
    return false;
}

const ChunkBlockData& Inventory::removeBlock(const ChunkBlockType& type) {
    auto it = blocks.find(type);
    //block not found
    if(it == blocks.end()) return block_type::AirBlock;

    auto key = it->first;
    it->second--;
    if(it->second == 0) {
        for(auto& iterator : inventorySlots) {
            if(iterator.second == type) {
                iterator.second = ChunkBlockType::Air;
                break;
            }
        }
        blocks.erase(key);
    }

    return *(NameDataMapper.find(key)->second);
}

std::unordered_map<ChunkBlockType, int>::iterator Inventory::getSelectedSlot() const {
    return selectedSlot;
}

const ChunkBlockData *Inventory::getCurrentBlock() {
    if(selectedSlot != blocks.end() && selectedSlot->second > 0) {
        return NameDataMapper.find(selectedSlot->first)->second;
    }
    return nullptr;
}

void Inventory::logInventory() {
    for(const auto& b : inventorySlots) {
        std::cout << b.first << " " << static_cast<int>(b.second) << std::endl;
    }
}

Inventory::Inventory() {
    for(int i = 0; i < 10; i++) {
        inventorySlots.insert({i, ChunkBlockType::Air}); //index, airblock
    }
}

void Inventory::setSelectedSlot(unsigned int slot) {
    if(slot > 9) return;
    auto x = inventorySlots.find(slot);
    if(x != inventorySlots.end()) {
        selectedSlot = blocks.find(x->second);
    }
}
