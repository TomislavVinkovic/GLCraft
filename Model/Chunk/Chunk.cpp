#include "Chunk.h"

//TODO: Add random chunk generation
Chunk::Chunk(const glm::vec3 &dimensions, const glm::vec3& position) : dimensions(dimensions), position(position) {
      //this will all be air blocks
      for(int k = position.y; k < position.y + dimensions.y; k += 1) {
            for(int i = position.x; i < position.x + dimensions.x; i += 1) {
                for(int j = position.z; j < position.z + dimensions.z; j += 1) {
                    blocks.push_back(ChunkBlock({
                            static_cast<int>(i),
                            static_cast<int>(k),
                            static_cast<int>(j)
                    }, &block_type::AirBlock));
                }
        }
    }
}

const std::vector<ChunkBlock> &Chunk::getBlocks() {
    return blocks;
}

const glm::vec3 &Chunk::getDimensions() const{
    return dimensions;
}

ChunkBlock Chunk::block(const glm::vec3 &searchPosition, bool logInfo) const {
    if(logInfo) {
        //std::cout << searchPosition.x << " " << searchPosition.y << " " << searchPosition.z << std::endl;
    }
    //ako je blok out of bounds, vrati air blok, to znaci da se lice nece renderati
    bool containedInX = searchPosition.x >= position.x && searchPosition.x < position.x + dimensions.x;
    bool containedInY = searchPosition.y >= position.y && searchPosition.y < position.y + dimensions.y;
    bool containedInZ = searchPosition.z >= position.z && searchPosition.z < position.z + dimensions.z;
    if(
        !containedInX || !containedInY || !containedInZ
    ) {
        return ChunkBlock(searchPosition, &block_type::AirBlock);
    }
//    if(logInfo) {
//        std::cout << "block found" << std::endl;
//    }
    int relX = static_cast<int>(floor(searchPosition.x)) & (static_cast<int>(dimensions.x)-1);
    int relY = static_cast<int>(floor(searchPosition.y)) & (static_cast<int>(dimensions.y)-1);
    int relZ = static_cast<int>(floor(searchPosition.z)) & (static_cast<int>(dimensions.z)-1);

    int offset = relX + dimensions.x * (relY + dimensions.y * relZ);
    return blocks[offset];
}



