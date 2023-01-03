#include "Application.h"
#include "StatePlaying.h"

//zasad cu hardkodirat atribute za renderer
Application::Application(unsigned int w, unsigned int h, const std::string &name, const Camera& camera)
    : context(Context(camera, w, h, name)), renderer(
        "/home/tomislav/Desktop/faks/3d/projekt/GLCraft/shaders/texturedVertexShader.vert",
        "/home/tomislav/Desktop/faks/3d/projekt/GLCraft/shaders/texturedFragmentShader.frag",
        "/home/tomislav/Desktop/faks/3d/projekt/GLCraft/textures/grass_simple.jpg"
    ) {}

void Application::runLoop() {
    while(!glfwWindowShouldClose(context.window)) {
        context.adjustDeltaTime();
        context.handleKeyboardInput(context.window); //kontinuriani input

        renderer.render(context.window, context.camera);
    }
    renderer.clearData();
    glfwTerminate();
}
