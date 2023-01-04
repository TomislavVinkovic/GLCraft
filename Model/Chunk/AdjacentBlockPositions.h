#pragma once

#include "glm.hpp"

struct AdjacentBlockPositions
{
    void update(int x, int y, int z)
    {
        top      =   {x,     y + 1,  z};
        bottom    =   {x,     y - 1,  z};
        left    =   {x - 1, y,      z};
        right   =   {x + 1, y,      z};
        front   =   {x,     y,      z + 1};
        back    =   {x,     y,      z - 1};
    }

    glm::vec3 top;
    glm::vec3 bottom;
    glm::vec3 left;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 back;
};