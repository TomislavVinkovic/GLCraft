#include "Application.h"

//zasad cu hardkodirat atribute za renderer
Application::Application(unsigned int w, unsigned int h, const std::string &name, const Camera& camera)
    : context(Context(camera, w, h, name)), renderer(
        w, h,
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedVertexShader.vert",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedFragmentShader.frag",
        {"/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/grass_simple.jpg"},
        &context.state.world
    ) {}

void Application::runLoop() {
    while(!glfwWindowShouldClose(context.window)) {
        context.adjustDeltaTime();
        context.handleKeyboardInput(context.window); //kontinuriani input

        renderer.render(context.window, context.state.player.getCamera());
    }
    renderer.clearData();
    glfwTerminate();
}
