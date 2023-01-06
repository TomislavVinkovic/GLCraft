#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const std::string &filePath, GLenum format, int SINGLE_TEXTURE_SIZE) {
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    this->format = format;

    setTextureParameters();
    loadAndApplyTextureImage(filePath);
    this->SINGLE_TEXTURE_SIZE = SINGLE_TEXTURE_SIZE;
}

TextureAtlas::~TextureAtlas() {
    glDeleteTextures(1, &ID);
}

TextureAtlas TextureAtlas::operator=(const TextureAtlas &texture) {
    return TextureAtlas();
}

void TextureAtlas::setTextureParameters() {
    //TODO: REMOVE HARDCODING OF TEXTURE PARAMETERS

    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void TextureAtlas::loadAndApplyTextureImage(const std::string &filePath) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(
            filePath.c_str(),
            &width,
            &height,
            &nrChannels,
            0
    );
    if(width != height) {
        std::cout << "Failed to load texture. The texture image's width and height have to be the same";
        return;
    }
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture!" << std::endl;
        return;
    }
    TEXTURE_PACK_SIZE = width;
    stbi_image_free(data);
    textureFilepath = filePath;
    std::cout << "Texture loaded successfully" << std::endl;
}

void TextureAtlas::changeTexture(const std::string &filePath) {
    glBindTexture(GL_TEXTURE_2D, ID);
    loadAndApplyTextureImage(filePath);
}

void TextureAtlas::bindTexture() const {
    glBindTexture(GL_TEXTURE_2D, ID);
}
