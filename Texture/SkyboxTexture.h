#pragma once

#include "BasicTexture.h"
#include <string>

class SkyboxTexture : public BasicTexture {
    protected:
        unsigned int i = 0;
        void setTextureParameters() override;

    public:
        SkyboxTexture();
        SkyboxTexture(const std::string& filePath, unsigned int i, GLenum format = GL_RGB);
        void bindTexture() const override;
        void changeTexture(const std::string &filePath) override;
        void loadAndApplyTextureImage(const std::string &filePath) override;
        ~SkyboxTexture();
        void i_increment();
        void i_decrement();

        //getters
        unsigned int i_get();

        //operators
        SkyboxTexture operator=(const SkyboxTexture& texture);
};
