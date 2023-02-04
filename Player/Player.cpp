#include "Player.h"

Player::Player(const Camera &camera) : camera(camera){}

Camera &Player::getCamera() {
    return camera;
}

const Inventory &Player::getInventory() {
    return inventory;
}

void Player::addToInventory(const ChunkBlockData &block) {
    inventory.addBlock(block);
}

void Player::removeFromInventory(const ChunkBlockType& type) {
    inventory.removeBlock(type);
}

const ChunkBlockType& Player::getCurrentBlock() const {
    return inventory.getCurrentBlock();
}

void Player::setSelectedSlot(unsigned int slot) {
    inventory.setSelectedSlot(slot);
}
