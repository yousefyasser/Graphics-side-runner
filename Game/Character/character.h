#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

struct robot_t {
	float speed;
	float xPos;
	float yPos;
	float jumpSpeed;
	float jumpHeight;
	int health;
};

extern robot_t robot;

void drawCircle(float x, float y, float radius);

void drawRobot(float characterSpeed);
void moveRobot();
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);

#endif