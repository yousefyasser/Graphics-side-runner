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
    drawCircle(30.0f, 47.0f, 5.0f); // Adjust head to start higher (previously at 75.0)

    // Visor
    glColor3f(0.0f, 0.0f, 0.0f);  // Black for the visor band
    glBegin(GL_QUADS);
    glVertex2f(25.0f, 48.0f);
    glVertex2f(35.0f, 48.0f);
    glVertex2f(35.0f, 46.0f);
    glVertex2f(25.0f, 46.0f);
    glEnd();

    // Visor light (glowing eye)
    glColor3f(0.4f, 1.0f, 1.0f);  // Light blue for glowing eye
    drawCircle(33.0f, 47.0f, 1.5f); // Small circle for the light
}

void drawBody() {
    // Central body shape
    glColor3f(0.5f, 0.5f, 0.5f);  // Gray
    glBegin(GL_POLYGON);
    glVertex2f(27.0f, 40.0f);  // Lower body position (previously at 68.0)
    glVertex2f(33.0f, 40.0f);
    glVertex2f(32.0f, 27.0f);  // Lower
    glVertex2f(28.0f, 27.0f);
    glEnd();

    // Shoulder armor (left)
    glColor3f(0.6f, 0.6f, 0.6f);  // Slightly lighter gray
    glBegin(GL_QUADS);
    glVertex2f(26.0f, 39.0f);
    glVertex2f(27.0f, 39.0f);
    glVertex2f(27.0f, 33.0f);
    glVertex2f(26.0f, 33.0f);
    glEnd();

    // Shoulder armor (right)
    glBegin(GL_QUADS);
    glVertex2f(33.0f, 39.0f);
    glVertex2f(34.0f, 39.0f);
    glVertex2f(34.0f, 33.0f);
    glVertex2f(33.0f, 33.0f);
    glEnd();

    // Blue glowing detail on the side
    glColor3f(0.4f, 1.0f, 1.0f);  // Light blue
    drawCircle(27.5f, 34.0f, 1.0f); // Circular blue light on the side
}

void drawLegs() {
    // Main leg (left)
    glColor3f(0.4f, 0.4f, 0.4f);  // Dark gray
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, 27.0f);  // Adjusted to start at y = 22
    glVertex2f(28.5f, 22.0f);
    glVertex2f(28.0f, 22.0f);
    glEnd();

    // Main leg (right)
    glBegin(GL_POLYGON);
    glVertex2f(31.0f, 27.0f);  // Adjusted to start at y = 22
    glVertex2f(31.5f, 22.0f);
    glVertex2f(32.0f, 22.0f);
    glEnd();

    // Foot details (left and right)
    glColor3f(0.3f, 0.3f, 0.3f);  // Very dark gray
    glBegin(GL_QUADS);
    // Left foot
    glVertex2f(27.0f, 22.0f);  // Aligned with y = 22 (ground level)
    glVertex2f(29.0f, 22.0f);
    glVertex2f(29.0f, 21.5f);
    glVertex2f(27.0f, 21.5f);

    // Right foot
    glVertex2f(31.0f, 22.0f);
    glVertex2f(33.0f, 22.0f);
    glVertex2f(33.0f, 21.5f);
    glVertex2f(31.0f, 21.5f);
    glEnd();
}

void drawRobot() {
    drawHead();
    drawBody();
    drawLegs();
}
