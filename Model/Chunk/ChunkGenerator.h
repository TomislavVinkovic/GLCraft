#pragma once

#include "glm.hpp"
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

#include "Chunk.h"
#include "ChunkBlock.h"
#include "Face.h"

#include "AdjacentBlockPositions.h"
#include "AdjacentChunkPositions.h"

#include <unordered_map>
#include<string>

class ChunkGenerator{
    public:
        explicit ChunkGenerator(const std::vector<glm::vec3>& chunkPositions, const glm::vec3& dimensions={16,16,16});
        std::vector<Chunk> generate();

        //getters
        int getNumberOfFaces();

    private:
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
                const std::unordered_map<std::string, Chunk*>& chunkMap
        );

        void addFace(
                Chunk& chunk,
                const ChunkBlock& block,
                const std::vector<GLfloat>& face,
                const glm::vec3& position,
                const glm::vec3& adjBlockPos,
                const glm::vec3& adjChunkPosition,
                const std::unordered_map<std::string, Chunk*>& chunkMap
        );
};