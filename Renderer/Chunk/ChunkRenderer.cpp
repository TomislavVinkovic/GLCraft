#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer()
    : ChunkRenderer(
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedVertexShader.vert",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/shaders/texturedFragmentShader.frag",
        "/home/tomislav/Desktop/faks/Projekt3D/GLCraft/textures/texture_pack_1.png"
    ){}

ChunkRenderer::ChunkRenderer(
        const std::string &vertexShaderPath,
        const std::string &fragmentShaderPath,
        const std::string &texturePath
    ) : shader(Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str())),
        testTexture(texturePath.c_str(), GL_RGBA) {

        glm::vec3 defaultDimensions = glm::vec3(16,16,16);
        float positionZ = 0.f;
        float positionX = 0.f;

        std::vector<glm::vec3> chunkPositions;

    //        for(int i = 0; i < 10; i++) {
//            for(int j = 0; j < 10; j++) {
//                for(int k = 0; k < 10; k++) {
//                    chunkPositions.push_back({positionX, positionY, positionZ});
//                    positionX += 8;
//                }
//                positionX = 0;
//                positionZ += 8;
//            }
//            //positionX = 0;
//            positionZ = 0;
//            positionY -= 8;
//        }

        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++) {
                chunkPositions.push_back({positionX, 0, positionZ});
                positionX += 8;
            }
            positionZ += 8;
            positionX = 0;
        }
//        for(const auto& pos : chunkPositions) {
//            std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
//        }

        ChunkGenerator generator{chunkPositions};
        chunks = generator.generate();
        for(auto& chunk : chunks) {
            chunk.generateGraphicsData();
        }
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
