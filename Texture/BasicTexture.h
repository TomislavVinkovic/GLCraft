#pragma once
#include <string>
#include <iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include "TextureAbstract.h"

class BasicTexture : public TextureAbstract {
    protected:
        virtual void setTextureParameters() override;
        virtual void loadAndApplyTextureImage(const std::string &filePath) override;


    public:
        BasicTexture() = default;
        BasicTexture(const std::string& filePath, GLenum format = GL_RGB);
        ~BasicTexture();

        virtual void changeTexture(const std::string &filePath) override;
        virtual void bindTexture() const override;

        //operators
        BasicTexture operator=(const BasicTexture& texture);
};
