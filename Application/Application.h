#pragma once

#include <vector>
#include <memory>
#include<string>
#include<thread>
#include <mutex>

#include "Context.h"
#include "Camera.h"
#include "Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"

class Application {
    public:
        Application(unsigned int w, unsigned int h, const std::string& name, const Camera& camera);

        void runLoop();

        Camera& getCamera() {
            return this->context.state.player.getCamera();
        }

    private:
        Context context;
        Renderer renderer;

};
