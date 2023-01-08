#pragma once

#include "Player.h"
#include "World.h"
///Klasa koja ce drzati sav potreban state potreban za gameplay i render svijeta

struct State {
    State(const Camera& camera);
    World world;
    Player player;
};
