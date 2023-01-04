#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include "ChunkBlock.h"
#include "ChunkBlockType.h"

class Chunk {
    private:
        unsigned int VAO = 0;
        unsigned int EBO = 0;
        unsigned int VBO = 0;

        std::vector<ChunkBlock> blocks;
        glm::vec3 dimensions;
        glm::vec3 position;

        void genEbo();
        void genVbo();
        void genVao();

        //maybe I will remove this later
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

    public:
        //constructors and destructors
        Chunk() = default;
        Chunk(const glm::vec3& dimensions, const glm::vec3& position={0,0,0});
        //TODO: IMPLEMENT DESTRUCTOR

        //getters
        const std::vector<ChunkBlock>& getBlocks();
        ChunkBlock block(const glm::vec3& searchPosition) const;
        const glm::vec3& getDimensions() const;
        const glm::vec3& getPosition() const;
        const std::vector<GLuint>& getIndices() const;
        const std::vector<GLfloat>& getVertices() const;


        //setters
        void addFace(const std::vector<GLfloat>& face, const glm::vec3& blockPosition);

        //Graphics data commands
        GLuint currentVIndex = 0; //TODO: make private
        void bindVAO() const;
        void bindVBO() const;
        void bindEBO() const;
        unsigned int getVAO() const;
        unsigned int getEBO() const;

        //operators
        Chunk operator=(Chunk chunk);

        void generateGraphicsData();
        void deleteGraphicsData();
        void updateGraphicsData(); //TODO:
};