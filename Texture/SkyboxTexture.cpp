#include "SkyboxTexture.h"

SkyboxTexture::SkyboxTexture() : BasicTexture() {}

SkyboxTexture::SkyboxTexture(const std::string &filePath, unsigned int i, GLenum format) : BasicTexture(filePath, format) {
    this->i = i;
}

SkyboxTexture::~SkyboxTexture() {
    glDeleteTextures(1, &ID);
}

void SkyboxTexture::setTextureParameters() {
    //drukciji parametri teksture za skybox
    //bindTexture();
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyboxTexture::bindTexture() const {
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void SkyboxTexture::changeTexture(const std::string &filePath) {
    BasicTexture::changeTexture(filePath);
}

void SkyboxTexture::loadAndApplyTextureImage(const std::string &filePath) {
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
        stbi_set_flip_vertically_on_load(false);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
        stbi_set_flip_vertically_on_load(true);
    }
    else {
        std::cout << "Failed to load texture!" << std::endl;
        return;
    }
    stbi_image_free(data);
    textureFilepath = filePath;
    std::cout << "Texture loaded successfully" << std::endl;
}

SkyboxTexture SkyboxTexture::operator=(const SkyboxTexture &texture) {
    if(texture.ID != 0) glDeleteTextures(1, &ID);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    format = texture.format;

    setTextureParameters();

    loadAndApplyTextureImage(texture.textureFilepath);
    return *this;
}

void SkyboxTexture::i_increment() {
    i++;
}

void SkyboxTexture::i_decrement() {
    i--;
}

unsigned int SkyboxTexture::i_get() {
    return i;
}
