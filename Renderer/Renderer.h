#pragma once
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader.hpp"

#include "Cube/CubeRenderer.h"
#include "Chunk/ChunkRenderer.h"
#include "UIRenderer/UIRenderer.h"
#include "Skybox/SkyboxRenderer.h"
#include "ImGuiRenderer/ImGuiRenderer.h"
#include "Context.h"

class Renderer {
    private:
        Context* context;

        glm::vec4 clearColor;
        UIRenderer uiRenderer;
        CubeRenderer cubeRenderer;
        ChunkRenderer chunkRenderer;
        SkyboxRenderer skyboxRenderer;
        ImGuiRenderer imGuiRenderer;

    public:
        Renderer(
            unsigned int scr_width,
            unsigned int scr_height,
            const std::string& cubeVertexPath,
            const std::string& cubeFragmentPath,
            const std::string& skyboxVertexPath,
            const std::string& skyboxFragmentPath,
            const std::vector<std::string>& cubeTextures,
            Context* context,
            glm::vec4 clearColor = glm::vec4(0.f, 0.77f, 1.f, 1.0f)
        ) : cubeRenderer(CubeRenderer(cubeVertexPath, cubeFragmentPath, cubeTextures)),
            chunkRenderer(&context->state.world), uiRenderer(scr_width, scr_height), context(context),
            skyboxRenderer(
                    skyboxVertexPath,
                    skyboxFragmentPath,
                    "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/skybox_top.png",
                    "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/skybox_bottom.png",
                    "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/skybox_middle.png"
            ){
            this->context = context;
            this->clearColor = clearColor;
            imGuiRenderer.setContext(context);
        }

        //void drawCube(const glm::vec3& pos);
        //void drawChunk(const glm::vec3& pos);

        void setCubeRenderer(const CubeRenderer& cubeRenderer);
        void setChunkRenderer(const ChunkRenderer& chunkRenderer);

        void render(GLFWwindow* window, Camera& camera);

        //ciscenje podataka na kraju
        void clearData();
};
