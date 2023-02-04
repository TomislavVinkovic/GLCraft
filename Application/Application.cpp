#include "Application.h"

//zasad cu hardkodirat atribute za renderer
Application::Application(unsigned int w, unsigned int h, const std::string &name, const Camera& camera)
    : context(Context(camera, w, h, name)), renderer(
        w, h,
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedVertexShader.vert",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedFragmentShader.frag",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/skyboxVertexShader.vert",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/skyboxFragmentShader.frag",
        {"/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/grass_simple.jpg"},
        &context
    ) {}

void Application::runLoop() {
    //ImGui setup
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(context.window, false, NULL);
    ImGui::StyleColorsDark();

    //Main render loop
    while(!glfwWindowShouldClose(context.window)) {
        context.adjustDeltaTime();
        context.handleKeyboardInput(context.window); //kontinuriani input

        renderer.render(context.window, context.state.player.getCamera());
    }
    //ImGui cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    //Graphics renderer cleanup
    renderer.clearData();
    glfwTerminate();
}
