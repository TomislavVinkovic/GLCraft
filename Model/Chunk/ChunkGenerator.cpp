#include "ChunkGenerator.h"

ChunkGenerator::ChunkGenerator(const std::vector<glm::vec3>& chunkPositions, const glm::vec3& dimensions)
    : dimensions(dimensions),chunkPositions(chunkPositions) {}

std::vector<Chunk> ChunkGenerator::generate() {
    std::vector<Chunk> chunks(chunkPositions.size());
    std::unordered_map<std::string, Chunk*> chunkMap;
    int i = 0;

    for(const auto& chunkPosition : chunkPositions) {
        chunks[i] = Chunk(dimensions, chunkPosition);
        std::string key =
                std::to_string(static_cast<int>(chunkPosition.x)) + " "
                + std::to_string(static_cast<int>(chunkPosition.y)) + " "
                + std::to_string(static_cast<int>(chunkPosition.z));
        chunkMap.insert({key, &chunks[i]});
        i++;
    }
    //first generate blocks for all chunks
    for(auto& chunk : chunks) {
        auto heightMap = createChunkHeightMap(chunk);
        generateSmoothTerrain(chunk, heightMap);
    }
    //then create all rendering data
    for(auto& chunk : chunks) {
        generateChunk(chunk, chunkMap);
    }
    return chunks;
}

void ChunkGenerator::generateChunk(
        Chunk &chunk,
        const ChunkMap& chunkMap
) {
    const auto& chunkPosition = chunk.getPosition();
    chunkDirections.update(chunkPosition.x, chunkPosition.y, chunkPosition.z);
    for(const auto& block : chunk.getBlocks()) {
        glm::vec3 blockPosition = block.getPosition();
        if(block.getData()->blockType == ChunkBlockType::Air) {
            continue;
        }

        //else, check of you should render specific faces
        blockDirections.update(blockPosition.x,blockPosition.y,blockPosition.z);
        addFace(
                chunk, block, Face::backFace, blockPosition,
                blockDirections.back, chunkDirections.back, chunkMap
        );
        addFace(
                chunk, block, Face::frontFace, blockPosition,
                blockDirections.front,chunkDirections.front, chunkMap
        );
        addFace(
                chunk, block, Face::leftFace, blockPosition,
                blockDirections.left,chunkDirections.left, chunkMap
        );
        addFace(
                chunk, block, Face::rightFace, blockPosition,
                blockDirections.right,chunkDirections.right, chunkMap
        );
        addFace(
                chunk, block, Face::bottomFace, blockPosition,
                blockDirections.bottom,chunkDirections.bottom, chunkMap
        );
        addFace(
                chunk, block, Face::topFace, blockPosition,
                blockDirections.top,chunkDirections.top, chunkMap
        );
    }
}

void ChunkGenerator::addFace(
        Chunk& chunk,
        const ChunkBlock& block,
        const std::vector<GLfloat>& face,
        const glm::vec3& position,
        const glm::vec3& adjBlockPos,
        const glm::vec3& adjChunkPosition,
        const std::unordered_map<std::string, Chunk*>& chunkMap
) {

    if(shouldGenerateFace(chunk, adjBlockPos, adjChunkPosition, chunkMap)) {
        std::vector<GLfloat> texCoords;
        fillTextureCoords(block, texCoords, face);

        chunk.addFace(face, position, texCoords);
        no_faces++;
    }
}

