#include "CubeMap.h"

CubeMap::CubeMap(const std::array<std::string, 6>& faces, GLenum format) {
    glGenTextures(1, &ID);
    bindTexture();
    this->format = format;

    int width, height, nrChannels;
    for (unsigned int i = 0; i < 6; i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    setTextureParameters();
}

void CubeMap::setTextureParameters() {
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMap::bindTexture() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubeMap::deleteData() {
    glDeleteTextures(1, &ID);
}

unsigned int CubeMap::getID() const {
    return ID;
}

CubeMap::~CubeMap() {
    //TODO: FIND A WAY TO SAFELY DELETE DATA
    //deleteData();
}
