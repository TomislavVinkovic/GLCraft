#include "CubeRenderer.h"

CubeRenderer::CubeRenderer(
        const std::string& vertexShaderPath,
       const std::string& fragmentShaderPath,
       const std::string& textureFilePath
    ) : shader(Shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str())),
        texture(BasicTexture(textureFilePath.c_str())){
    //default cube
    std::vector<GLfloat> vertices = {
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

    add(glm::vec3(0,0,0));
}

//I WILL ADD THESE LATER

//CubeRenderer::CubeRenderer(const CubeRenderer &cb) : CubeRenderer() {
//    pos = cb.pos;
//}
//
//void CubeRenderer::operator=(const CubeRenderer &cb) {
//    pos = cb.pos;
//}

void CubeRenderer::add(const glm::vec3 &pos) {
    this->pos.push_back(pos);
}

void CubeRenderer::render(Camera& camera) {
    texture.bindTexture();
    shader.use();
    block.bindVAO();

    //std::cout << "CubeRenderer[render] : Setting projection matrix" << std::endl;
    shader.setMatrix4fv("projection", camera.GetProjectionMatrix());

    for(const glm::vec3& p : pos) {
        //std::cout << p.x << " " << p.y << " " << p.z << std::endl;
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, p);

        shader.setMatrix4fv("model", model);
        shader.setMatrix4fv("view", camera.GetViewMatrix());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, block.getEBO());
        glDrawElements(GL_TRIANGLES, block.getIndicesCount(), GL_UNSIGNED_INT, 0);
    }

}

void CubeRenderer::deleteData() {
    block.deleteData();
}
