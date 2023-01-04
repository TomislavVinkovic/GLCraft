#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(const glm::vec3 &dimensions, const glm::vec3& position)
    : chunk(Chunk(dimensions, position)){}

Chunk ChunkGenerator::generate() {
    const auto& chunkDimensions = chunk.getDimensions();
    const auto& chunkPosition = chunk.getPosition();

    for(int y = chunkPosition.y; y < chunkPosition.y + chunkDimensions.y; y += 1) {
        for(int x = chunkPosition.x; x < chunkPosition.x + chunkDimensions.x; x += 1) {
            for(int z = chunkPosition.z; z < chunkPosition.z + chunkDimensions.z; z += 1) {
                glm::vec3 position = glm::vec3(x,y,z);
                const auto& block = chunk.block(position);
                //std::cout << x << " " << y << " " << z << std::endl;
                //no need to draw an air block
                if(block.getType() == ChunkBlockType::Air) {
                    continue;
                }

                //else, check of you should render specific faces
                directions.update(x,y,z);
                //std::cout << directions.top.x << " " << directions.top.y << " " << directions.top.z << std::endl;
                addFace(Face::backFace, position, directions.back);
                addFace(Face::frontFace, position, directions.front);
                addFace(Face::leftFace, position, directions.left);
                addFace(Face::rightFace, position, directions.right);
                addFace(Face::bottomFace, position, directions.bottom);
                addFace(Face::topFace, position, directions.top);
            }
        }
    }
    std::cout << "Number of faces generated: " << no_faces << std::endl;
    return chunk;
}

void ChunkGenerator::addFace(const std::vector<GLfloat>& face, const glm::vec3& position, const glm::vec3& adjBlockPos) {

    if(shouldGenerateFace(face, adjBlockPos)) {
        chunk.addFace(face, position);
        no_faces++;
        return;
    }
}

bool ChunkGenerator::shouldGenerateFace(const std::vector<GLfloat> &face, const glm::vec3 adjBlockPosition) {
    auto block = chunk.block(adjBlockPosition);
    //std::cout << (block.getType() == ChunkBlockType::Air) << std::endl;
    if(block.getType() == ChunkBlockType::Air) return true; //render a face if the adjacent block is not solid
    else return false;
}

int ChunkGenerator::getNumberOfFaces() {
    return no_faces;
}
