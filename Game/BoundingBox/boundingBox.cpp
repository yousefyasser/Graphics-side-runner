#include <stdlib.h>
#include <glut.h>
#include "../Obstacles/obstacle.h"

void drawBoundingBoxObstacle(obstacle_t obstacle)
{
    float posY = obstacle.flying ? 50 : 30;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(obstacle.posX - 5, posY - 5);
    glVertex2f(obstacle.posX - 5, posY + 5);
    glVertex2f(obstacle.posX + 5, posY + 5);
    glVertex2f(obstacle.posX + 5, posY - 5);
    glVertex2f(obstacle.posX - 5, posY - 5);
    glEnd();
}

void drawBoundingBoxRobot(obstacle_t obstacle)
{
    float posY = obstacle.flying ? 50 : 30;

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(obstacle.posX - 5, posY - 5);
    glVertex2f(obstacle.posX - 5, posY + 5);
    glVertex2f(obstacle.posX + 5, posY + 5);
    glVertex2f(obstacle.posX + 5, posY - 5);
    glVertex2f(obstacle.posX - 5, posY - 5);
    glEnd();
}