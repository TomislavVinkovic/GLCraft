#include "ChunkGenerator.h"

namespace {
    const int seed = RandomSingleton::get().intInRange(424, 325322);
    const int heightSeed = RandomSingleton::get().intInRange(424, 325322);
}
NoiseGenerator ChunkGenerator::biomeGenerator(seed * 2);
NoiseGenerator ChunkGenerator::noiseGenerator(heightSeed);
ChunkGenerator::ChunkGenerator() :
        grassBiome(seed),
        desertBiome(seed),
        forestBiome(seed),
        oceanBiome(seed)
{
    srand(time(NULL));
}

ChunkGenerator::ChunkGenerator(const std::vector<glm::vec3>& chunkPositions, const glm::vec3& dimensions): ChunkGenerator()
{
    this->dimensions = dimensions;
    this->chunkPositions = chunkPositions;
    static bool noiseGen = false;
    if (!noiseGen) {
        noiseGen = true;

        NoiseParameters biomeParmams;
        biomeParmams.octaves = 5;
        biomeParmams.amplitude = 120;
        biomeParmams.smoothness = 1035;
        biomeParmams.heightOffset = 0;
        biomeParmams.roughness = 0.75;

        biomeGenerator.setParameters(biomeParmams);
    }
}

void ChunkGenerator::setDimensions(const glm::vec3 &dimensions) {
    this->dimensions = dimensions;
}

void ChunkGenerator::setPositions(const std::vector<glm::vec3> &chunkPositions) {
    this->chunkPositions = chunkPositions;
}

void ChunkGenerator::addChunks(const std::vector<glm::vec3>& newPositions) {
    //iz nekog razloga se memorija corrupta
    std::vector<Chunk*> newChunks;
    //ova sljedeca linija bi mogala potencijalno bit bug al nema veze
    std::size_t i = chunks.size();
    chunks.resize(chunks.size() + newPositions.size());
    for(const auto& p : newPositions) {
        chunkPositions.push_back(p);
        chunks[i] = Chunk(dimensions, p);
        std::string key =
                std::to_string(static_cast<int>(p.x)) + " "
                + std::to_string(static_cast<int>(p.y)) + " "
                + std::to_string(static_cast<int>(p.z));

        newChunks.push_back(&chunks[i]);
        chunkMap.insert({key, &chunks[i]});
        i++;
    }
    //first generate blocks for all chunks
    for(const auto& c : newChunks) {
        auto heightMap = createChunkHeightMap(*c);
        auto biomeMap = createChunkBiomeMap(*c);
        generateSmoothTerrain(*c, heightMap, biomeMap);
        //terrainGenerator.generateTerrainFor(*c);
    }
}

void ChunkGenerator::generate() {
    chunks = std::vector<Chunk>(chunkPositions.size());
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
    std::vector<std::thread> threads;
    for(auto& chunk : chunks) {
        auto f = [&]() {
            auto heightMap = createChunkHeightMap(chunk);
            auto biomeMap = createChunkBiomeMap(chunk);
            generateSmoothTerrain(chunk, heightMap, biomeMap);
            //terrainGenerator.generateTerrainFor(chunk);
        };
        threads.push_back(std::thread(f));
    }
    for(auto& t : threads) {
        t.join();
    }
    for(auto& chunk : chunks) {
        if(!chunk.getAirStatus()) {
            continue;
        }
    }
    currentChunk = 0;
}

Chunk* ChunkGenerator::generateNextChunk() {
    if(currentChunk >= chunks.size()) {
        return nullptr;
    }
    auto cc = chunks[currentChunk];
    generateChunk(chunks[currentChunk]);
    Chunk* c = &chunks[currentChunk];
    currentChunk++;
    return c;
}