void ChunkGenerator::fillTextureCoords(
        const ChunkBlock& block,
        std::vector<GLfloat> &texCoords,
        const std::vector<GLfloat> &face
) {
    if(face == Face::frontFace) {
        texCoords.push_back(block.getData()->frontFaceTextureMin.x);
        texCoords.push_back(block.getData()->frontFaceTextureMin.y);
        texCoords.push_back(block.getData()->frontFaceTextureMax.x);
        texCoords.push_back(block.getData()->frontFaceTextureMin.y);
        texCoords.push_back(block.getData()->frontFaceTextureMax.x);
        texCoords.push_back(block.getData()->frontFaceTextureMax.y);
        texCoords.push_back(block.getData()->frontFaceTextureMin.x);
        texCoords.push_back(block.getData()->frontFaceTextureMax.y);
    }

    if(face == Face::backFace) {
        texCoords.push_back(block.getData()->backFaceTextureMin.x);
        texCoords.push_back(block.getData()->backFaceTextureMin.y);
        texCoords.push_back(block.getData()->backFaceTextureMax.x);
        texCoords.push_back(block.getData()->backFaceTextureMin.y);
        texCoords.push_back(block.getData()->backFaceTextureMax.x);
        texCoords.push_back(block.getData()->backFaceTextureMax.y);
        texCoords.push_back(block.getData()->backFaceTextureMin.x);
        texCoords.push_back(block.getData()->backFaceTextureMax.y);
    }

    if(face == Face::leftFace) {
        texCoords.push_back(block.getData()->leftFaceTextureMin.x);
        texCoords.push_back(block.getData()->leftFaceTextureMin.y);
        texCoords.push_back(block.getData()->leftFaceTextureMax.x);
        texCoords.push_back(block.getData()->leftFaceTextureMin.y);
        texCoords.push_back(block.getData()->leftFaceTextureMax.x);
        texCoords.push_back(block.getData()->leftFaceTextureMax.y);
        texCoords.push_back(block.getData()->leftFaceTextureMin.x);
        texCoords.push_back(block.getData()->leftFaceTextureMax.y);
    }

    if(face == Face::rightFace) {
        texCoords.push_back(block.getData()->rightFaceTextureMin.x);
        texCoords.push_back(block.getData()->rightFaceTextureMin.y);
        texCoords.push_back(block.getData()->rightFaceTextureMax.x);
        texCoords.push_back(block.getData()->rightFaceTextureMin.y);
        texCoords.push_back(block.getData()->rightFaceTextureMax.x);
        texCoords.push_back(block.getData()->rightFaceTextureMax.y);
        texCoords.push_back(block.getData()->rightFaceTextureMin.x);
        texCoords.push_back(block.getData()->rightFaceTextureMax.y);
    }

    if(face == Face::bottomFace) {
        texCoords.push_back(block.getData()->bottomFaceTextureMin.x);
        texCoords.push_back(block.getData()->bottomFaceTextureMin.y);
        texCoords.push_back(block.getData()->bottomFaceTextureMax.x);
        texCoords.push_back(block.getData()->bottomFaceTextureMin.y);
        texCoords.push_back(block.getData()->bottomFaceTextureMax.x);
        texCoords.push_back(block.getData()->bottomFaceTextureMax.y);
        texCoords.push_back(block.getData()->bottomFaceTextureMin.x);
        texCoords.push_back(block.getData()->bottomFaceTextureMax.y);
    }

    if(face == Face::topFace) {
        texCoords.push_back(block.getData()->topFaceTextureMin.x);
        texCoords.push_back(block.getData()->topFaceTextureMin.y);
        texCoords.push_back(block.getData()->topFaceTextureMax.x);
        texCoords.push_back(block.getData()->topFaceTextureMin.y);
        texCoords.push_back(block.getData()->topFaceTextureMax.x);
        texCoords.push_back(block.getData()->topFaceTextureMax.y);
        texCoords.push_back(block.getData()->topFaceTextureMin.x);
        texCoords.push_back(block.getData()->topFaceTextureMax.y);
    }
}

