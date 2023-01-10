#include "SkyboxRenderer.h"

void SkyboxRenderer::genVAO() {
    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
    }
    glGenVertexArrays(1, &VAO);
}

void SkyboxRenderer::genVBO() {
    if(VBO != 0) {
        glDeleteBuffers(1, &VBO);
    }
    glGenBuffers(1, &VBO);
}

void SkyboxRenderer::genEBO() {
    if(EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
    glGenBuffers(1, &EBO);
}

void SkyboxRenderer::bindVAO() {
    glBindVertexArray(VAO);
}

void SkyboxRenderer::bindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void SkyboxRenderer::bindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

unsigned int SkyboxRenderer::getVAO() {
    return VAO;
}

unsigned int SkyboxRenderer::getVBO() {
    return VBO;
}

unsigned int SkyboxRenderer::getEBO() {
    return EBO;
}

SkyboxRenderer::SkyboxRenderer(
        const std::string &vertShaderPath, const std::string &fragShaderPath,
        const std::string &topTexturePath, const std::string &bottomTexturePath,
        const std::string &middleTexturePath
        ) : shader(vertShaderPath.c_str(), fragShaderPath.c_str()),
            topTexture(topTexturePath, 0, GL_RGBA),
            middleTexture(middleTexturePath, 1,GL_RGBA),
            bottomTexture(bottomTexturePath, 2, GL_RGBA)
{
    float skyboxVertices[] =
    {
            //   Coordinates
            -1.0f, -1.0f,  1.0f,//        7--------6
            1.0f, -1.0f,  1.0f,//       /|       /|
            1.0f, -1.0f, -1.0f,//      4--------5 |
            -1.0f, -1.0f, -1.0f,//      | |      | |
            -1.0f,  1.0f,  1.0f,//      | 3------|-2
            1.0f,  1.0f,  1.0f,//      |/       |/
            1.0f,  1.0f, -1.0f,//      0--------1
            -1.0f,  1.0f, -1.0f
    };

    unsigned int skyboxIndices[] =
    {
            // Right
            1, 2, 6,
            6, 5, 1,
            // Left
            0, 4, 7,
            7, 3, 0,
            // Top
            4, 5, 6,
            6, 7, 4,
            // Bottom
            0, 3, 2,
            2, 1, 0,
            // Back
            0, 1, 5,
            5, 4, 0,
            // Front
            3, 7, 6,
            6, 2, 3
    };

    //load vertices and indices
    genVAO();
    bindVAO();

    genVBO();
    bindVBO();
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    genEBO();
    bindEBO();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), skyboxIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

SkyboxRenderer::~SkyboxRenderer() {
    deleteData();
}

void SkyboxRenderer::deleteData() {
    if(VAO != 0) {
        VAO = 0;
        glDeleteVertexArrays(1, &VAO);
    }
    if(VBO != 0) {
        VBO = 0;
        glDeleteBuffers(1, &VBO);
    }
    if(EBO != 0) {
        EBO = 0;
        glDeleteBuffers(1, &EBO);
    }
}

void SkyboxRenderer::render() {
    //TODO: Implement the skybox renderer
}

void SkyboxRenderer::unbindVAO() {
    glBindVertexArray(0);
}

void SkyboxRenderer::unbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SkyboxRenderer::unbindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
