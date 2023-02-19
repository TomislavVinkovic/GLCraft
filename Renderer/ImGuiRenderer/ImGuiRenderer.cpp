#include "ImGuiRenderer.h"

void ImGuiRenderer::render() {
    //ImGUI render

    //Framerate Counter
    {
        ImGui::SetNextWindowPos(ImVec2(20, 20));

        static float f = 0.0f;
        ImGui::Begin("FPS Counter");
        ImGui::SameLine();
        //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Framerate: %.1f FPS", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(20, 100));
        ImGui::SetNextWindowSize(ImVec2(300, 400));
    }

    //Inventory window
    {
        ImGui::Begin("Inventory");
        auto inventory = context->state.player.getInventory();
        for(const auto& item : inventory.getInventory()) {
            std::string name = block_type::getBlockDataByType(item.second.first).name;
            ImVec4 color(1.f, 1.f, 1.f, 1.f);
            if(name == "Air") {
                name = "Empty";
            }
            if(item.first == inventory.getSelectedSlot()) {
                color = {1.f, 1.f, 0.f, 1.f};
            }
            ImGui::TextColored(
                    color,
                    "%d. %s, %d",
                    item.first,
                    name.c_str(),
                    item.second.second
            );
            ImGui::NewLine();
        }
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiRenderer::ImGuiRenderer(Context *context) : context(context) {}

void ImGuiRenderer::setContext(Context *context) {
    this->context = context;
}
