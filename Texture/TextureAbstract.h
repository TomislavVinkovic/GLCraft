#pragma once

#include <string>
#include <iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include <stb_image.h>

class TextureAbstract{
    protected:
        virtual void setTextureParameters() = 0;
        virtual void loadAndApplyTextureImage(const std::string& filePath) = 0;
        std::string textureFilepath;
        GLenum format = GL_RGB;
        unsigned int ID = 0;

    public:

        virtual void changeTexture(const std::string& filePath) = 0;
        virtual void bindTexture() const = 0;

        //getters
        unsigned int getId() const {
            return ID;
        }
};