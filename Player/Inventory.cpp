#include "Inventory.h"

const std::unordered_map<std::string, int> &Inventory::getBlocks() const {
    return blocks;
}

bool Inventory::addBlock(const ChunkBlockData &block) {
    auto it = blocks.find(block.name);
    if((it == blocks.end() && blocks.size() < MAX_INVENTORY_SIZE)) {
        //add a new block
        blocks.insert({block.name, 1});
        return true;
    }
    if(it != blocks.end()) {
        it->second += 1;
        return true;
    }

    return false;
}

const ChunkBlockData& Inventory::removeBlock(const std::string& name) {
    auto it = blocks.find(name);
    //block not found
    if(it == blocks.end()) return block_type::AirBlock;

    auto key = it->first;
    it->second--;
    if(it->second == 0) blocks.erase(key);

    return *(NameDataMapper.find(key)->second);
}
