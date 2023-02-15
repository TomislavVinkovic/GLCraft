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

const glm::vec3 &Player::getPosition() const {
    return camera.Position;
}

void Player::setPosition(const glm::vec3 &pos) {
    camera.Position = pos;
}
