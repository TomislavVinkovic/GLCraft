#include "ChunkBlock.h"

ChunkBlock::ChunkBlock(glm::vec3 position) : position(position) {
    type = ChunkBlockType::Grass;
}

ChunkBlock::ChunkBlock(glm::vec3 position, const ChunkBlockType& blockType)
    : position(position), type(blockType){}

const glm::vec3 &ChunkBlock::getPosition() const{
    return position;
}

const ChunkBlockType &ChunkBlock::getType() const {
    return type;
}
