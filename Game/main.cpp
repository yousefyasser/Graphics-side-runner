#include <stdlib.h>
#include <glut.h>
#include "constants.h"
#include "Character/character.h"
#include "Ground/ground.h"

float groundSpeed = 0;
float gameSpeed = 0;
float maxGameSpeed = 0.02f;

void Display() {

	glClearColor(1, 1, 1, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawRobot();
	drawGround(groundSpeed);
	
	glFlush();
}

void Anim() {
	groundSpeed += gameSpeed;
	gameSpeed += 0.00005f;

	if (gameSpeed > maxGameSpeed) {
		gameSpeed = maxGameSpeed;
	}

	if (groundSpeed >= 500) {
		groundSpeed = 0;
	}

	glutPostRedisplay(); // Redraw the scene
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(SCREEN_X, SCREEN_Y);

	glutCreateWindow("Side Runner");
	glutDisplayFunc(Display);
	glutIdleFunc(Anim);

	glPointSize(25);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);

	gluOrtho2D(0.0, 500, 0.0, 250);

	glutMainLoop();
}
