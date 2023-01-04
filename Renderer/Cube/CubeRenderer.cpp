#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(
    const std::string& vertexShaderPath,
    const std::string& fragmentShaderPath,
    const std::vector<std::string>& textures
    ) : shader(Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str())),
    testTexture(BasicTexture(textures[0].c_str())){
    //default cube
    std::vector<GLfloat> vertices = {
            //Back
            1, 0, 0, 0.f, 0.f,
            0, 0, 0, 1.f, 0.f,
            0, 1, 0, 1.f, 1.f,
            1, 1, 0, 0.f, 1.f,

            //Front
            0, 0, 1, 0.f, 0.f,
            1, 0, 1, 1.f, 0.f,
            1, 1, 1, 1.f, 1.f,
            0, 1, 1, 0.f, 1.f,

            //Right
            1, 0, 1, 0.f, 0.f,
            1, 0, 0, 1.f, 0.f,
            1, 1, 0, 1.f, 1.f,
            1, 1, 1, 0.f, 1.f,

            //Left
            0, 0, 0, 0.f, 0.f,
            0, 0, 1, 1.f, 0.f,
            0, 1, 1, 1.f, 1.f,
            0, 1, 0, 0.f, 1.f,

            //Top
            0, 1, 1, 0.f, 0.f,
            1, 1, 1, 1.f, 0.f,
            1, 1, 0, 1.f, 1.f,
            0, 1, 0, 0.f, 1.f,

            //Bottom
            0, 0, 0, 0.f, 0.f,
            1, 0, 0, 1.f, 0.f,
            1, 0, 1,  1.f, 1.f,
            0, 0, 1, 0.f, 1.f
    };

    std::vector<GLuint> indices = {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
    };

    block.setVertices(vertices);
    block.setIndices(indices);

//    for(auto text : textures) {
//        std::cout << text << std::endl;
//        this->textures.push_back(BasicTexture(text.c_str()));
//    }


    add({glm::vec3(0,0,0), 0});

//    for(int k = 0; k < 1; k++) {
//        for(int i = 0; i < 1; i++) {
//            for(int j = 0; j < 1; j++) {
//                add({
//                    glm::vec3(i, k, j), 0
//                });
//                }
//            }
//    }
}

void CubeRenderer::add(const PositionTexturePair &pos) {
    this->pos.push_back(pos);
}

void CubeRenderer::render(Camera& camera) {
    shader.use();
    testTexture.bindTexture();
    block.bindVAO();
    for(const auto& p : pos) {
//        shader.use();
//        //textures[p.second].bindTexture();
//        block.bindVAO();


        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, p.first);

        shader.setMatrix4fv("projection", camera.GetProjectionMatrix());
        shader.setMatrix4fv("model", model);
        shader.setMatrix4fv("view", camera.GetViewMatrix());

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block.getEBO());
        glDrawElements(GL_TRIANGLES, block.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

}

void CubeRenderer::deleteData() {
    block.deleteData();
}
