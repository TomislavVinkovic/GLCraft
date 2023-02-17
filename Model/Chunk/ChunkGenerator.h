#pragma once

#include "glm.hpp"
#include "gtc/noise.hpp"
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include <iostream>
#include <algorithm>
#include <array>
#include <thread>
#include <ctime>

#include "Chunk.h"
#include "ChunkBlock.h"
#include "Face.h"
#include "Random.h"

#include "AdjacentBlockPositions.h"
#include "AdjacentChunkPositions.h"
#include "NoiseGenerator.h"
#include "Generation/Terrain/TerrainGenerator.h"

#include <unordered_map>
#include<string>

typedef std::unordered_map<std::string, Chunk*> ChunkMap;

class ChunkGenerator{
    public:
        ChunkGenerator();
        explicit ChunkGenerator(const std::vector<glm::vec3>& chunkPositions, const glm::vec3& dimensions={16,16,16});
        void generate();
        Chunk* generateNextChunk();
        void regenerate(std::vector<Chunk*> chunksToRegenerate);

        void addChunks(const std::vector<glm::vec3>& newPositions);

        //getters
        int getNumberOfFaces();
        int getCurrentChunk();

        //setters
        void setDimensions(const glm::vec3& dimensions);
        void setPositions(const std::vector<glm::vec3>& chunkPositions);

private:
        Random<std::minstd_rand> randomEngine;
        GrasslandBiome grassBiome;
        DesertBiome desertBiome;
        OceanBiome oceanBiome;
        ForestBiome forestBiome;
        //remember that this is fixed for now
        static const int chunkDimensions = 16*16*16;
        static const int chunkSize = 16;
        static const int heightMapSize = chunkSize*chunkSize;
        static const int biomeMapSize = (chunkSize+1)*(chunkSize + 1);
        std::unordered_map<std::string, Chunk*> chunkMap;
        std::vector<Chunk> chunks;

        int currentChunk = 0;

        //27891 //najdrazi
        //31245
        static NoiseGenerator noiseGenerator;
        static NoiseGenerator biomeGenerator;

        //isprobavanje novog terrain generatora
        TerrainGenerator terrainGenerator;

        //height map generation
        std::array<int, heightMapSize> createChunkHeightMap(Chunk& chunk);
        std::array<int, biomeMapSize> createChunkBiomeMap(Chunk& chunk);
        void generateSmoothTerrain(
            Chunk& chunk,
            const std::array<int, heightMapSize>& heightMap,
            const std::array<int, biomeMapSize>& biomeMap
        );

        const Biome& getBiome(
                int x,
                int z,
                const std::array<int, biomeMapSize>& biomeMap
        ) const;

        void generateChunk(
            Chunk& chunk
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
                const ChunkBlock& blockToPlace,
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