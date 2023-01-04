#pragma once
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include "glm.hpp"
#include "Shader.hpp"

#include "Cube/CubeRenderer.h"
#include "Chunk/ChunkRenderer.h"

class Renderer {
    private:
        glm::vec4 clearColor;
        CubeRenderer cubeRenderer;
        ChunkRenderer chunkRenderer{};
    public:
        Renderer(
            const std::string& cubeVertexPath,
            const std::string& cubeFragmentPath,
            const std::vector<std::string>& cubeTextures,
            glm::vec4 clearColor = glm::vec4(0.f, 0.77f, 1.f, 1.0f)
        ) : cubeRenderer(CubeRenderer(cubeVertexPath, cubeFragmentPath, cubeTextures)){
            this->clearColor = clearColor;
            glEnable(GL_DEPTH_TEST); //ukljuci z-buffer
        }

        //void drawCube(const glm::vec3& pos);
        //void drawChunk(const glm::vec3& pos);

        void setCubeRenderer(const CubeRenderer& cubeRenderer);
        void setChunkRenderer(const ChunkRenderer& chunkRenderer);

        void render(GLFWwindow* window, Camera& camera);

        //ciscenje podataka na kraju
        void clearData();
};
