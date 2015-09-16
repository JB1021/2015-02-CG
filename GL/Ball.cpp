#include "Ball.h"
#include <GL/glut.h>
#include <stdio.h>

Ball::Ball()
{
}


Ball::~Ball()
{
	printf("Delete!!\n");
}


void Ball::Init(int xx, int yy)
{
	x = (float)(xx - 400)/100;
	y = -(float)(yy - 300)/100;
	z = -6;
	rX = 0;
	rY = 0;
	rZ = 0;
	speed = 30;
}

void Ball::Update(float dt)
{
	z -= speed * dt;
	rY += 10 * dt;
}

void Ball::Render()
{
	glColor3ub(255, 152, 45);

	glPushMatrix();

	glTranslated(x, y, z);
	
	//glRotatef(rX, 1.0f, 0.0f, 0.0f);
	//glRotatef(rY, 0.0f, 1.0f, 0.0f);
	//glRotatef(rX, 0.0f, 0.0f, 1.0f);

	glutSolidSphere(1, 50, 50);
	
	glPopMatrix();
}

bool Ball::IsGone()
{
	if (z < -100)
		return true;
	return false;
}
