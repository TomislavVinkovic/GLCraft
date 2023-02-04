#include "Renderer.h"

void Renderer::setCubeRenderer(const CubeRenderer &cubeRenderer) {
    this->cubeRenderer = cubeRenderer;
}

void Renderer::setChunkRenderer(const ChunkRenderer &chunkRenderer) {
    this->chunkRenderer = chunkRenderer;
}

void Renderer::render(GLFWwindow *window, Camera &camera) {
    //std::cout << "Filled with fill color" << std::endl;
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    //glClearColor(0.f, 0.f, 0.f, 1.f); //when testing the skybox
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //ImGUI new frame
    ImGui_ImplGlfwGL3_NewFrame();

    //GRAPHICS RENDERING STARTS HERE...
    //skyboxRenderer.render(camera);

    chunkRenderer.render(camera);
    glDisable(GL_DEPTH_TEST);
    uiRenderer.render();
    glEnable(GL_DEPTH_TEST);

    //AND ENDS HERE...

    //ImGui rendering goes here
    imGuiRenderer.render();

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::clearData() {
    uiRenderer.deleteGraphicsData();
    cubeRenderer.deleteData();
    chunkRenderer.deleteData();
    skyboxRenderer.deleteData();
}
