#include "State.h"

State::State(const Camera &camera) : player(camera) {
    world.setPlayer(&player);
}