void ChunkGenerator::generateChunk(
        Chunk &chunk
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

    if(shouldGenerateFace(chunk, block, adjBlockPos, adjChunkPosition, chunkMap)) {
        std::vector<GLfloat> texCoords;
        fillTextureCoords(block, texCoords, face);
        chunk.addFace(block, face, position, texCoords);
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
        const ChunkBlock& blockToPlace,
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
        if(it == chunkMap.end()) {
            return block.getData()->blockType == ChunkBlockType::Air
               || (
                       block.getData()->blockType == ChunkBlockType::Water
                       && blockToPlace.getData()->blockType != ChunkBlockType::Water
               );
        }


        else {
            adjChunk = it->second;
            auto adjChunkBlock = adjChunk->block(adjBlockPosition);
            return
                    (adjChunkBlock.getData()->blockType == ChunkBlockType::Air
            && block.getData()->blockType == ChunkBlockType::Air)
            || (
            (
                    (
                            adjChunkBlock.getData()->blockType == ChunkBlockType::Water
                            && blockToPlace.getData()->blockType != ChunkBlockType::Water
                    ) ||
                    adjChunkBlock.getData()->blockType == ChunkBlockType::Air
            )
             && (
                    (
                            block.getData()->blockType == ChunkBlockType::Water
                            && blockToPlace.getData()->blockType != ChunkBlockType::Water
                    ) ||
                     block.getData()->blockType == ChunkBlockType::Air
             )
            );
        }
}

int ChunkGenerator::getNumberOfFaces() {
    return no_faces;
}

void ChunkGenerator::regenerate(std::vector<Chunk*> chunksToRegenerate) {
    no_faces = 0;
    if(chunks.empty()) return;
    dimensions = chunks.begin()->getDimensions();
    ChunkMap chunkMap = generateChunkMap(chunks);
    for(auto& chunk : chunks) {
        if(std::find(chunksToRegenerate.begin(), chunksToRegenerate.end(), &chunk) != chunksToRegenerate.end()) {
            //std::cout << "Regenerating chunk" << std::endl;
            chunk.clearData();
            //trenutno ne generiram novu height mapu
            //TODO: vratiti ovo ako se stvari pokidaju
//            auto heightMap = createChunkHeightMap(chunk);
            generateChunk(chunk);
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

std::array<int, ChunkGenerator::biomeMapSize> ChunkGenerator::createChunkBiomeMap(Chunk &chunk) {
    std::array<int, ChunkGenerator::biomeMapSize> biomeMap;
    auto pos = chunk.getPosition();
    const auto& blocks = chunk.getBlocks();
    for(int i = 0; i < biomeMapSize; i++) {
        const auto& blockPosition = blocks[i].getPosition();
        biomeMap[i] = biomeGenerator.getHeight(blockPosition.x, blockPosition.z, pos.x + 10, pos.z + 10);
    }
    return biomeMap;
}

//TODO: NEKAKO POPRAVITI ZA NEGATIVNE KOORDINATE
void ChunkGenerator::generateSmoothTerrain(
        Chunk &chunk,
        const std::array<int, ChunkGenerator::heightMapSize> &heightMap,
        const std::array<int, biomeMapSize>& biomeMap
) {
    const auto& chunkPosition = chunk.getPosition();
    //I need to pass this empty vector to edit block

    std::vector<glm::vec3> trees;

    for(int z = chunkPosition.z; z < chunkPosition.z + chunkSize; z++) {
        for(int x = chunkPosition.x; x < chunkPosition.x + chunkSize; x++) {
            auto& biome = getBiome(x, z, biomeMap);
            int height = heightMap[z%(chunkSize-1) * chunkSize + x%(chunkSize-1)];
            for(int y = chunkPosition.y; y < chunkPosition.y + chunkSize; y++) {
                //trees
                if(y > height && y >= noiseGenerator.getWaterLevel()) {
                    //air block
                    continue;
                }

                else {
                    if (randomEngine.intInRange(0, biome.getTreeFrequency()) ==
                        5 && y >= height - 6
                        && y > noiseGenerator.getWaterLevel()) {
                        trees.push_back({x, y + 1, z});
                    }
                    if(y > height and y < noiseGenerator.getWaterLevel()) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &block_type::WaterBlock);
                        chunk.setHasWater(true);
                    }
                    else if(y == height && y > noiseGenerator.getWaterLevel()) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &biome.getTopBlock(randomEngine));
                    }
                    else if(y > height - 4 && y < noiseGenerator.getWaterLevel()) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &biome.getUnderWaterBlock(randomEngine));
                    }
                    else if(y > height - 4) {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &block_type::DirtBlock);
                    }
                    else {
                        chunk.setAirStatus(false);
                        chunk.placeBlock({x,y,z}, &block_type::CobblestoneBlock);
                    }
                }
            }
        }
    }

    for(const auto& tree : trees) {
        int x = tree.x;
        int z = tree.z;

        getBiome(x, z, biomeMap).makeTree(randomEngine, chunk, x, tree.y, z);
    }
}

int ChunkGenerator::getCurrentChunk() {
    return currentChunk;
}

const Biome& ChunkGenerator::getBiome(
        int x,
        int z,
        const std::array<int, biomeMapSize>& biomeMap
) const {
    int biomeValue = biomeMap[z%(chunkSize) * chunkSize + x%(chunkSize)];

    if (biomeValue > 160) {
        return oceanBiome;
    }
    else if (biomeValue > 150) {
        return grassBiome;
    }
    else if (biomeValue > 130) {
        return forestBiome;
    }
//    else if (biomeValue > 120) {
//        return m_temperateForest;
//    }
    else if (biomeValue > 110) {
        return forestBiome;
    }
    else if (biomeValue > 80) {
        return grassBiome;
    }
    else {
        return desertBiome;
    }
}