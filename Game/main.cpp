#include <stdlib.h>
#include <vector>
#include <glut.h>
#include "constants.h"
#include "Character/character.h"
#include "Ground/ground.h"
#include "OnScreenInfo/onScreenInfo.h"
#include "Obstacles/obstacle.h"

float groundSpeed = 0.1f;
float gameSpeed = 0.2f;
float maxGameSpeed = 10.0f;

int score = 0;
float remainingSeconds = GAME_TIME;

std::vector<obstacle_t> obstacles;
float spawnInterval = OBSTACLE_SPAWN_RATE;

void Display() {

	glClearColor(0, 1, 1, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawRobot(groundSpeed);
	drawGround(groundSpeed);
	drawInfo(robot.health, score, remainingSeconds);
	drawObstacles(obstacles);

	glFlush();
}

void Anim(int v) {
	static float obstacleSpawnTimer = 0.0f;
	float frameTime = 1.0f / FPS;

	remainingSeconds -= frameTime;

	if (gameSpeed > maxGameSpeed) {
		gameSpeed = maxGameSpeed;
	}
	else {
		gameSpeed += 0.005f;
	}

	if (groundSpeed >= 500) {
		groundSpeed = 0;
	}
	else {
		groundSpeed += gameSpeed;
	}

	obstacleSpawnTimer += frameTime;
	if (obstacleSpawnTimer >= spawnInterval) {
		spawnObstacle(obstacles);
		obstacleSpawnTimer = 0.0f;

		if (spawnInterval > 0.5) {
			spawnInterval -= 0.1f;
		}
	}

	moveRobot();
	moveObstacles(obstacles, gameSpeed);

	glutPostRedisplay();
	glutTimerFunc(16, Anim, 0);
}

void main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(SCREEN_X, SCREEN_Y);

	glutCreateWindow("Side Runner");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Key);
	glutKeyboardUpFunc(KeyUp);
	glutTimerFunc(0, Anim, 0);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);

	gluOrtho2D(0.0, 500, 0.0, 250);

	glutMainLoop();
}
