#pragma once
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include "glm.hpp"
#include "Shader.hpp"

#include "Cube/CubeRenderer.h"
#include "Chunk/ChunkRenderer.h"
#include "UIRenderer/UIRenderer.h"

class Renderer {
    private:
        World* world;
        glm::vec4 clearColor;
        UIRenderer uiRenderer;
        CubeRenderer cubeRenderer;
        ChunkRenderer chunkRenderer;
    public:
        Renderer(
            unsigned int scr_width,
            unsigned int scr_height,
            const std::string& cubeVertexPath,
            const std::string& cubeFragmentPath,
            const std::vector<std::string>& cubeTextures,
            World* world,
            glm::vec4 clearColor = glm::vec4(0.f, 0.77f, 1.f, 1.0f)
        ) : cubeRenderer(CubeRenderer(cubeVertexPath, cubeFragmentPath, cubeTextures)),
            chunkRenderer(world), uiRenderer(scr_width, scr_height){
            this->world = world;
            this->clearColor = clearColor;
        }

        //void drawCube(const glm::vec3& pos);
        //void drawChunk(const glm::vec3& pos);

        void setCubeRenderer(const CubeRenderer& cubeRenderer);
        void setChunkRenderer(const ChunkRenderer& chunkRenderer);

        void render(GLFWwindow* window, Camera& camera);

        //ciscenje podataka na kraju
        void clearData();
};
