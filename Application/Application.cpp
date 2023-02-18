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
    glfwSwapInterval(0);
    //Main render loop
    while(!glfwWindowShouldClose(context.window)) {
        context.adjustDeltaTime();
        context.handleKeyboardInput(context.window); //kontinuriani input

        context.state.world.sortChunksByDistanceToCamera(getCamera());
        renderer.render(context.window, context.state.player.getCamera());

        //generate the next chunk
        //generiranje grafickih podataka
        context.state.world.updatePositions();
        context.state.world.generateNext();
        context.state.world.sortChunksByDistanceToCamera(getCamera());
    }
    //ImGui cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    //Graphics renderer cleanup
    renderer.clearData();
    glfwTerminate();
}
