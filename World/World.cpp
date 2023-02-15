#include "World.h"

World::World(Player *player) {
    this->player = player;
}

const std::vector<Chunk*> &World::getChunks() const {
    return chunks;
}

void World::generate() {
    glm::vec3 defaultDimensions = glm::vec3(16,16,16);
    float positionZ = 0.f;
    float positionX = 0.f;
    float positionY = 160.f;

//    for(int i = 0; i < 20; i++) {
//        for(int j = 0; j < 20; j++) {
//            for(int k = 0; k <= 20; k++) {
//                chunkPositions.push_back({positionX, positionY, positionZ});
//                positionX += 16;
//            }
//            positionX = 0;
//            positionZ += 16;
//        }
//        positionX = 0;
//        positionZ = 0;
//        positionY -= 16;
//    }

    //the first of chunk positions being relative to the player
    //no infinite world yet :D
    updatePositions();




    //generate chunks with their heightmaps
    //then later in the rendering pipeline, chunks will be rendered one by one, reducing load times
    generator.setPositions(chunkPositions);
    generator.setDimensions(defaultDimensions);

    generator.generate();
}

//ne radi apsolutno nista kod ovoga, osim inicijalnog generiranja svijeta
void World::updatePositions() {
    const auto& playerPos = player->getPosition();
    glm::vec3 playerChunk = {
            (static_cast<int>(floor(playerPos.x))/16)*16 - 16,
            (static_cast<int>(floor(playerPos.y))/16)*16 - 16,
            (static_cast<int>(floor(playerPos.z))/16)*16 - 16,
    };
    //do not update if the player has not moved
    if(playerChunk == playerChunkPosition) return;
    auto prevChunkPosition = playerChunkPosition;
    playerChunkPosition = playerChunk;

    if(firstGeneration) {

        float positionZ = playerChunk.z;
        float positionX = playerChunk.x;
        float positionY = playerChunk.y - 16;

        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 30; j++) {
                for(int k = 0; k < 30; k++) {
                    chunkPositions.push_back({positionX, positionY, positionZ});
                    if(positionX > largestX) largestX = positionX;
                    positionX += 16;
                }
                positionX = 0;
                if(positionZ > largestZ) largestZ = positionX;
                positionZ += 16;
            }
            positionX = 0;
            positionZ = 0;
            positionY -= 16;
        }

        float pcx2 = pow(playerChunk.x, 2);
        float pcy2 = pow(playerChunk.y, 2);
        float pcz2 = pow(playerChunk.z, 2);

        std::sort(chunkPositions.begin(), chunkPositions.end(), [&](auto& a, auto& b) {
            return ((pow(a.x, 2) - pcx2) + (pow(a.y, 2) - pcy2) + (pow(a.z, 2) - pcz2))
                < ((pow(b.x, 2) - pcx2) + (pow(b.y, 2) - pcy2) + (pow(b.z, 2) - pcz2));
        });
        player->setPosition({playerPos.x, playerPos.y-16, playerPos.z});
        firstGeneration = false;
    }

    //generate a row on the z direction
//    else if(!firstGeneration && playerChunkPosition.z > prevChunkPosition.z) {
//        float positionZ = largestZ;
//        float positionX = playerChunk.x;
//        float positionY = playerChunk.y - 16;
//
//        int i = 0;
//        for(int x = positionX; x < 10; x++) {
//            chunkPositions.push_back({x + i*16, positionY, largestZ + 1});
//            generator.addChunk({x + i*16, positionY, largestZ + 1});
//            i++;
//        }
//        largestZ++;
//    }
//
//    else if(!firstGeneration && playerChunkPosition.x > prevChunkPosition.x) {
//        float positionZ = playerChunk.z;
//        float positionX = largestX;
//        float positionY = playerChunk.y - 16;
//
//        int i = 0;
//        for(int z = positionZ; z < 10; z++) {
//            chunkPositions.push_back({largestX + 1, positionY, z + i*16});
//            generator.addChunk({largestX + 1, positionY, z + i*16});
//            i++;
//        }
//        largestX++;
//    }
}

Chunk* World::generateNext() {
    Chunk* c = generator.generateNextChunk();
    if(c != nullptr) {
        c->generateGraphicsData();
        chunks.push_back(c);
    }

    return c;
}

void World::deleteData() {
    for(auto& chunk : chunks) {
        chunk->deleteGraphicsData();
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
        const auto& position = chunk->getPosition();
        const auto& dimensions = chunk->getDimensions();
        bool containedInX = searchPosition.x >= position.x && searchPosition.x < position.x + dimensions.x;
        bool containedInY = searchPosition.y >= position.y && searchPosition.y < position.y + dimensions.y;
        bool containedInZ = searchPosition.z >= position.z && searchPosition.z < position.z + dimensions.z;

        if(containedInX && containedInY && containedInZ) return chunk;
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
        generator.regenerate(chunksToRegenerate);
    }

}
Chunk* World::getChunkWorld(const glm::vec3& searchPosition) {
    //najgluplji nacin za ovo, ali trebao bi raditi
    for(auto& chunk : chunks) {
        const auto& position = chunk->getPosition();
        const auto& dimensions = chunk->getDimensions();
        bool containedInX = searchPosition.x >= position.x && searchPosition.x < position.x + dimensions.x;
        bool containedInY = searchPosition.y >= position.y && searchPosition.y < position.y + dimensions.y;
        bool containedInZ = searchPosition.z >= position.z && searchPosition.z < position.z + dimensions.z;

        if(containedInX && containedInY && containedInZ) {
            return chunk;
        }
    }
    return nullptr;
}

void World::setPlayer(Player *player) {
    if(player != nullptr) {
        this->player = player;
    }
}

void World::sortChunksByDistanceToCamera(const Camera &camera) {
    auto p = camera.Position;

    //sowrt the chunks by distance to the camera
    std::sort(chunks.begin(), chunks.end(), [&](Chunk*& a, Chunk*& b){
        return (
            pow(a->getPosition().x - p.x, 2)
            + pow(a->getPosition().y - p.y, 2)
            + pow(a->getPosition().z - p.z, 2)
        ) > (
                pow(b->getPosition().x - p.x, 2)
                + pow(b->getPosition().y - p.y, 2)
                + pow(b->getPosition().z - p.z, 2)
        );
    });
}
