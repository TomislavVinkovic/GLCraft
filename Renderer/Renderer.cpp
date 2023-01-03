#include "Renderer.h"

void Renderer::drawCube(const glm::vec3 &pos) {
    cubeRenderer.add(pos);
}

void Renderer::setCubeRenderer(const CubeRenderer &cubeRenderer) {
    this->cubeRenderer = cubeRenderer;
}

void Renderer::setChunkRenderer(const ChunkRenderer &chunkRenderer) {
    this->chunkRenderer = chunkRenderer;
}

void Renderer::render(GLFWwindow *window, Camera &camera) {
    //std::cout << "Filled with fill color" << std::endl;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //std::cout << "Entering cube renderer" << std::endl;
    cubeRenderer.render(camera);

    //std::cout << "swapping buffers" << std::endl;
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::clearData() {
    cubeRenderer.deleteData();
    chunkRenderer.deleteData();
}
