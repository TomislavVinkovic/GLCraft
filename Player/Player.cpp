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

void Player::removeFromInventory(const std::string &name) {
    inventory.removeBlock(name);
}
