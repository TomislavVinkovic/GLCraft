#pragma once

#include "glm.hpp"

struct AdjacentChunkPositions{
    void update(int x, int y, int z)
    {
        top      =   {x,     y + 8,  z};
        bottom    =   {x,     y - 8,  z};
        left    =   {x - 8, y,      z};
        right   =   {x + 8, y,      z};
        front   =   {x,     y,      z + 8};
        back    =   {x,     y,      z - 8};
    }
    glm::vec3 top;
    glm::vec3 bottom;
    glm::vec3 left;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 back;
};