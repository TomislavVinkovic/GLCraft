#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
    : shader(
            Shader(
                "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedVertexShader.vert",
                "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedFragmentShader.frag"
            )
    ), testTexture(BasicTexture("/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/grass_simple.jpg"))
    {
        ChunkGenerator generator({16,16,16}, {0,0,-5});
        testChunk = generator.generate();
        testChunk.generateGraphicsData();
    }

ChunkRenderer::ChunkRenderer(
        const std::string &vertexShaderPath,
        const std::string &fragmentShaderPath,
        const std::string &texturePath
    ) : shader(Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str())),
        testTexture(texturePath.c_str()) {

        ChunkGenerator generator({16,16,16}, {0,0,0});
        testChunk = generator.generate();
        testChunk.generateGraphicsData();
    }

void ChunkRenderer::render(Camera &camera) {
    shader.use();
    testTexture.bindTexture();
//    for(const auto& chunk : chunks) {
//        chunk.bindVAO();
//        glm::mat4 model = glm::mat4(1.f);
//
//        shader.setMatrix4fv("view", camera.GetViewMatrix());
//        shader.setMatrix4fv("projection", camera.GetProjectionMatrix());
//        shader.setMatrix4fv("model", model);
//
//        chunk.bindEBO();
//        glDrawElements(GL_TRIANGLES, chunk.getIndices().size(), GL_UNSIGNED_INT, 0);
//    }

    testChunk.bindVAO();
    glm::mat4 model = glm::mat4(1.f);
    shader.setMatrix4fv("projection", camera.GetProjectionMatrix());
    shader.setMatrix4fv("model", model);
    shader.setMatrix4fv("view", camera.GetViewMatrix());

    testChunk.bindEBO();
    glDrawElements(GL_TRIANGLES, testChunk.getIndices().size(), GL_UNSIGNED_INT, 0);

}

void ChunkRenderer::deleteData() {
    for(auto& chunk : chunks) {
        chunk.deleteGraphicsData();
    }
}
