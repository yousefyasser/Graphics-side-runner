#include <stdlib.h>
#include <glut.h>
#include <cmath>
#include <vector>
#include "../Character/character.h"
#include "../constants.h"
#include "spawnable.h"
#include "../BoundingBox/boundingBox.h"

using namespace std;

void drawSpawnable(spawnable_t spawnable)
{
    if (spawnable.type == OBSTACLE)
    {
        glColor3f(0.0f, 0.0f, 0.0f);
    }
    else if (spawnable.type == COLLECTIBLE)
    {
        glColor3f(1.0f, 1.0f, 0.0f);
    }
    else
    {
        glColor3f(1.0f, 0.0f, 1.0f);
    }

    drawCircle(spawnable.posX, spawnable.posY, 5);
}

void drawSpawnables(vector<spawnable_t>& spawnables)
{
    for (int i = 0; i < spawnables.size(); i++)
    {
        drawSpawnable(spawnables[i]);
        drawBoundingBox(spawnables[i].posX, spawnables[i].posY, spawnables[i].width, spawnables[i].height);
    }
}

void spawn(vector<spawnable_t>& spawnables, spawnable_type_t type)
{
    spawnable_t newSpawnable = {
        type,                                                   // spawnable type
        (float)SCREEN_WIDTH / 2,                                // x position
        30.0f,                                                  // y position
        10.0f,                                                  // width
        10.0f,                                                  // height
        (((float)rand() / RAND_MAX) >= FLYING_SPAWNABLE_PROB)   // is flying?
    };
    newSpawnable.posY = newSpawnable.flying ? 55.0f : 30.0f;
    spawnables.push_back(newSpawnable);
}

void moveSpawnables(vector<spawnable_t>& spawnables, float gameSpeed) 
{
    std::vector<spawnable_t> onScreenSpawnables;

    for (int i = 0; i < spawnables.size(); i++)
    {
        spawnables[i].posX -= gameSpeed;
        if (spawnables[i].posX > 0)
        {
            onScreenSpawnables.push_back(spawnables[i]);
        }
    }

    spawnables = onScreenSpawnables;
}

void performSpawnableAction(spawnable_t spawnable, int* score, int* robotHealth)
{
    switch (spawnable.type)
    {
    case OBSTACLE:
        (*robotHealth)--;
        break;
    case COLLECTIBLE:
        *score += 10;
        break;
    default:
        break;
    }
    
}

void removeSpawnable(vector<spawnable_t>& spawnables, int spawnableToRemoveIndex)
{
    vector<spawnable_t> updatedSpawnables;
    for (int i = 0; i < spawnables.size(); i++) 
    {
        if (i != spawnableToRemoveIndex)
        {
            updatedSpawnables.push_back(spawnables[i]);
        }
    }

    spawnables = updatedSpawnables;
}