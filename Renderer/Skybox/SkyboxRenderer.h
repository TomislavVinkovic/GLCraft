#pragma once

#include <vector>
#include <string>
#include <array>

#include "CubeMap.h"
#include "Shader.hpp"
#include "Camera.h"

class SkyboxRenderer {
    private:
        unsigned int VAO = 0;
        unsigned int VBO = 0;
        unsigned int EBO = 0;

        unsigned int no_indices = 0;

        void genVAO();
        void genVBO();
        void genEBO();

        void bindVAO();
        void bindVBO();
        void bindEBO();

        void unbindVAO();
        void unbindVBO();
        void unbindEBO();

        CubeMap cubemap;
        Shader shader;

    public:
        unsigned int getVAO();
        unsigned int getVBO();
        unsigned int getEBO();

        SkyboxRenderer(
            const std::string& vertShaderPath,
            const std::string& fragShaderPath,
            const std::string& topTexturePath,
            const std::string& bottomTexturePath,
            const std::string& middleTexturePath
        );

        ~SkyboxRenderer();

        void deleteData();
        void render(const Camera& camera);

};
