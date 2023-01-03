#pragma once

#include <vector>
#include <memory>
#include<string>

#include "Context.h"
#include "Camera.h"
#include "StateAbstract.h"
#include "Renderer.h"

class Application {
    public:
        Application(unsigned int w, unsigned int h, const std::string& name, const Camera& camera);

        void runLoop();

        Camera& getCamera() {
            return this->context.camera;
        }

    private:
        std::vector<std::unique_ptr<StateAbstract>> states;

        Context context;
        Renderer renderer;

};
