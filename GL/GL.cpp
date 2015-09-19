#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h> 
#include <stdio.h>
#include <vector>

#include "Ball.h"


const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


static std::vector<Ball*> balls;

void SetupRC()
{
	glClearColor(1, 1, 1, 1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}


static void resize(int width, int height)
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Ball* ball = new Ball();
		ball->Init(x, y, 1);
		balls.push_back(ball);
	}
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		exit(1);
	}
}

boolean isCollision(Ball* ball, Ball* otherBall) {
	float x = ball->x;
	float y = ball->y;
	float z = ball->z;
	float oX = otherBall->x;
	float oY = otherBall->y;
	float oZ = otherBall->z;
	float distance = sqrt(pow(x - oX, 2) + pow(y - oY, 2)+ pow(z - oZ, 2));

	if (distance > ball->radius * 2) {
		return false;
	}
	else {
		return true;
	}
}

void Update(float dt)
{
	int tempI = -1;
	int checkTotal = 25;
	static int check = 0;
	check++;
	if (check > checkTotal) {
		check = 0;
		for (int i = 0; i < balls.size(); i++) {
			for (int j = i + 1; j < balls.size(); j++) {
				if (isCollision(balls[i], balls[j])) {

					balls[i]->xSpeed = -balls[i]->xSpeed;
					balls[i]->ySpeed = -balls[i]->ySpeed;
					balls[i]->zSpeed = -balls[i]->zSpeed;
					balls[i]->x += balls[i]->xSpeed * 0.35;
					balls[i]->y += balls[i]->ySpeed * 0.35;
					balls[i]->z += balls[i]->zSpeed * 0.35;

					if (balls[i]->xSpeed * balls[j]->xSpeed < 0) {
						balls[j]->xSpeed = -balls[j]->xSpeed;
					}
					if (balls[i]->ySpeed * balls[j]->ySpeed < 0) {
						balls[j]->ySpeed = -balls[j]->ySpeed;
					}
					if (balls[i]->zSpeed * balls[j]->zSpeed < 0) {
						balls[j]->zSpeed = -balls[j]->zSpeed;
					}

				}
			}
		}
	}
	int i = 0;
	for (auto& ball : balls)
	{
		ball->Update(dt);
		if (ball->IsGone())
		{
			tempI = i;
		}
		++i;
	}

	if (tempI != -1)
	{
		delete balls[tempI];
		balls.erase(balls.begin() + tempI);
	}


}


void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto& ball : balls)
	{
		ball->Render();
	}
	glutSwapBuffers();
}

void MainLoop()
{

	static int prevTime = GetTickCount();
	int curTime = GetTickCount();

	float dt = (float)(curTime - prevTime) / 1000;
	prevTime = curTime;

	Update(dt);
	Render();
}

int main(int argc, char *argv[])
{
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Programming Techniques - 3D Spheres");

	glutReshapeFunc(resize);
	glutDisplayFunc(Render);
	glutMouseFunc(mouse);
	glutIdleFunc(MainLoop);

	SetupRC();

	glutMainLoop();

	return EXIT_SUCCESS;
}