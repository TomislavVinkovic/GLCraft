#include "SkyboxRenderer.h"

void SkyboxRenderer::genVAO() {
    if(VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    glGenVertexArrays(1, &VAO);
}

void SkyboxRenderer::genVBO() {
    if(VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    glGenBuffers(1, &VBO);
}

void SkyboxRenderer::genEBO() {
    if(EBO != 0) {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
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
        cubemap({
            middleTexturePath, middleTexturePath, topTexturePath,
            bottomTexturePath, middleTexturePath, middleTexturePath
        })
{
    float skyboxVertices[] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    //load vertices and indices
    genVAO();
    genVBO();
    //genEBO();

    bindVAO();
    bindVBO();

    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    shader.setInt("skybox", 0);
}

SkyboxRenderer::~SkyboxRenderer() {
    deleteData();
}

void SkyboxRenderer::deleteData() {
    //std::cout << "Skybox delete data called" << std::endl;
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

void SkyboxRenderer::render(const Camera& camera) {

    glDepthFunc(GL_LEQUAL);
    shader.use();
    glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    glm::mat4 projection = camera.GetProjectionMatrix();

    shader.setMatrix4fv("view", view);
    shader.setMatrix4fv("projection", projection);

    bindVAO();
    glActiveTexture(GL_TEXTURE0);
    cubemap.bindTexture();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    unbindVAO();
    glDepthFunc(GL_LESS);
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
