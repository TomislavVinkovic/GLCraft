#pragma once

#include <string>
#include <iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include "TextureAbstract.h"

class TextureAtlas : public TextureAbstract {
    private:
        void setTextureParameters() override;
        void loadAndApplyTextureImage(const std::string &filePath) override;

        int TEXTURE_PACK_SIZE = 256;
        int SINGLE_TEXTURE_SIZE = 16;


    public:
        TextureAtlas(const std::string& filePath, GLenum format = GL_RGB, int SINGLE_TEXTURE_SIZE=16);
        TextureAtlas() = default;
        ~TextureAtlas();

        void changeTexture(const std::string &filePath) override;
        void bindTexture() const override;

        //operators
        TextureAtlas operator=(const TextureAtlas& texture);
};
