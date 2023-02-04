#pragma once

#include "Context.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

class ImGuiRenderer {
    private:
        Context* context = nullptr;
    public:
        ImGuiRenderer() = default;
        ImGuiRenderer(Context* context);
        void render();

        //setters
        void setContext(Context* context);
};
