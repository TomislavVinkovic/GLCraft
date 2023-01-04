#include "BasicTexture.h"

BasicTexture::BasicTexture(const std::string &filePath, GLenum format) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    setTextureParameters();

    loadAndApplyTextureImage(filePath, format);
}

BasicTexture::~BasicTexture() {
    glDeleteTextures(1, &ID);
}

void BasicTexture::changeTexture(const std::string &filePath, GLenum format) {
    glBindTexture(GL_TEXTURE_2D, ID);
    loadAndApplyTextureImage(filePath, format);
}

void BasicTexture::bindTexture() const {
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void BasicTexture::loadAndApplyTextureImage(const std::string &filePath, GLenum format) {
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    unsigned char *data = stbi_load(
            filePath.c_str(),
            &width,
            &height,
            &nrChannels,
            0
    );
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    textureFilepath = filePath;
    this->format = format;
    std::cout << "Texture loaded successfully" << std::endl;
}

BasicTexture BasicTexture::operator=(const BasicTexture &texture) {
    if(ID != 0) glDeleteTextures(1, &ID);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    setTextureParameters();

    loadAndApplyTextureImage(texture.textureFilepath, texture.format);

    return *this;
}

void BasicTexture::setTextureParameters() {
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
