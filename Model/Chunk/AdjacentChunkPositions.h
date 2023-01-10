#pragma once

#include "glm.hpp"

struct AdjacentChunkPositions{
    void update(int x, int y, int z)
    {
        top      =   {x,     y + 16,  z};
        bottom    =   {x,     y - 16,  z};
        left    =   {x - 16, y,      z};
        right   =   {x + 16, y,      z};
        front   =   {x,     y,      z + 16};
        back    =   {x,     y,      z - 16};
    }
    glm::vec3 top;
    glm::vec3 bottom;
    glm::vec3 left;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 back;
};