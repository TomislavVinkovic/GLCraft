#pragma once

#include "Camera.h"
#include "Inventory.h"
#include "Ray.h"

//the idea is to at some point implement colision detection

class Player {
    private:
        Camera camera;
        Inventory inventory;

    public:
        explicit Player(const Camera& camera);
        Camera& getCamera();
        const Inventory& getInventory();
        void addToInventory(const ChunkBlockData& block);
        //TODO: Maybe I will need to change this function definition
        void removeFromInventory(const ChunkBlockType& type);
        void setSelectedSlot(unsigned int slot);
        const ChunkBlockData* getCurrentBlock();
};
