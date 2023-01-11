#include "Renderer.h"

void Renderer::setCubeRenderer(const CubeRenderer &cubeRenderer) {
    this->cubeRenderer = cubeRenderer;
}

void Renderer::setChunkRenderer(const ChunkRenderer &chunkRenderer) {
    this->chunkRenderer = chunkRenderer;
}

void Renderer::render(GLFWwindow *window, Camera &camera) {
    //std::cout << "Filled with fill color" << std::endl;
    //glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skyboxRenderer.render(camera);
    glEnable(GL_CULL_FACE);
    chunkRenderer.render(camera);
    glDisable(GL_DEPTH_TEST);
    //tu negdje ce ici skyboxRenderer.render()...
    uiRenderer.render();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::clearData() {
    uiRenderer.deleteGraphicsData();
    cubeRenderer.deleteData();
    chunkRenderer.deleteData();
    skyboxRenderer.deleteData();
}
