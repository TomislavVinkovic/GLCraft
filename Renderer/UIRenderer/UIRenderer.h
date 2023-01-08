#pragma once

#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include "Shader.hpp"
#include <string>

class UIRenderer {
    private:
        unsigned int VAO;
        unsigned int VBO;
        Shader shader;

        void genVAO();
        void genVBO();
        void bindVAO();
        void bindVBO();
        void unbindVAO();
        void unbindVBO();

        const float crosshair_size = 0.f;
    public:
        void deleteGraphicsData();
        UIRenderer(unsigned int scr_width,
                   unsigned int scr_height
       );
        UIRenderer(
                unsigned int scr_width,
                unsigned int scr_height,
                const std::string& vertexShaderPath,
                const std::string& fragmentShaderPath
        );
        ~UIRenderer();

        void render();
};
