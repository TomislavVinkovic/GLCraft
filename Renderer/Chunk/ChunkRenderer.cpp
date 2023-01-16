#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(World* world)
    : ChunkRenderer(
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedVertexShader.vert",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedFragmentShader.frag",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/texture_pack_1.png",
        world
    ){}

ChunkRenderer::ChunkRenderer(
        const std::string &vertexShaderPath,
        const std::string &fragmentShaderPath,
        const std::string &texturePath,
        World* world
    ) : shader(Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str())),
        testTexture(texturePath.c_str(), GL_RGBA), world(world) {

        glm::vec3 defaultDimensions = glm::vec3(16,16,16);
        float positionZ = 0.f;
        float positionX = 0.f;

        std::vector<glm::vec3> chunkPositions;
        world->generate();
    }

void ChunkRenderer::render(Camera &camera) {
    shader.use();
    testTexture.bindTexture();

    glm::mat4 model = glm::mat4(1.f);
    shader.setMatrix4fv("projection", camera.GetProjectionMatrix());
    shader.setMatrix4fv("model", model);

    glEnable(GL_CULL_FACE);
    for(auto& chunk : world->getChunks()) {
        chunk.bindVAO();
        shader.setMatrix4fv("view", camera.GetViewMatrix());
        chunk.bindEBO();

        glDrawElements(GL_TRIANGLES, chunk.getIndices().size(), GL_UNSIGNED_INT, 0);
        //unbinding
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    glDisable(GL_CULL_FACE);
}

void ChunkRenderer::deleteData() {
    world->deleteData();
}
