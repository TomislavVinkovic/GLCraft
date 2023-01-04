#pragma once
#include <string>
#include <iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include <stb_image.h>

class BasicTexture {
    private:
        void setTextureParameters();
        std::string textureFilepath;
        GLenum format;
        unsigned int ID = 0;

    void loadAndApplyTextureImage(const std::string& filePath, GLenum format = GL_RGB);
    public:
        BasicTexture() = default;
        BasicTexture(const std::string& filePath, GLenum format = GL_RGB);
        ~BasicTexture();

        void changeTexture(const std::string& filePath, GLenum format = GL_RGB);
        void bindTexture() const;

        //operators
        BasicTexture operator=(const BasicTexture& texture);

        //getters
        unsigned int getId() const {
            return ID;
        }
};
