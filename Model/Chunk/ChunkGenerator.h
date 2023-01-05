#pragma once

#include "glm.hpp"
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include <iostream>

#include "Chunk.h"
#include "ChunkBlock.h"
#include "Face.h"
#include "AdjacentBlockPositions.h"



class ChunkGenerator{
    public:
        explicit ChunkGenerator(const glm::vec3& dimensions={16,16,16}, const glm::vec3& position = {0,0,0});
        Chunk generate();
        void newChunk(const glm::vec3& dimensions={16,16,16}, const glm::vec3& position = {0,0,0});

        //getters
        int getNumberOfFaces();

    private:
        int no_faces = 0;
        Chunk chunk;
        AdjacentBlockPositions directions;
        bool shouldGenerateFace(
                const std::vector<GLfloat>& face,
                const glm::vec3 adjBlockPosition
        );
        void addFace(const std::vector<GLfloat>& face, const glm::vec3& position, const glm::vec3& adjBlockPos);
};