void Chunk::addFace(
        const ChunkBlock& block,
        const std::vector<GLfloat> &face,
        const glm::vec3 &blockPosition,
        const std::vector<GLfloat>& textureCoords
) {
    auto v = &vertices;
    if(hasWater && block.getData()->blockType == ChunkBlockType::Water) {
        v = &verticesWater;
    }

    for(int i = 0, j = 0, k=0; i < 4; i++) {
        v->push_back(face[j++] + blockPosition.x);
        v->push_back(face[j++] + blockPosition.y);
        v->push_back(face[j++] + blockPosition.z);

        //pushing back texture coordinates
        //both coordinates are normalized between 0 and 1
        float textureX = static_cast<float>(textureCoords[k++])/TEXTURE_PACK_SIZE;
        float textureY = 1.f - static_cast<float>(textureCoords[k++])/TEXTURE_PACK_SIZE;
        //std::cout << textureX << " " << textureY << std::endl;
        v->push_back(textureX); //texture x
        v->push_back(textureY); //texture y

        //adding opacity
        //for now let all values be 1
        if(block.getData()->blockType == ChunkBlockType::Water) {
            v->push_back(0.7f);
        }
        else v->push_back(1.f);

        //adding face lighting information
        //left and right face : 0.86
        //front and back face : 0.80
        //bottom face: 0.50
        //top face : 1.0
        if((face == Face::frontFace || face == Face::backFace) && block.getData()->blockType != ChunkBlockType::Water) {
            v->push_back(0.80f);
        }

        else if((face == Face::leftFace || face == Face::rightFace) && block.getData()->blockType != ChunkBlockType::Water) {
            v->push_back(0.7f);
        }

        else if(face == Face::bottomFace && block.getData()->blockType != ChunkBlockType::Water) {
            v->push_back(0.5f);
        }

        else {
            v->push_back(1.0f);
        }
    }
    //update indices
    if(hasWater && block.getData()->blockType == ChunkBlockType::Water) {
        indicesWater.insert(indicesWater.end(), {
                currentVIndexWater,
                currentVIndexWater + 1,
                currentVIndexWater + 2,

                currentVIndexWater + 2,
                currentVIndexWater + 3,
                currentVIndexWater
        });
        currentVIndexWater += 4;
    }

    else {
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
}

const glm::vec3 &Chunk::getPosition() const{
    return position;
}

void Chunk::generateGraphicsData() {
    if(VAO == 0) genVao();
    if(VBO == 0) genVbo();
    if(EBO == 0) genEbo();

    //water data
    if(hasWater) {
        if(VAO_WATER == 0) genVaoWater();
        if(VBO_WATER == 0) genVboWater();
        if(EBO_WATER == 0) genEboWater();

        bindVAOWater();
        bindVBOWater();

        glBufferData(
                GL_ARRAY_BUFFER,
                verticesWater.size() * sizeof(GLfloat),
                verticesWater.data(),
                GL_STATIC_DRAW //mozda ce morati biti dynamic
        );
        //atribut pozicije
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        //atribut teksturne koordinate
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        //atribut prozirnosti
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        //atribut osvjetljenosti
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(3);

        bindEBOWater();
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                indicesWater.size() * sizeof(GLuint),
                indicesWater.data(),
                GL_STATIC_DRAW
        );
    }

    bindVAO();
    bindVBO();

    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(GLfloat),
            vertices.data(),
            GL_STATIC_DRAW //mozda ce morati biti dynamic
    );
    //atribut pozicije
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    //atribut teksturne koordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //atribut prozirnosti
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    //atribut osvjetljenosti
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);

    bindEBO();
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(GLuint),
            indices.data(),
            GL_STATIC_DRAW
    );

    //test ovoga
    //clearData();
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
    bindVAO();
    bindVBO();
    glBufferData(
            GL_ARRAY_BUFFER,
            vertices.size() * sizeof(GLfloat),
            vertices.data(),
            GL_STATIC_DRAW //mozda ce morati biti dynamic
    );

    bindEBO();
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            indices.size() * sizeof(GLuint),
            indices.data(),
            GL_STATIC_DRAW
    );
    //test ovoga
    //clearData();
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


///This function has 2 primary tasks
///The first task is to edit whichever block is passed to the function
///The other task is to check whether or not that block is an edge block. If the given block is an edge block,
///Push back the positions of all chunks that are surrounding the block to the vector of chunks passed by refference
void Chunk::editBlock(
        const glm::vec3 &searchPosition,
        const ChunkBlockData* blockData,
        std::vector<glm::vec3>& surroundingChunkPositions
) {
    auto block = blockInner(searchPosition);
    if(block != blocks.end()) {
        checkEdgeBlock(searchPosition, surroundingChunkPositions);
        *block = ChunkBlock(searchPosition, blockData);
    }
}

std::vector<ChunkBlock>::iterator Chunk::blockInner(const glm::vec3 &searchPosition) {
    //ako je blok out of bounds, vrati air blok, to znaci da se lice nece renderati
    bool containedInX = searchPosition.x >= position.x && searchPosition.x < position.x + dimensions.x;
    bool containedInY = searchPosition.y >= position.y && searchPosition.y < position.y + dimensions.y;
    bool containedInZ = searchPosition.z >= position.z && searchPosition.z < position.z + dimensions.z;
    if(!containedInX || !containedInY || !containedInZ) {
        return blocks.end();
    }
    int relX = static_cast<int>(floor(searchPosition.x)) & (static_cast<int>(dimensions.x)-1);
    int relY = static_cast<int>(floor(searchPosition.y)) & (static_cast<int>(dimensions.y)-1);
    int relZ = static_cast<int>(floor(searchPosition.z)) & (static_cast<int>(dimensions.z)-1);

    int offset = relX + dimensions.x * (relY + dimensions.y * relZ);
    return blocks.begin() + offset;
}

