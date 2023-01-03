#pragma once
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader.hpp"
#include "Camera.h"
#include "Block.h"
#include "BasicTexture.h"

#include <vector>
#include <string>

class CubeRenderer {
    public:
        CubeRenderer(
                const std::string& vertexShaderPath,
                const std::string& fragmentShaderPath,
                const std::string& textureFilePath
        );

        //void operator=(const CubeRenderer&);

        void add(const glm::vec3& pos);
        void render(Camera& camera);

//        void setShader();
//        void setTexture(const std::string& filePath);

        void deleteData();
    private:
        Shader shader;
        BasicTexture texture;
        std::vector<glm::vec3> pos;
        Block block;
};
