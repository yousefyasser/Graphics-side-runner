#pragma once

#include <vector>
using namespace std;

enum spawnable_type_t {
    OBSTACLE,
    COLLECTIBLE,
    POWERUP
};

struct spawnable_t {
    enum spawnable_type_t type;
    float posX;
    float posY;
    float width;
    float height;
    bool flying;
};

void spawn(vector<spawnable_t>& spawnables, spawnable_type_t type);
void drawSpawnables(vector<spawnable_t>& spawnables);
void moveSpawnables(vector<spawnable_t>& spawnables, float gameSpeed);
void performSpawnableAction(spawnable_t spawnable, int* score, int* robotHealth);
void removeSpawnable(vector<spawnable_t>& spawnables, int spawnableToRemoveIndex);