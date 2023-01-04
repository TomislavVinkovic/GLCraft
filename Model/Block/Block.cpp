#include "Block.h"

Block::Block() {
    genVao();
}

void Block::setIndices(std::vector<GLuint> indices) {
    glBindVertexArray(VAO);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(GLuint),
            indices.data(),
            GL_STATIC_DRAW
    );
    indices_count = indices.size();
}

void Block::setVertices(std::vector<GLfloat> vertices) {
    glBindVertexArray(VAO);

    VBOs.push_back(0);
    glGenBuffers(1, &VBOs.back());
    glBindBuffer(GL_ARRAY_BUFFER, VBOs.back());
    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(GLfloat),
            vertices.data(),
            GL_STATIC_DRAW
    );

    //atribut pozicije
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //atribut teksturne koordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
