#include "TreeGenerator.h"

void TreeGenerator::makeOakTree(Chunk &chunk, Random<std::minstd_rand> &rand, int x, int y, int z) {
    chunk.placeBlock({x,y,z}, &block_type::WoodBlock);
    chunk.placeBlock({x,y+1,z}, &block_type::WoodBlock);
    chunk.placeBlock({x,y+2,z}, &block_type::WoodBlock);

    chunk.placeBlock({x,y+3,z}, &block_type::WoodBlock);


    chunk.placeBlock({x,y+4,z}, &block_type::WoodBlock);
    chunk.placeBlock({x,y+4,z-1}, &block_type::BushBlock);
    chunk.placeBlock({x-1,y+4,z}, &block_type::BushBlock);
    chunk.placeBlock({x+1,y+4,z}, &block_type::BushBlock);
    chunk.placeBlock({x,y+4,z+1}, &block_type::BushBlock);
    chunk.placeBlock({x-1,y+4,z-1}, &block_type::BushBlock);
    chunk.placeBlock({x+1,y+4,z-1}, &block_type::BushBlock);
    chunk.placeBlock({x-1,y+4,z+1}, &block_type::BushBlock);
    chunk.placeBlock({x+1,y+4,z+1}, &block_type::BushBlock);

    chunk.placeBlock({x,y+5,z}, &block_type::WoodBlock);
    chunk.placeBlock({x,y+5,z-1}, &block_type::BushBlock);
    chunk.placeBlock({x,y+5,z+1}, &block_type::BushBlock);
    chunk.placeBlock({x-1,y+5,z}, &block_type::BushBlock);
    chunk.placeBlock({x+1,y+5,z}, &block_type::BushBlock);
    chunk.placeBlock({x-1,y+5,z-1}, &block_type::BushBlock);
    chunk.placeBlock({x+1,y+5,z-1}, &block_type::BushBlock);
    chunk.placeBlock({x-1,y+5,z+1}, &block_type::BushBlock);
    chunk.placeBlock({x+1,y+5,z+1}, &block_type::BushBlock);

    chunk.placeBlock({x,y+6,z}, &block_type::BushBlock);
}

void TreeGenerator::makeCactus(Chunk &chunk, Random<std::minstd_rand> &rand, int x, int y, int z) {
    //let's try this first
    chunk.placeBlock({x,y,z}, &block_type::CactusBlock);
    chunk.placeBlock({x,y+1,z}, &block_type::CactusBlock);
    chunk.placeBlock({x,y+2,z}, &block_type::CactusBlock);
    chunk.placeBlock({x,y+3,z}, &block_type::CactusBlock);
}
