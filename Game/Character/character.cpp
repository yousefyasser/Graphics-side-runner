#include <string>
#include <glut.h>
#include "character.h"

bool isJumping = false;
bool isDucking = false;
float characterSpeed = 0.0f;
float characterYPosition = 0.0f;
float jumpSpeed = 0.15f;
float jumpHeight = 15.0f;
float compressionFactor = 1;

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
    drawCircle(30.0f, 47.0f * compressionFactor + characterYPosition, 5.0f * compressionFactor);

    // Visor
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(25.0f, 48.0f * compressionFactor + characterYPosition);
    glVertex2f(35.0f, 48.0f * compressionFactor + characterYPosition);
    glVertex2f(35.0f, 46.0f * compressionFactor + characterYPosition);
    glVertex2f(25.0f, 46.0f * compressionFactor + characterYPosition);
    glEnd();

    // Visor light (glowing eye)
    glColor3f(0.4f, 1.0f, 1.0f);
    drawCircle(33.0f, 47.0f * compressionFactor + characterYPosition, 1.5f * compressionFactor);
}

void drawBody() {
    // Central body shape
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    glVertex2f(27.0f, 40.0f * compressionFactor + characterYPosition);
    glVertex2f(33.0f, 40.0f * compressionFactor + characterYPosition);
    glVertex2f(32.0f, 27.0f * compressionFactor + characterYPosition);
    glVertex2f(28.0f, 27.0f * compressionFactor + characterYPosition);
    glEnd();

    // Shoulder armor (left)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
    glVertex2f(26.0f, 39.0f * compressionFactor + characterYPosition);
    glVertex2f(27.0f, 39.0f * compressionFactor + characterYPosition);
    glVertex2f(27.0f, 33.0f * compressionFactor + characterYPosition);
    glVertex2f(26.0f, 33.0f * compressionFactor + characterYPosition);
    glEnd();

    // Shoulder armor (right)
    glBegin(GL_QUADS);
    glVertex2f(33.0f, 39.0f * compressionFactor + characterYPosition);
    glVertex2f(34.0f, 39.0f * compressionFactor + characterYPosition);
    glVertex2f(34.0f, 33.0f * compressionFactor + characterYPosition);
    glVertex2f(33.0f, 33.0f * compressionFactor + characterYPosition);
    glEnd();

    // Blue glowing detail on the side
    glColor3f(0.4f, 1.0f, 1.0f);
    drawCircle(27.5f, 34.0f * compressionFactor + characterYPosition, 1.0f * compressionFactor);
}

void drawLegs() {
    float swingAngle = sin(characterSpeed * 0.1f) * 5.0f;

    // Adjust leg position if ducking
    float legOffset = isDucking ? -5.0f : 0.0f;

    // Main leg (left)
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, (27.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(28.5f + swingAngle, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(28.0f + swingAngle, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glEnd();

    // Main leg (right)
    glBegin(GL_POLYGON);
    glVertex2f(31.0f, (27.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(31.5f - swingAngle, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(32.0f - swingAngle, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glEnd();

    // Foot details (left and right)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    // Left foot
    glVertex2f(27.0f, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(29.0f, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(29.0f, (21.5f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(27.0f, (21.5f + legOffset) * compressionFactor + characterYPosition);

    // Right foot
    glVertex2f(31.0f, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(33.0f, (22.0f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(33.0f, (21.5f + legOffset) * compressionFactor + characterYPosition);
    glVertex2f(31.0f, (21.5f + legOffset) * compressionFactor + characterYPosition);
    glEnd();
}

void drawRobot(float groundSpeed) {
    characterSpeed = groundSpeed;
    drawHead();
    drawBody();
    drawLegs();
}

void moveRobot() {
    if (isJumping) {
        if (jumpHeight > 0.0f) {
            characterYPosition += jumpSpeed;
            jumpHeight -= 0.04f;
        }
        else {
            characterYPosition -= jumpSpeed;
            if (characterYPosition <= 0.0f) {
                characterYPosition = 0.0f;
                isJumping = false;
            }
        }
    }

    if (!isDucking) {
        compressionFactor = 1.0f;
    }
}

void Key(unsigned char key, int x, int y) {
    if (key == 'w' && !isJumping) {
        isJumping = true;
        jumpHeight = 15.0f;
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