bool ChunkGenerator::shouldGenerateFace(
        Chunk& chunk,
        const glm::vec3& adjBlockPosition,
        const glm::vec3& adjChunkPosition,
        const std::unordered_map<std::string, Chunk*>& chunkMap
) {
        auto block = chunk.block(adjBlockPosition);

        std::string key =
                std::to_string(static_cast<int>(adjChunkPosition.x)) + " "
                + std::to_string(static_cast<int>(adjChunkPosition.y)) + " "
                + std::to_string(static_cast<int>(adjChunkPosition.z));
        Chunk* adjChunk = nullptr;
        auto it = chunkMap.find(key);

        //if there is no chunk then the only important condition is the adjacent block
        if(it == chunkMap.end()) return block.getData()->blockType == ChunkBlockType::Air;

        else {
            adjChunk = it->second;
            auto adjChunkBlock = adjChunk->block(adjBlockPosition);
            return adjChunkBlock.getData()->blockType == ChunkBlockType::Air
            && block.getData()->blockType == ChunkBlockType::Air;
        }
}

int ChunkGenerator::getNumberOfFaces() {
    return no_faces;
}

void ChunkGenerator::regenerate(std::vector<Chunk>& chunks, std::vector<Chunk*> chunksToRegenerate) {
    no_faces = 0;
    if(chunks.empty()) return;
    dimensions = chunks.begin()->getDimensions();
    ChunkMap chunkMap = generateChunkMap(chunks);
    for(auto& chunk : chunks) {
        if(std::find(chunksToRegenerate.begin(), chunksToRegenerate.end(), &chunk) != chunksToRegenerate.end()) {
            //std::cout << "Regenerating chunk" << std::endl;
            chunk.clearData();
            auto heightMap = createChunkHeightMap(chunk);
            generateChunk(chunk, chunkMap);
            chunk.updateGraphicsData();
        }
    }
}

ChunkMap ChunkGenerator::generateChunkMap(std::vector<Chunk> &chunks) {
    ChunkMap chunkMap;
    for(auto& chunk : chunks) {
        std::string key =
                std::to_string(static_cast<int>(chunk.getPosition().x)) + " "
                + std::to_string(static_cast<int>(chunk.getPosition().y)) + " "
                + std::to_string(static_cast<int>(chunk.getPosition().z));
        chunkMap.insert({key, &chunk});
    }
    return chunkMap;
}


std::array<int, ChunkGenerator::heightMapSize> ChunkGenerator::createChunkHeightMap(Chunk &chunk) {
    std::array<int, ChunkGenerator::heightMapSize> heightMap;
    const auto& blocks = chunk.getBlocks();
    const auto& chunkPosition = chunk.getPosition();
    //generating a height map for same x and z positions
    for(int i = 0; i <= 255; i++) {
        const auto& blockPosition = blocks[i].getPosition();
        heightMap[i] = noiseGenerator.getHeight(blockPosition.x, blockPosition.z, chunkPosition.x, chunkPosition.z);
    }
    return heightMap;
}

void ChunkGenerator::generateSmoothTerrain(Chunk &chunk, const std::array<int, ChunkGenerator::heightMapSize> &heightMap) {
    const auto& chunkPosition = chunk.getPosition();
    //I need to pass this empty vector to edit block
    for(int z = chunkPosition.z; z < chunkPosition.z + chunkSize; z++) {
        for(int x = chunkPosition.x; x < chunkPosition.x + chunkSize; x++) {
            int height = heightMap[z%(chunkSize-1) * chunkSize + x%(chunkSize-1)];
            for(int y = chunkPosition.y; y < chunkPosition.y + chunkSize; y++) {
                if(y > height and y < noiseGenerator.getWaterLevel()) {
                    chunk.placeBlock({x,y,z}, &block_type::WaterBlock);
                    continue;
                }
                else if(y > height) {
                    continue;
                }
                else if(y == height) {
                    chunk.placeBlock({x,y,z}, &block_type::GrassBlock);
                }
                else if(y > height - 4) {
                    chunk.placeBlock({x,y,z}, &block_type::DirtBlock);
                }
                else if(y <= height-4) {
                    chunk.placeBlock({x,y,z}, &block_type::CobblestoneBlock);
                }
            }
        }
    }
}