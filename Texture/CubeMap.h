#pragma once

#include <string>
#include <iostream>
#include <array>

#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include "TextureAbstract.h"

class CubeMap {
    private:
        unsigned int ID = 0;
        void setTextureParameters();
        GLenum format = GL_RGB;

    public:
        //constructors and destructors
        CubeMap() = default;
        ///The faces should be placed in the array in the following order:
        ///right, left, top, bottom, front, back
        CubeMap(
            const std::array<std::string, 6>& faces,
            GLenum format = GL_RGB
        );
        ~CubeMap();
        //getters
        unsigned int getID() const;

        //utility functions
        void bindTexture();
        void deleteData();
};