void Chunk::checkEdgeBlock(const glm::vec3& searchPosition, std::vector<glm::vec3> &surroundingChunkPositions) {
    AdjacentChunkPositions adjacentChunkPositions;
    adjacentChunkPositions.update(position.x, position.y, position.z);
    if(searchPosition.x == position.x) {
        surroundingChunkPositions.push_back({position.x-16, position.y, position.z});
    }
    if(searchPosition.x == position.x + (dimensions.x - 1)) {
        surroundingChunkPositions.push_back({position.x+16, position.y, position.z});
    }
    if(searchPosition.y == position.y) {
        surroundingChunkPositions.push_back({position.x, position.y-16, position.z});
    }
    if(searchPosition.y == position.y + (dimensions.y - 1)) {
        surroundingChunkPositions.push_back({position.x, position.y+16, position.z});
    }
    //jos provjeriti za ovo kod back i front za z
    if(searchPosition.z == position.z) {
        surroundingChunkPositions.push_back({position.x, position.y, position.z-16});
    }
    if(searchPosition.z == position.z + (dimensions.z - 1)) {
        surroundingChunkPositions.push_back({position.x, position.y, position.z+16});
    }
}

void Chunk::clearData() {
    vertices.clear();
    indices.clear();
    currentVIndex = 0;
}

void Chunk::placeBlock(const glm::vec3 &pos, const ChunkBlockData* blockData) {
    //checking boundaries for now
    bool containedInX = pos.x >= position.x && pos.x < position.x + dimensions.x;
    bool containedInY = pos.y >= position.y && pos.y < position.y + dimensions.y;
    bool containedInZ = pos.z >= position.z && pos.z < position.z + dimensions.z;
    //do not place the block if it is out of bounds
    if(!containedInX || !containedInY || !containedInZ) return;

    int relX = static_cast<int>(floor(pos.x)) & (static_cast<int>(dimensions.x)-1);
    int relY = static_cast<int>(floor(pos.y)) & (static_cast<int>(dimensions.y)-1);
    int relZ = static_cast<int>(floor(pos.z)) & (static_cast<int>(dimensions.z)-1);

    int offset = relX + dimensions.x * (relY + dimensions.y * relZ);

    //TODO: implement setters to solve copying
    blocks[offset] = ChunkBlock(pos, blockData);
}

bool Chunk::getAirStatus() {
    return airChunk;
}

void Chunk::setAirStatus(bool status) {
    airChunk = status;
}

void Chunk::sortByOpacity() {
    std::sort(blocks.begin(), blocks.end(), [](const ChunkBlock& a, const ChunkBlock& b) {
        return a.getOpacity() > b.getOpacity();
    });
}

bool Chunk::getHasWater() {
    return hasWater;
}

void Chunk::setHasWater(bool water) {
    hasWater = water;
}

void Chunk::genEboWater() {
    glGenBuffers(1, &EBO_WATER);
}

void Chunk::genVboWater() {
    glGenBuffers(1, &VBO_WATER);
}

void Chunk::genVaoWater() {
    glGenVertexArrays(1, &VAO_WATER);
}

void Chunk::bindVAOWater() const {
    glBindVertexArray(VAO_WATER);
}

void Chunk::bindVBOWater() const {
    glBindBuffer(GL_ARRAY_BUFFER, VBO_WATER);
}

void Chunk::bindEBOWater() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_WATER);
}

unsigned int Chunk::getVAOWater() const {
    return VAO_WATER;
}

unsigned int Chunk::getVBOWater() const {
    return VBO_WATER;
}

unsigned int Chunk::getEBOWater() const {
    return EBO_WATER;
}

const std::vector<GLuint> &Chunk::getWaterIndices() const {
    return indicesWater;
}

const std::vector<GLfloat> &Chunk::getWaterVertices() const {
    return verticesWater;
}
