#include <iostream>
#include <glut.h>
#include "ground.h"

void drawGroundBlock(float x) {
    // Draw dirt layer (bottom)
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color for dirt
    glVertex2f(x + 0.0f, 0.0f);    // Bottom-left (x-start is smaller to extend area)
    glVertex2f(x + 50.0f, 0.0f);    // Bottom-right (increased x-end)
    glVertex2f(x + 50.0f, 15.0f);   // Top-right (increased height for bigger dirt layer)
    glVertex2f(x + 0.0f, 15.0f);   // Top-left
    glEnd();

    // Draw grass layer (on top of dirt)
    glBegin(GL_QUADS);
    glColor3f(0.13f, 0.55f, 0.13f); // Green color for grass
    glVertex2f(x + 0.0f, 15.0f);   // Bottom-left (above dirt)
    glVertex2f(x + 50.0f, 15.0f);   // Bottom-right
    glVertex2f(x + 50.0f, 22.0f);   // Top-right (higher for bigger grass layer)
    glVertex2f(x + 0.0f, 22.0f);   // Top-left
    glEnd();

    // Add some "blades" or random variation to the grass edge
    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.6f, 0.1f); // Slightly darker green for grass blades
    // Large blades
    glVertex2f(x + 5.0f, 22.0f); glVertex2f(x + 6.0f, 25.0f); glVertex2f(x + 7.0f, 22.0f); 
    glVertex2f(x + 15.0f, 22.0f); glVertex2f(x + 16.0f, 26.5f); glVertex2f(x + 17.0f, 22.0f); 
    glVertex2f(x + 25.0f, 22.0f); glVertex2f(x + 26.0f, 27.2f); glVertex2f(x + 27.0f, 22.0f); 
    glVertex2f(x + 35.0f, 22.0f); glVertex2f(x + 36.0f, 26.0f); glVertex2f(x + 37.0f, 22.0f); 
    glVertex2f(x + 45.0f, 22.0f); glVertex2f(x + 46.0f, 25.3f); glVertex2f(x + 47.0f, 22.0f); 
    glEnd();
}

void drawGround(float speedX) {
    for (int blocks = 0; blocks <= 10; blocks++) {
        float startingPos = blocks * 50 - fmod(speedX, 50);
        drawGroundBlock(startingPos);
    }
}