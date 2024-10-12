#include <string>
#include <glut.h>
#include "character.h"

void drawCircle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    for (int i = 0; i <= 100; i++) {
        float angle = i * (2.0f * 3.14159f / 100);
        glVertex2f(x + radius * cosf(angle), y + radius * sinf(angle));
    }
    glEnd();
}

void drawHead() {
    // Outer head (sphere-like)
    glColor3f(0.3f, 0.3f, 0.3f);  // Dark gray
    drawCircle(30.0f, 75.0f, 5.0f); // Main head

    // Visor
    glColor3f(0.0f, 0.0f, 0.0f);  // Black for the visor band
    glBegin(GL_QUADS);
    glVertex2f(25.0f, 76.0f);
    glVertex2f(35.0f, 76.0f);
    glVertex2f(35.0f, 74.0f);
    glVertex2f(25.0f, 74.0f);
    glEnd();

    // Visor light (glowing eye)
    glColor3f(0.4f, 1.0f, 1.0f);  // Light blue for glowing eye
    drawCircle(33.0f, 75.0f, 1.5f); // Small circle for the light
}

void drawBody() {
    // Central body shape
    glColor3f(0.5f, 0.5f, 0.5f);  // Gray
    glBegin(GL_POLYGON);
    glVertex2f(27.0f, 68.0f);
    glVertex2f(33.0f, 68.0f);
    glVertex2f(32.0f, 55.0f);
    glVertex2f(28.0f, 55.0f);
    glEnd();

    // Shoulder armor (left)
    glColor3f(0.6f, 0.6f, 0.6f);  // Slightly lighter gray
    glBegin(GL_QUADS);
    glVertex2f(26.0f, 67.0f);
    glVertex2f(27.0f, 67.0f);
    glVertex2f(27.0f, 61.0f);
    glVertex2f(26.0f, 61.0f);
    glEnd();

    // Shoulder armor (right)
    glBegin(GL_QUADS);
    glVertex2f(33.0f, 67.0f);
    glVertex2f(34.0f, 67.0f);
    glVertex2f(34.0f, 61.0f);
    glVertex2f(33.0f, 61.0f);
    glEnd();

    // Blue glowing detail on the side
    glColor3f(0.4f, 1.0f, 1.0f);  // Light blue
    drawCircle(27.5f, 62.0f, 1.0f); // Circular blue light on the side
}

void drawLegs() {
    // Main leg (left)
    glColor3f(0.4f, 0.4f, 0.4f);  // Dark gray
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, 55.0f);
    glVertex2f(28.5f, 50.0f);
    glVertex2f(28.0f, 50.0f);
    glEnd();

    // Main leg (right)
    glBegin(GL_POLYGON);
    glVertex2f(31.0f, 55.0f);
    glVertex2f(31.5f, 50.0f);
    glVertex2f(32.0f, 50.0f);
    glEnd();

    // Foot details (left and right)
    glColor3f(0.3f, 0.3f, 0.3f);  // Very dark gray
    glBegin(GL_QUADS);
    // Left foot
    glVertex2f(27.0f, 50.0f);
    glVertex2f(29.0f, 50.0f);
    glVertex2f(29.0f, 49.5f);
    glVertex2f(27.0f, 49.5f);

    // Right foot
    glVertex2f(31.0f, 50.0f);
    glVertex2f(33.0f, 50.0f);
    glVertex2f(33.0f, 49.5f);
    glVertex2f(31.0f, 49.5f);
    glEnd();
}

void drawRobot() {
    drawHead();
    drawBody();
    drawLegs();
}