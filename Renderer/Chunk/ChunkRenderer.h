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

#include <iostream>

class ChunkRenderer : public AbstractObjectRenderer {
    public:
        ChunkRenderer();
        ChunkRenderer(
                const std::string& vertexShaderPath,
                const std::string& fragmentShaderPath,
                const std::string& texturePath
        );

        void render(Camera& camera);
        void deleteData();

    private:
        Shader shader;
        TextureAtlas testTexture;
        std::vector<Chunk> chunks;
};