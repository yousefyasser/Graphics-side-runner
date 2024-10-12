#include <glut.h>
#include "constants.h"

void Display() {

	glClearColor(0, 0, 0, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	glFlush();
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(SCREEN_X, SCREEN_Y);

	glutCreateWindow("Side Runner");
	glutDisplayFunc(Display);
	glPointSize(25);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 500, 0.0, 250);

	glutMainLoop();
}
