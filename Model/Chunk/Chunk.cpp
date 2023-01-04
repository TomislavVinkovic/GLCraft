#include "Chunk.h"

//TODO: Add random chunk generation
Chunk::Chunk(const glm::vec3 &dimensions, const glm::vec3& position) : dimensions(dimensions), position(position) {

    for(int k = position.y; k < position.y + dimensions.y; k += 1) {
        for(int i = position.x; i < position.x + dimensions.x; i += 1) {
            for(int j = position.z; j < position.z + dimensions.z; j += 1) {
                blocks.push_back(ChunkBlock(glm::vec3(
                        static_cast<float>(i), //x
                        static_cast<float>(k), //y
                        static_cast<float>(j) //z
                ),
        ChunkBlockType::Grass));
            }
        }
    }
    std::cout << blocks.size() << std::endl;
}

const std::vector<ChunkBlock> &Chunk::getBlocks() {
    return blocks;
}

const glm::vec3 &Chunk::getDimensions() const{
    return dimensions;
}

ChunkBlock Chunk::block(const glm::vec3 &searchPosition) const {

    //ako je blok out of bounds, vrati air blok, to znaci da se lice nece renderati
    bool containedInX = searchPosition.x >= position.x && searchPosition.x < position.x + dimensions.x;
    bool containedInY = searchPosition.y >= position.y && searchPosition.y < position.y + dimensions.y;
    bool containedInZ = searchPosition.z >= position.z && searchPosition.z < position.z + dimensions.z;
    if(
        !containedInX || !containedInY || !containedInZ
    ) {
        return ChunkBlock(searchPosition, ChunkBlockType::Air);
    }
    //ili Flat[x + WIDTH * (y + DEPTH * z)] = Original[x, y, z]
    auto xOffset = abs(position.x);
    auto yOffsetFromZero = abs(position.y);
    auto zOffsetFromZero = abs(position.z);
    return blocks[(searchPosition.x + xOffset) + dimensions.x * ((searchPosition.y + yOffsetFromZero) + dimensions.y * (searchPosition.z + zOffsetFromZero))];
}

void Chunk::addFace(const std::vector<GLfloat> &face, const glm::vec3 &blockPosition) {
    //there are 3 vertices inside a face
//    std::cout << blockPosition.x << " ";
//    std::cout << blockPosition.y << " ";
//    std::cout << blockPosition.z << std::endl;
//    std::cout << face[0] + this->position.x  + blockPosition.x << " ";
//    std::cout << face[1] + this->position.y  + blockPosition.y << " ";
//    std::cout << face[2] + this->position.z  + blockPosition.z << std::endl;
    for(int i = 0, j = 0; i < 4; i++) {
        vertices.push_back(face[j++] + this->position.x + blockPosition.x);
        vertices.push_back(face[j++] + this->position.y + blockPosition.y);
        vertices.push_back(face[j++] + this->position.z + blockPosition.z);

        //pushing back texture coordinates
        vertices.push_back(face[j++]); //texture x
        vertices.push_back(face[j++]); //texture y
    }
    //update indices
    indices.insert(indices.end(), {
        currentVIndex,
        currentVIndex + 1,
        currentVIndex + 2,

        currentVIndex + 2,
        currentVIndex + 3,
        currentVIndex
    });
    currentVIndex += 4;
}

const glm::vec3 &Chunk::getPosition() const{
    return position;
}

void Chunk::generateGraphicsData() {
    if(VAO == 0) genVao();
    if(VBO == 0) genVbo();
    if(EBO == 0) genEbo();

    bindVAO();
    bindVBO();

    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(GLfloat),
            vertices.data(),
            GL_STATIC_DRAW //mozda ce morati biti dynamic
    );
    //atribut pozicije
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    //atribut teksturne koordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    bindEBO();
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(GLuint),
            indices.data(),
            GL_STATIC_DRAW
    );
    //TU SAM STAO
}

void Chunk::deleteGraphicsData() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    VAO = 0;
    VBO = 0;
    EBO = 0;
}

void Chunk::genEbo() {
    glGenBuffers(1, &EBO);
}

void Chunk::genVbo() {
    glGenBuffers(1, &VBO);
}

void Chunk::genVao() {
    glGenVertexArrays(1, &VAO);
}

void Chunk::bindVAO() const{
    glBindVertexArray(VAO);
}

void Chunk::bindEBO() const{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Chunk::bindVBO() const {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}


unsigned int Chunk::getVAO() const{
    return VAO;
}

unsigned int Chunk::getEBO() const{
    return EBO;
}

void Chunk::updateGraphicsData() {
    //TODO: IMPLEMENT EXCEPTION HANDLING
    //TODO: IMPLEMENT THIS FUNCTION
    std::cout << "Update graphics data not implemented" << std::endl;
    return;
}

const std::vector<GLuint> &Chunk::getIndices() const {
    return indices;
}

Chunk Chunk::operator=(Chunk chunk) {
    VAO = chunk.VAO;
    EBO = chunk.EBO;
    VBO = chunk.VBO;

    blocks = chunk.blocks;
    dimensions = chunk.dimensions;
    position = chunk.position;
    vertices = chunk.vertices;
    indices = chunk.indices;

    currentVIndex = chunk.currentVIndex;

    return *this;
}

const std::vector<GLfloat> &Chunk::getVertices() const {
    return vertices;
}
