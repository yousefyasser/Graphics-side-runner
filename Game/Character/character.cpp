#include <string>
#include <glut.h>
#include "character.h"
#include "../constants.h"

bool isJumping = false;
bool isDucking = false;
float compressionFactor = 1;

robot_t robot = {
    0.0f,        // speed
    0.0f,        // xPos
    0.0f,        // yPos
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
    drawCircle(30.0f, 47.0f * compressionFactor + robot.yPos, 5.0f * compressionFactor);

    // Visor
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(25.0f, 48.0f * compressionFactor + robot.yPos);
    glVertex2f(35.0f, 48.0f * compressionFactor + robot.yPos);
    glVertex2f(35.0f, 46.0f * compressionFactor + robot.yPos);
    glVertex2f(25.0f, 46.0f * compressionFactor + robot.yPos);
    glEnd();

    // Visor light (glowing eye)
    glColor3f(0.4f, 1.0f, 1.0f);
    drawCircle(33.0f, 47.0f * compressionFactor + robot.yPos, 1.5f * compressionFactor);
}

void drawBody() {
    // Central body shape
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(27.0f, 40.0f * compressionFactor + robot.yPos);
    glVertex2f(33.0f, 40.0f * compressionFactor + robot.yPos);
    glVertex2f(32.0f, 27.0f * compressionFactor + robot.yPos);
    glVertex2f(28.0f, 27.0f * compressionFactor + robot.yPos);
    glEnd();

    // Shoulder armor (left)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(26.0f, 39.0f * compressionFactor + robot.yPos);
    glVertex2f(27.0f, 39.0f * compressionFactor + robot.yPos);
    glVertex2f(27.0f, 33.0f * compressionFactor + robot.yPos);
    glVertex2f(26.0f, 33.0f * compressionFactor + robot.yPos);
    glEnd();

    // Shoulder armor (right)
    glBegin(GL_QUADS);
    glVertex2f(33.0f, 39.0f * compressionFactor + robot.yPos);
    glVertex2f(34.0f, 39.0f * compressionFactor + robot.yPos);
    glVertex2f(34.0f, 33.0f * compressionFactor + robot.yPos);
    glVertex2f(33.0f, 33.0f * compressionFactor + robot.yPos);
    glEnd();

    // Blue glowing detail on the side
    glColor3f(0.4f, 1.0f, 1.0f);
    drawCircle(27.5f, 34.0f * compressionFactor + robot.yPos, 1.0f * compressionFactor);
}

void drawLegs() {
    float swingAngle = sin(robot.speed * 0.1f) * 5.0f;

    // Adjust leg position if ducking
    float legOffset = isDucking ? -5.0f : 0.0f;

    // Main leg (left)
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, (27.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(28.5f + swingAngle, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(28.0f + swingAngle, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glEnd();

    // Main leg (right)
    glBegin(GL_POLYGON);
    glVertex2f(31.0f, (27.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(31.5f - swingAngle, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(32.0f - swingAngle, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glEnd();

    // Foot details (left and right)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    // Left foot
    glVertex2f(27.0f, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(29.0f, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(29.0f, (21.5f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(27.0f, (21.5f + legOffset) * compressionFactor + robot.yPos);

    // Right foot
    glVertex2f(31.0f, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(33.0f, (22.0f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(33.0f, (21.5f + legOffset) * compressionFactor + robot.yPos);
    glVertex2f(31.0f, (21.5f + legOffset) * compressionFactor + robot.yPos);
    glEnd();
}

void drawRobot(float groundSpeed) {
    robot.speed = groundSpeed;
    drawHead();
    drawBody();
    drawLegs();
}

void moveRobot() {
    if (isJumping) {
        if (robot.jumpHeight > 0.0f) {
            robot.yPos += robot.jumpSpeed;
            robot.jumpHeight -= 1.0f;
        }
        else
            robot.yPos -= robot.jumpSpeed;
        
        if (robot.yPos <= 0.0f) {
            robot.yPos = 0.0f;
            isJumping = false;
        }
    }

    if (!isDucking) {
        compressionFactor = 1.0f;
    }
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
