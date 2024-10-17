#include <glut.h>

void drawBoundingBox(float x, float y, float width, float height)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x - width/2, y - height/2);
    glVertex2f(x - width/2, y + height/2);
    glVertex2f(x + width/2, y + height/2);
    glVertex2f(x + width/2, y - height/2);
    glVertex2f(x - width/2, y - height/2);
    glEnd();
}

bool hasCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {
    float halfWidth1 = width1 / 2.0;
    float halfHeight1 = height1 / 2.0;
    float halfWidth2 = width2 / 2.0;
    float halfHeight2 = height2 / 2.0;

    // Check if the rectangles do not overlap
    if (x1 + halfWidth1 < x2 - halfWidth2 || x2 + halfWidth2 < x1 - halfWidth1) {
        return false;  // No overlap horizontally
    }
    if (y1 + halfHeight1 < y2 - halfHeight2 || y2 + halfHeight2 < y1 - halfHeight1) {
        return false;  // No overlap vertically
    }
    return true;
}