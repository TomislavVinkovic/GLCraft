#pragma once
#include <string>
#include <iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include <stb_image.h>

class BasicTexture {
    unsigned int ID;
    void loadAndApplyTextureImage(const std::string& filePath, GLenum format = GL_RGB);
    public:
        BasicTexture() = default;
        BasicTexture(const std::string& filePath, GLenum format = GL_RGB);
        ~BasicTexture();

        void changeTexture(const std::string& filePath, GLenum format = GL_RGB);
        void bindTexture() const;
};
