#include "ChunkBlock.h"

ChunkBlock::ChunkBlock(glm::vec3 position, const ChunkBlockData* blockData)
    : position(position), blockData(blockData) {}


const glm::vec3 &ChunkBlock::getPosition() const{
    return position;
}

const ChunkBlockData* ChunkBlock::getData() const {
    return blockData;
}

ChunkBlock ChunkBlock::operator=(const ChunkBlock &block) {
    blockData = block.blockData;
    position = block.position;

    return *this;
}
