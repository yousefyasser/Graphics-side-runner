#include <cmath>
#include <glut.h>
#include <sstream>
#include "../constants.h";

void drawHealthBar(int robotHealth) {
    float barWidth = 20.0f;
    float barHeight = 10.0f;
    float padding = 1.0f;

    float startX = SCREEN_WIDTH/2 - (MAX_HEALTH * (barWidth + padding)) - 20; 
    float startY = SCREEN_HEIGHT/2 - barHeight - 120; 

    for (int i = 0; i < MAX_HEALTH; i++) {
        if (i < robotHealth) {
            glColor3f(0.0f, 1.0f, 0.0f);
        }
        else {
            glColor3f(1.0f, 0.0f, 0.0f); 
        }

        glBegin(GL_QUADS);
        glVertex2f(startX + i * (barWidth + padding), startY);
        glVertex2f(startX + i * (barWidth + padding) + barWidth, startY); 
        glVertex2f(startX + i * (barWidth + padding) + barWidth, startY + barHeight);
        glVertex2f(startX + i * (barWidth + padding), startY + barHeight);  
        glEnd();
    }
}

void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);  // Position to start drawing
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);  // Render each character
    }
}

void drawScore(int score) {
    float textPosX = 10;
    float textPosY = SCREEN_HEIGHT / 2 - 125;

    std::ostringstream scoreStream;
    scoreStream << "Score: " << score;

    glColor3f(0.0f, 0.0f, 0.0f);

    renderBitmapString(textPosX, textPosY, GLUT_BITMAP_HELVETICA_18, scoreStream.str().c_str());
}

void drawRemainingTime(int remTime) {
    float textPosX = SCREEN_WIDTH/4 - 50;
    float textPosY = SCREEN_HEIGHT / 2 - 125;

    std::ostringstream timeStream;
    timeStream << "Time Left: " << remTime << " s";

    glColor3f(0.0f, 0.0f, 0.0f);

    renderBitmapString(textPosX, textPosY, GLUT_BITMAP_HELVETICA_18, timeStream.str().c_str());
}

void drawInfo(int robotHealth, int score, int remTime) {
	drawHealthBar(robotHealth);
	drawScore(score);
	drawRemainingTime(remTime);
}