#include "World.h"

World::World(Player *player) {
    this->player = player;
}

const std::vector<Chunk> &World::getChunks() const {
    return chunks;
}

void World::generate() {
    glm::vec3 defaultDimensions = glm::vec3(16,16,16);
    float positionZ = 0.f;
    float positionX = 0.f;
    float positionY = 160.f;

    std::vector<glm::vec3> chunkPositions;

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 15; j++) {
            for(int k = 0; k <= 15; k++) {
                chunkPositions.push_back({positionX, positionY, positionZ});
                positionX += 16;
            }
            positionX = 0;
            positionZ += 16;
        }
        positionX = 0;
        positionZ = 0;
        positionY -= 16;
    }


    ChunkGenerator generator{chunkPositions};
    chunks = generator.generate();


    for(auto& chunk : chunks) {
        chunk.generateGraphicsData();
    }
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
        auto blockData = block.getData();
        if(blockData->blockType != ChunkBlockType::Air) {
            //break the loop, but not the block
            if(blockData->breakable == false) {
                break;
            }

            if(button == GLFW_MOUSE_BUTTON_LEFT) {
                player->addToInventory(*blockData);
                editBlock(ray.getEnd(), block_type::AirBlock);
                break; //break only the first block
            }

            else if(button == GLFW_MOUSE_BUTTON_RIGHT) {
                auto currentBlock = player->getCurrentBlock();

                if(currentBlock != ChunkBlockType::Air) {
                    glm::vec3 placeDest;
                    const auto& rayEnd = ray.getEnd();

                    float epsX1 = rayEnd.x - floor(rayEnd.x);
                    float epsY1 = rayEnd.y - floor(rayEnd.y);
                    float epsZ1 = rayEnd.z - floor(rayEnd.z);

                    float epsX2 = ceil(rayEnd.x) - rayEnd.x;
                    float epsY2 = ceil(rayEnd.y) - rayEnd.y;
                    float epsZ2 = ceil(rayEnd.z) - rayEnd.z;


                    float epsMin1 = std::min(epsX1, std::min(epsY1, epsZ1));
                    float epsMin2 = std::min(epsX2, std::min(epsY2, epsZ2));
                    float epsMin = std::min(epsMin1, epsMin2);

                    if(epsMin == epsX1) {
                        placeDest = {
                                rayEnd.x - 1, rayEnd.y, rayEnd.z
                        };
                    }
                    else if(epsMin == epsZ1) {
                        placeDest = {
                                rayEnd.x, rayEnd.y, rayEnd.z - 1
                        };
                    }
                    else if(epsMin == epsY1){
                        placeDest = {
                                rayEnd.x, rayEnd.y-1, rayEnd.z
                        };
                    }

                    else if(epsMin == epsX2) {
                        placeDest = {
                                rayEnd.x + 1, rayEnd.y, rayEnd.z
                        };
                    }
                    else if(epsMin == epsZ2) {
                        placeDest = {
                                rayEnd.x, rayEnd.y, rayEnd.z + 1
                        };
                    }
                    else {
                        placeDest = {
                                rayEnd.x, rayEnd.y + 1, rayEnd.z
                        };
                    }
                    editBlock(placeDest, block_type::getBlockDataByType(currentBlock));
                    player->removeFromInventory(currentBlock);
                }
                break;
            }
        }
    }
}

World::~World() {
    deleteData();
}

const Chunk* World::getChunk(const glm::vec3 &searchPosition) const {

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
}

ChunkBlock World::getBlock(const glm::vec3 &position) const {
    const Chunk* chunk = getChunk(position);
    if(chunk == nullptr) return ChunkBlock(position, &block_type::AirBlock);
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
        chunk->editBlock({
         static_cast<int>(position.x),
         static_cast<int>(position.y),
         static_cast<int>(position.z),
        }, &blockData, surroundingChunkPositions);
        //std::cout << "Breaking block at " << position.x << " " << position.y << " " << position.z << std::endl;
        std::vector<Chunk*> chunksToRegenerate;
        chunksToRegenerate.push_back(chunk);
        for(const auto& pos : surroundingChunkPositions) {
            chunksToRegenerate.push_back(getChunkWorld(pos));
        }
        ChunkGenerator generator;
        generator.regenerate(chunks, chunksToRegenerate);
    }

}
Chunk* World::getChunkWorld(const glm::vec3& searchPosition) {
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

void World::setPlayer(Player *player) {
    if(player != nullptr) {
        this->player = player;
    }
}
