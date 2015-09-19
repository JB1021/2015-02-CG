#include "Ball.h"
#include <GL/glut.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>

Ball::Ball()
{
}


Ball::~Ball()
{
	printf("Delete!!\n");
}


void Ball::Init(int xx, int yy, int ballRadius)
{
	srand((unsigned int)time(NULL));
	
	xSpeed = (rand() % 20) - 10;
	ySpeed = (rand() % 20) - 10;
	zSpeed = rand() % 30;
	radius = (float)ballRadius;

	x = (float)(xx - 400)/100;
	y = -(float)(yy - 300)/100;
	z = -6;
	rX = 0;
	rY = 0;
	rZ = 0;
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;
}

void Ball::Update(float dt)
{
	if (z < -60) {
		zSpeed = -zSpeed;
	}
	if (x < -20) {
		x = -20;
		xSpeed = -xSpeed;
	}
	if (x > 20) {
		x = 20;
		xSpeed = -xSpeed;
	}
	if (y < -10) {
		y = -10;
		ySpeed = -ySpeed;
	}
	if (y > 10) {
		y = 10;
		ySpeed = -ySpeed;
	}

	z -= zSpeed * dt;
	x += xSpeed * dt;
	y += ySpeed * dt;
	rY += 10 * dt;
}

void Ball::Render()
{
	glColor3ub(r, g, b);
	glPushMatrix();

	glTranslated(x, y, z);
	
	glRotatef(rX, 1.0f, 0.0f, 0.0f);

	glutSolidSphere(radius, 50, 50);
	
	glPopMatrix();
}

bool Ball::IsGone()
{
	if (z  > -6)
		return true;
	return false;
}
