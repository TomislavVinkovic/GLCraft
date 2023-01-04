#pragma once

#include<vector>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

struct FaceIndices {
    inline const static std::vector<GLuint> frontFaceIndices = {
        //FRONT
        4, 5, 6,
        6, 7, 4,
    };
    inline const static std::vector<GLuint> backFaceIndices = {
        //BACK
        0, 1, 2,
        2, 3, 0,
    };
    inline const static std::vector<GLuint> rightFaceIndices = {
        //RIGHT
        8, 9, 10,
        10, 11, 8,
    };
    inline const static std::vector<GLuint> leftFaceIndices = {
        //LEFT
        12, 13, 14,
        14, 15, 12,
    };
    inline const static std::vector<GLuint> topFaceIndices = {
        //TOP
        16, 17, 18,
        18, 19, 16,
    };
    inline const static std::vector<GLuint> bottomFaceIndices = {
        //BOTTOM
        20, 21, 22,
        22, 23, 20
    };
};