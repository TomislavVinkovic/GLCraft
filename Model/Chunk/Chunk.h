#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include "ChunkBlock.h"
#include "ChunkBlockType.h"
#include "AdjacentChunkPositions.h"
#include "Face.h"

class Chunk {
    private:
        //TODO: remove hardcoding
        //I will hardcode this for now

        float TEXTURE_PACK_SIZE = 256.f;
        float SINGLE_TEXTURE_SIZE = 16.f;

        unsigned int VAO = 0;
        unsigned int EBO = 0;
        unsigned int VBO = 0;

        //these are added for water transparency effects
        unsigned int VAO_WATER = 0;
        unsigned int VBO_WATER = 0;
        unsigned int EBO_WATER = 0;


        //is this chunk comprised of air blocks only?
        bool airChunk = true;

        std::vector<ChunkBlock> blocks;
        glm::vec3 dimensions{16,16,16};
        glm::vec3 position;

        void genEbo();
        void genVbo();
        void genVao();

        void genEboWater();
        void genVboWater();
        void genVaoWater();

        //maybe I will remove this later
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;

        std::vector<GLfloat> verticesWater;
        std::vector<GLuint> indicesWater;

        std::vector<ChunkBlock>::iterator blockInner(const glm::vec3& searchPosition);
        bool hasWater = true;

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
        const std::vector<GLuint>& getWaterIndices() const;
        const std::vector<GLfloat>& getWaterVertices() const;
        void clearData();
        bool getAirStatus();
        bool getHasWater();

        //setters
        void addFace(
                const ChunkBlock& block,
                const std::vector<GLfloat>& face,
                const glm::vec3& blockPosition,
                const std::vector<GLfloat>& textureCoords
        );
        void placeBlock(
            const glm::vec3& pos,
            const ChunkBlockData* blockData
        );
        void editBlock(
                const glm::vec3& position,
                const ChunkBlockData* blockData,
                std::vector<glm::vec3>& surroundingBlockPositions
        );
        void checkEdgeBlock(
                const glm::vec3& searchPosition,
                std::vector<glm::vec3>& surroundingBlockPositions
        );
        void setAirStatus(bool status);
        void sortByOpacity();

        //Graphics data commands
        GLuint currentVIndex = 0;
        GLuint currentVIndexWater = 0;
        void bindVAO() const;
        void bindVBO() const;
        void bindEBO() const;
        void bindVAOWater() const;
        void bindVBOWater() const;
        void bindEBOWater() const;


        unsigned int getVAO() const;
        unsigned int getEBO() const;
        unsigned int getVAOWater() const;
        unsigned int getVBOWater() const;
        unsigned int getEBOWater() const;

        void setHasWater(bool water);

        //operators
        Chunk operator=(Chunk chunk);

        void generateGraphicsData();
        void deleteGraphicsData();
        void updateGraphicsData();
};