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
        //TODO: remove hardcoding
        //I will hardcode this for now

        float TEXTURE_PACK_SIZE = 256.f;
        float SINGLE_TEXTURE_SIZE = 16.f;

        unsigned int VAO = 0;
        unsigned int EBO = 0;
        unsigned int VBO = 0;

        std::vector<ChunkBlock> blocks;
        glm::vec3 dimensions{16,16,16};
        glm::vec3 position;

        void genEbo();
        void genVbo();
        void genVao();

        //maybe I will remove this later
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        std::vector<ChunkBlock>::iterator blockInner(const glm::vec3& searchPosition);

    public:
        //constructors and destructors
        Chunk(const glm::vec3& dimensions={16,16,16}, const glm::vec3& position={0,0,0});
        //TODO: IMPLEMENT DESTRUCTOR

        //getters
        const std::vector<ChunkBlock>& getBlocks();
        ChunkBlock block(const glm::vec3& searchPosition, bool logInfo=false) const;
        const glm::vec3& getDimensions() const;
        const glm::vec3& getPosition() const;
        const std::vector<GLuint>& getIndices() const;
        const std::vector<GLfloat>& getVertices() const;

        //setters
        void addFace(
                const std::vector<GLfloat>& face,
                const glm::vec3& blockPosition,
                const std::vector<GLfloat>& textureCoords
        );
        void editBlock(
                const glm::vec3& position,
                const ChunkBlockData& blockData,
                std::vector<glm::vec3>& surroundingBlockPositions
        );
        void checkEdgeBlock(
                std::vector<ChunkBlock>::iterator block,
                std::vector<glm::vec3>& surroundingBlockPositions
        );

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