#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
    : shader(
            Shader(
                "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedVertexShader.vert",
                "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedFragmentShader.frag"
            )
    ), testTexture(BasicTexture("/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/grass_simple.jpg"))
    {
        //TODO: ISPRAVITI BUG SA Z-OSI U POZITIVNOM SMJERU
        ChunkGenerator generator;
        glm::vec3 defaultDimensions = glm::vec3(16,256,16);
        float positionZ = 0.f;
        float positionX = 0.f;
//        generator.newChunk(defaultDimensions, {0,0,-2});
//        Chunk c = generator.generate();
//        c.generateGraphicsData();
//        chunks.push_back(c);
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                generator.newChunk(defaultDimensions, {positionX, 0, positionZ});
                Chunk chunk = generator.generate();
                chunk.generateGraphicsData();
                chunks.push_back(chunk);
                positionX += 8; //stavljam 8 jer generacija chunka ide od kraja prema pocetku
            }
            positionZ += 8;
            positionX = 0;
        }
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

    glm::mat4 model = glm::mat4(1.f);
    shader.setMatrix4fv("projection", camera.GetProjectionMatrix());
    shader.setMatrix4fv("model", model);

    for(const auto& chunk : chunks) {
        chunk.bindVAO();
        shader.setMatrix4fv("view", camera.GetViewMatrix());
        chunk.bindEBO();

        glDrawElements(GL_TRIANGLES, chunk.getIndices().size(), GL_UNSIGNED_INT, 0);

        //unbinding
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

//    testChunk.bindVAO();
//    glm::mat4 model = glm::mat4(1.f);
//    shader.setMatrix4fv("projection", camera.GetProjectionMatrix());
//    shader.setMatrix4fv("model", model);
//    shader.setMatrix4fv("view", camera.GetViewMatrix());
//
//    testChunk.bindEBO();
//    glDrawElements(GL_TRIANGLES, testChunk.getIndices().size(), GL_UNSIGNED_INT, 0);

}

void ChunkRenderer::deleteData() {
    for(auto& chunk : chunks) {
        chunk.deleteGraphicsData();
    }
}
