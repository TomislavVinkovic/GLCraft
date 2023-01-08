#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "glad/glad.h"
#include<GLFW/glfw3.h>

#include "Camera.h"
#include "Chunk.h"
#include "ChunkBlockType.h"
#include "ChunkGenerator.h"
#include "Shader.hpp"
#include "AbstractObjectRenderer.h"
#include "AdjacentChunkPositions.h"

#include "BasicTexture.h"
#include "TextureAtlas.h"
#include "State.h"

#include <iostream>

class ChunkRenderer : public AbstractObjectRenderer {
    public:
        ChunkRenderer(World* world);
        ChunkRenderer(
                const std::string& vertexShaderPath,
                const std::string& fragmentShaderPath,
                const std::string& texturePath,
                World* world

        );

        void render(Camera& camera);
        void deleteData();

    private:
        World* world;
        Shader shader;
        TextureAtlas testTexture;
};