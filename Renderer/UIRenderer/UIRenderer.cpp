#include "UIRenderer.h"

UIRenderer::UIRenderer(
        unsigned int scr_width,
        unsigned int scr_height,
        const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath
) : shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str()){
    float SCR_WIDTH = static_cast<float>(scr_width);
    float SCR_HEIGHT = static_cast<float>(scr_height);
    float vertices[] = {
            -0.01, 0.0,
            0.01, 0.0,

            0.0, -0.02,
            0.0, 0.02
    };

    genVAO();
    genVBO();
    
    bindVAO();
    bindVBO();
    shader.use();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    unbindVAO();
    unbindVBO();
}

UIRenderer::UIRenderer(unsigned int scr_width, unsigned int scr_height)
    : UIRenderer(
            scr_width, scr_height,
            "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/uiVertexShader.vert",
            "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/uiFragmentShader.frag"
    ){}

UIRenderer::~UIRenderer() {
    if(VAO != 0) {
        deleteGraphicsData();
    }
}

void UIRenderer::genVAO() {
    glGenVertexArrays(1, &VAO);
}

void UIRenderer::genVBO() {
    glGenBuffers(1, &VBO);
}

void UIRenderer::bindVAO() {
    glBindVertexArray(VAO);
}

void UIRenderer::bindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void UIRenderer::unbindVAO() {
    glBindVertexArray(0);
}

void UIRenderer::unbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void UIRenderer::deleteGraphicsData() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    VBO = 0;
    VAO = 0;
}

void UIRenderer::render() {
    shader.use();
    bindVAO();
    bindVBO();
    glDrawArrays(GL_LINES, 0, 4);

    unbindVAO();
    unbindVBO();
}
