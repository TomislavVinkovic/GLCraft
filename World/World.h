#pragma once


#include "ChunkBlockType.h"
#include "ChunkBlockData.h"
#include "Chunk.h"
#include "ChunkGenerator.h"


#include "Camera.h"
#include "Ray.h"
#include "Player.h"

#include <algorithm>
#include <array>

#include "glm.hpp"

///Klasa World odgovorna za generiranje chunkova preko ChunkGeneratora
///i jos brojne druge stvari vezane za game world

class World {
    private:
        Player* player;
        std::vector<Chunk> chunks;
        Chunk* getChunkWorld(const glm::vec3& position);
    public:
        World(Player* player);
        World() = default;
        ~World();
        const std::vector<Chunk>& getChunks() const;
        void generate();
        //void regenerate();
        void deleteData();

        const Chunk* getChunk(const glm::vec3& position) const;
        ChunkBlock getBlock(const glm::vec3& position) const;
        void castRay(const Camera& camera, int button);

        //block editing
        void editBlock(const glm::vec3& position, const ChunkBlockData& blockData);

        //setters
        void setPlayer(Player* player);
};
