#pragma once

#include "Chunk.h"
#include "Random.h"
#include "ChunkBlockData.h"
#include "ChunkBlockType.h"

//this class will be a static class
class TreeGenerator {
    public:
        TreeGenerator() = delete;
        ~TreeGenerator() = delete;

        static void makeOakTree(Chunk &chunk, Random<std::minstd_rand> &rand, int x, int y,
                         int z);

        static void makeCactus(Chunk &chunk, Random<std::minstd_rand> &rand, int x, int y,
                        int z);
};