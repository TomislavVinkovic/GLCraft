#pragma once
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include "glm.hpp"

#include "Shader.hpp"
#include "Camera.h"
#include "Block/Block.h"
#include "BasicTexture.h"
#include "AbstractObjectRenderer.h"

#include <vector>
#include <string>

//a pair of a block position and its texture
typedef std::pair<glm::vec3, unsigned int> PositionTexturePair;

//TODO: Fix textures vector not working

class CubeRenderer : public AbstractObjectRenderer{
    public:
        CubeRenderer(
                const std::string& vertexShaderPath,
                const std::string& fragmentShaderPath,
                const std::vector<std::string>& textures
        );

        //void operator=(const CubeRenderer&);

        void add(const PositionTexturePair& bt);
        void render(Camera& camera);

//        void setShader();
//        void setTexture(const std::string& filePath);

        void deleteData();
    private:
        Shader shader;
        BasicTexture testTexture;
        std::vector<BasicTexture> textures;
        std::vector<PositionTexturePair> pos;
        Block block;
};
