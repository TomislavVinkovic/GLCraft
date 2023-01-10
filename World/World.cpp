#include "World.h"

const std::vector<Chunk> &World::getChunks() const {
    return chunks;
}

void World::generate() {
    //std::cout << "Started world generation" << std::endl;
    glm::vec3 defaultDimensions = glm::vec3(16,16,16);
    float positionZ = 0.f;
    float positionX = 0.f;

    std::vector<glm::vec3> chunkPositions;

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            chunkPositions.push_back({positionX, 0, positionZ});
            positionX += 16;
        }
        positionZ += 16;
        positionX = 0;
    }

    ChunkGenerator generator{chunkPositions};
    chunks = generator.generate();
    for(auto& chunk : chunks) {
        chunk.generateGraphicsData();
    }
    for(const auto& block : chunks[1].getBlocks()) {
        continue;
    }
//    editBlock({0,0,0}, block_type::AirBlock);
//    chunks[0].updateGraphicsData();
}

void World::deleteData() {
    for(auto& chunk : chunks) {
        chunk.deleteGraphicsData();
    }
}


void World::castRay(const Camera &camera, int button) {
    Ray ray(camera.Position, camera.Front);
    for(ray; ray.getLength() < 6; ray.step(0.05f, camera)) {
        auto block = getBlock(ray.getEnd());
        if(block.getData().blockType != ChunkBlockType::Air) {
            //std::cout << "Breaking block" << std::endl;
            if(button == GLFW_MOUSE_BUTTON_LEFT) {
                editBlock(ray.getEnd(), block_type::AirBlock);
                break; //break only the first block
            }
            else if(button == GLFW_MOUSE_BUTTON_RIGHT) {
                //place a block, not sure how to do that right now
                //editBlock()
            }
        }
    }
}

World::~World() {
    deleteData();
}

const Chunk* World::getChunk(const glm::vec3 &searchPosition) const {
    //promisliti o offsetima kod dohvacanja blokovaaw
    int x = searchPosition.x;
    int z = searchPosition.z;

    //std::cout << x << " " << z << std::endl;

    int idx_x = x % 10;
    int idx_z = z % 10;

    //najgluplji nacin za ovo, ali trebao bi raditi
    for(const auto& chunk : chunks) {
        const auto& position = chunk.getPosition();
        const auto& dimensions = chunk.getDimensions();
        bool containedInX = searchPosition.x >= position.x && searchPosition.x < position.x + dimensions.x;
        bool containedInY = searchPosition.y >= position.y && searchPosition.y < position.y + dimensions.y;
        bool containedInZ = searchPosition.z >= position.z && searchPosition.z < position.z + dimensions.z;

        if(containedInX && containedInY && containedInZ) return &chunk;
    }
    return nullptr;


//    if(idx_z * 10 + idx_x > chunks.size()-1 || idx_z * 10 + idx_x < 0){
//        std::cout << "Out of bounds" << " " << (idx_z * 10 + idx_x ) << std::endl;
//        return nullptr;
//    }
//
//    return &chunks[idx_z * 10 + idx_x];
}

ChunkBlock World::getBlock(const glm::vec3 &position) const {
    const Chunk* chunk = getChunk(position);
    if(chunk == nullptr) return ChunkBlock(position, block_type::AirBlock);
    auto block = chunk->block({
          static_cast<int>(position.x),
          static_cast<int>(position.y),
          static_cast<int>(position.z),
    }, true);
    return block;
}



void World::editBlock(const glm::vec3 &position, const ChunkBlockData& blockData) {
    Chunk* chunk = getChunkWorld(position);
    std::vector<glm::vec3> surroundingChunkPositions{};
    if(chunk != nullptr) {
        //dobijem dobar chunk
        chunk->editBlock({
         static_cast<int>(position.x),
         static_cast<int>(position.y),
         static_cast<int>(position.z),
        }, blockData, surroundingChunkPositions);
        //std::cout << "Breaking block at " << position.x << " " << position.y << " " << position.z << std::endl;
        std::vector<Chunk*> chunksToRegenerate;
        chunksToRegenerate.push_back(chunk);

        ChunkGenerator generator;
        generator.regenerate(chunks, chunksToRegenerate);
    }

}
Chunk* World::getChunkWorld(const glm::vec3& searchPosition) {
//    int x = position.x;
//    int z = position.z;
//
//    //std::cout << x << " " << z << std::endl;
//
//    int idx_x = x % 10;
//    int idx_z = z % 10;
//
//    //std::cout << idx_x << " " << idx_z << std::endl;
//
//    if(idx_z * 10 + idx_x > chunks.size()-1 || idx_z * 10 + idx_x < 0){
//        std::cout << "Out of bounds" << " " << (idx_z * 10 + idx_x ) << std::endl;
//        return nullptr;
//    }
//
//    return &chunks[idx_z * 10 + idx_x];

    //najgluplji nacin za ovo, ali trebao bi raditi
    for(auto& chunk : chunks) {
        const auto& position = chunk.getPosition();
        const auto& dimensions = chunk.getDimensions();
        bool containedInX = searchPosition.x >= position.x && searchPosition.x < position.x + dimensions.x;
        bool containedInY = searchPosition.y >= position.y && searchPosition.y < position.y + dimensions.y;
        bool containedInZ = searchPosition.z >= position.z && searchPosition.z < position.z + dimensions.z;

        if(containedInX && containedInY && containedInZ) {
            return &chunk;
        }
    }
    return nullptr;
}
