#include <string>
#include <stdlib.h>
#include <vector>
#include <glut.h>
#include "character.h"
#include "../constants.h"
#include "../BoundingBox/boundingBox.h"
#include "../Spawnable/spawnable.h"

bool isJumping = false;
bool isDucking = false;
float compressionFactor = 1;

robot_t robot = {
    0.0f,        // speed
    25.0f,       // xPos
    22.0f,        // yPos
    10.0f,       // width  
    30.0f,       // height  
    5.0f,        // jumpSpeed
    10.0f,       // jumpHeight
    MAX_HEALTH
};

void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 100; i++) {
        float angle = i * (2.0f * 3.14159f / 100);
        glVertex2f(x + radius * cosf(angle), y + radius * sinf(angle));
    }
    glEnd();
}

void drawHead() {
    glColor3f(0.3f, 0.3f, 0.3f);
    drawCircle(robot.xPos + 5.0f, 27.0f * compressionFactor + robot.yPos, 5.0f * compressionFactor);

    // Visor
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(robot.xPos, 28.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 10.0f, 28.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 10.0f, 26.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos, 26.0f * compressionFactor + robot.yPos);
    glEnd();

    // Visor light (glowing eye)
    glColor3f(0.4f, 1.0f, 1.0f);
    drawCircle(robot.xPos + 8.0f, 27.0f * compressionFactor + robot.yPos, 1.5f * compressionFactor);
}

void drawBody() {
    // Central body shape
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(robot.xPos + 2.0f, 20.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 8.0f, 20.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 8.0f, 7.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 2.0f, 7.0f * compressionFactor + robot.yPos);
    glEnd();

    // Shoulder armor (left)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(robot.xPos + 1.0f, 19.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 2.0f, 19.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 2.0f, 13.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 1.0f, 13.0f * compressionFactor + robot.yPos);
    glEnd();

    // Shoulder armor (right)
    glBegin(GL_QUADS);
    glVertex2f(robot.xPos + 8.0f, 19.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 9.0f, 19.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 9.0f, 13.0f * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 8.0f, 13.0f * compressionFactor + robot.yPos);
    glEnd();

    // Blue glowing detail on the side
    glColor3f(0.4f, 1.0f, 1.0f);
    drawCircle(robot.xPos + 2.5f, 14.0f * compressionFactor + robot.yPos, 1.0f * compressionFactor);
}

void drawLegs() {
    float swingAngle = sin(robot.speed * 0.1f) * 5.0f;

    // Adjust leg position if ducking
    float legOffset = isDucking ? -5.0f : 0.0f;

    // Main leg (left)
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(robot.xPos + 4.0f, (7.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 3.5f + swingAngle, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 3.0f + swingAngle, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glEnd();

    // Main leg (right)
    glBegin(GL_POLYGON);
    glVertex2f(robot.xPos + 6.0f, (7.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 6.5f - swingAngle, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 7.0f - swingAngle, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glEnd();

    // Foot details (left and right)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    // Left foot
    glVertex2f(robot.xPos + 2.0f, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 4.0f, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 4.0f, (1.5f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 2.0f, (1.5f + legOffset) * compressionFactor + robot.yPos);

    // Right foot
    glVertex2f(robot.xPos + 6.0f, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 8.0f, (2.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 8.0f, (1.5f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(robot.xPos + 6.0f, (1.5f + legOffset) * compressionFactor + robot.yPos);
    glEnd();
}

void drawRobot(float groundSpeed) {
    robot.speed = groundSpeed;
    drawHead();
    drawBody();
    drawLegs();
    drawBoundingBox(robot.xPos + robot.width/2.0f, robot.yPos + 17*compressionFactor, robot.width, robot.height * compressionFactor);
}

void moveRobot() {
    if (isJumping) {
        if (robot.jumpHeight > 0.0f) {
            robot.yPos += robot.jumpSpeed;
            robot.jumpHeight -= 1.0f;
        }
        else
            robot.yPos -= robot.jumpSpeed;
        
        if (robot.yPos <= 22.0f) {
            robot.yPos = 22.0f;
            isJumping = false;
        }
    }

    if (!isDucking) {
        compressionFactor = 1.0f;
    }
}

int collideWithSpawnable(std::vector<spawnable_t> &spawnables)
{
    for (int i = 0; i < spawnables.size(); i++)
    {
        bool collided = hasCollided(
            robot.xPos + robot.width / 2.0f, robot.yPos + 17*compressionFactor, robot.width, robot.height * compressionFactor,
            spawnables[i].posX, spawnables[i].posY, spawnables[i].width, spawnables[i].height
        );

        if (collided)
        {
            return i;
        }
    }

    return -1;
}

void Key(unsigned char key, int x, int y) {
    if (key == 'w' && !isJumping) {
        isJumping = true;
        robot.jumpHeight = 15.0f;
    }
    else if (key == 's') {
        compressionFactor = 0.75f;
        isDucking = true;
    }

    glutPostRedisplay();
}

void KeyUp(unsigned char key, int x, int y) {
    isDucking = false;
    glutPostRedisplay();
}
