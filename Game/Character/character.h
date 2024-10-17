#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include "../Spawnable/spawnable.h"

struct robot_t {
	float speed;
	float xPos;
	float yPos;
	float width;
	float height;
	float jumpSpeed;
	float jumpHeight;
	int health;
};

extern robot_t robot;

void drawCircle(float x, float y, float radius);

void drawRobot(float characterSpeed);
void moveRobot();
int collideWithSpawnable(std::vector<spawnable_t> &spawnables);
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);

#endif