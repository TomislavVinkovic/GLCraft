#pragma once
#include<vector>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

struct Face {
    //vertices
    inline const static std::vector<GLfloat> frontFace = {
            //Front
            0, 0, 1,
            1, 0, 1,
            1, 1, 1,
            0, 1, 1,
    };

    inline const static std::vector<GLfloat> backFace = {
            //Back
            1, 0, 0,
            0, 0, 0,
            0, 1, 0,
            1, 1, 0,
    };

    inline const static std::vector<GLfloat> leftFace = {
            //Left
            0, 0, 0,
            0, 0, 1,
            0, 1, 1,
            0, 1, 0,
    };

    inline const static std::vector<GLfloat> rightFace = {
            //Right
            1, 0, 1,
            1, 0, 0,
            1, 1, 0,
            1, 1, 1,
    };

    inline const static std::vector<GLfloat> topFace = {
            //Top
            0, 1, 1,
            1, 1, 1,
            1, 1, 0,
            0, 1, 0,
    };

    inline const static std::vector<GLfloat> bottomFace = {
            //Bottom
            0, 0, 0,
            1, 0, 0,
            1, 0, 1,
            0, 0, 1,
    };
};