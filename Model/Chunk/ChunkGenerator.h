#pragma once

#include "glm.hpp"
#include "gtc/noise.hpp"
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include <iostream>
#include <algorithm>
#include <array>

#include "Chunk.h"
#include "ChunkBlock.h"
#include "Face.h"

#include "AdjacentBlockPositions.h"
#include "AdjacentChunkPositions.h"
#include "NoiseGenerator.h"

#include <unordered_map>
#include<string>

typedef std::unordered_map<std::string, Chunk*> ChunkMap;

class ChunkGenerator{
    public:
        ChunkGenerator() = default;
        explicit ChunkGenerator(const std::vector<glm::vec3>& chunkPositions, const glm::vec3& dimensions={16,16,16});
        std::vector<Chunk> generate();
        void regenerate(std::vector<Chunk>& chunks, std::vector<Chunk*> chunksToRegenerate);

        //getters
        int getNumberOfFaces();

    private:
        //remember that this is fixed for now
        static const int chunkDimensions = 16*16*16;
        static const int chunkSize = 16;
        static const int heightMapSize = chunkSize*chunkSize;

        NoiseGenerator noiseGenerator{27891};

        //height map generation
        std::array<int, heightMapSize> createChunkHeightMap(Chunk& chunk);
        void generateSmoothTerrain(Chunk& chunk, const std::array<int, heightMapSize>& heightMap);

        void generateChunk(
                Chunk& chunk,
                const ChunkMap& chunkMap
        );
        ChunkMap generateChunkMap(std::vector<Chunk>& chunks);
        glm::vec3 dimensions;
        std::vector<glm::vec3> chunkPositions;
        int no_faces = 0;

        AdjacentBlockPositions blockDirections;
        AdjacentChunkPositions chunkDirections;

        void fillTextureCoords(
            const ChunkBlock& block,
            std::vector<GLfloat>& texCoords,
            const std::vector<GLfloat>& face
        );

        bool shouldGenerateFace(
                Chunk& chunk,
                const glm::vec3& adjBlockPosition,
                const glm::vec3& adjChunkPosition,
                const ChunkMap& chunkMap
        );

        void addFace(
                Chunk& chunk,
                const ChunkBlock& block,
                const std::vector<GLfloat>& face,
                const glm::vec3& position,
                const glm::vec3& adjBlockPos,
                const glm::vec3& adjChunkPosition,
                const ChunkMap& chunkMap
        );
};