#pragma once
#include <vector>

struct obstacle_t {
    float posX;
    bool flying;
};

void spawnObstacle(std::vector<obstacle_t>& obstacles);
void drawObstacles(std::vector<obstacle_t>& obstacles);
void moveObstacles(std::vector<obstacle_t>& obstacles, float gameSpeed);