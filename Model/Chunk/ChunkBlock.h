#pragma once

#include "ChunkBlockType.h"
#include "glm.hpp"
#include <string>
#include <vector>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

//TODO: Implement a texture atlas and add it here

class ChunkBlock {
    ChunkBlockType type;
    glm::vec3 position;
public:
    ChunkBlock(glm::vec3 position);
    ChunkBlock(glm::vec3 position, const ChunkBlockType& blockType);

    //getters
    const glm::vec3& getPosition() const;
    const ChunkBlockType& getType() const;
};
