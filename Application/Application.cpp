#include "Application.h"

//zasad cu hardkodirat atribute za renderer
Application::Application(unsigned int w, unsigned int h, const std::string &name, const Camera& camera)
    : context(Context(camera, w, h, name)), renderer(
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedVertexShader.vert",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedFragmentShader.frag",
        {"/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/grass_simple.jpg"}
    ) {}

void Application::runLoop() {
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    while(!glfwWindowShouldClose(context.window)) {
        context.adjustDeltaTime();
        context.handleKeyboardInput(context.window); //kontinuriani input

        renderer.render(context.window, context.camera);
    }
    renderer.clearData();
    glfwTerminate();
}
