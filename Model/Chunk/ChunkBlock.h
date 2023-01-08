#pragma once

#include "ChunkBlockType.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include "ChunkBlockData.h"

//TODO: Implement a texture atlas and add it here

class ChunkBlock {
    ChunkBlockData blockData;
    glm::vec3 position;
public:
    ChunkBlock(glm::vec3 position, const ChunkBlockData& blockData = block_type::AirBlock);
    ChunkBlock operator=(const ChunkBlock& block);

    //getters
    const glm::vec3& getPosition() const;
    const ChunkBlockData& getData() const;
};
