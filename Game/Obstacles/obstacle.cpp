#include <stdlib.h>
#include <glut.h>
#include <cmath>
#include <vector>
#include "../Character/character.h"
#include "../constants.h"
#include "obstacle.h"
#include "../BoundingBox/boundingBox.h"

void drawObstacle(obstacle_t obstacle)
{
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(obstacle.posX, obstacle.flying ? 50 : 30, 5);
}

void drawObstacles(std::vector<obstacle_t>& obstacles)
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        drawObstacle(obstacles[i]);
        drawBoundingBoxObstacle(obstacles[i]);
    }
}

void spawnObstacle(std::vector<obstacle_t>& obstacles)
{
    obstacle_t newObstacle;
    newObstacle.posX = (float)SCREEN_WIDTH / 2;
    newObstacle.flying = (((float)rand() / RAND_MAX) >= FLYING_OBSTACLE_PROB);
    obstacles.push_back(newObstacle);
}

void moveObstacles(std::vector<obstacle_t>& obstacles, float gameSpeed) 
{
    std::vector<obstacle_t> onScreenObstacles;

    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i].posX -= gameSpeed;
        if (obstacles[i].posX > 0)
        {
            onScreenObstacles.push_back(obstacles[i]);
        }
    }

    obstacles = onScreenObstacles;
}