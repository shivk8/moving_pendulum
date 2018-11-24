#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include<stdlib.h>

using namespace std;

float coords[4] = { 5,5,5,25 };
float xr = 5, yr = 100;
void myInit()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(2);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-300, 300, -300, 300);
}

void plot(int a, int b, int xc, int yc)
{
	glBegin(GL_POINTS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2d(a + xc, b + yc);
	glEnd();

}



void midpoint(int xc, int yc, int r)
{
	int x, y, p;
	p = 1 - r;
	x = 0;
	y = r;
	plot(x, y, xc, yc);
	while (x <= y)
	{
		if (p <= 0)
		{
			x++;
			p += 2 * x + 1;
		}
		else
		{
			x++;
			y--;
			p += 2 * (x - y) + 1;
		}
		plot(x, y, xc, yc);
		plot(x, -y, xc, yc);
		plot(-x, y, xc, yc);
		plot(-x, -y, xc, yc);
		plot(y, x, xc, yc);
		plot(y, -x, xc, yc);
		plot(-y, x, xc, yc);
		plot(-y, -x, xc, yc);
	}

}

void rotatepen(float angles)
{
	double mat[3][3] = { 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0 };
	mat[0][0] = cos(angles);
	mat[0][1] = -sin(angles);
	mat[1][0] = sin(angles);
	mat[1][1] = cos(angles);
	mat[0][2] = xr * (1 - cos(angles)) + yr * sin(angles);
	mat[1][2] = yr * (1 - cos(angles)) - xr * sin(angles);
	double a[3][1], b[3][1];
	int index = 0;
	for (int c = 0; c < 2; ++c)
	{
		if (c == 0)
		{
			a[0][0] = coords[0];
			a[1][0] = coords[1];
		}
		if (c == 1)
		{
			a[0][0] = coords[2];
			a[1][0] = coords[3];
		}
		a[2][0] = 1.0;
		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 1; ++j)
			{
				b[i][j] = 0;
				for (int k = 0; k < 3; ++k)
				{
					b[i][j] += mat[i][k] * a[k][j];
				}
			}
		}
		coords[index] = b[0][0];
		coords[index + 1] = b[1][0];
		index += 2;
	}
}
void myDisplay()
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2d(5, 100);
	glVertex2d(5, 25);
	glEnd();
	glFlush();
	midpoint(5, 5, 20);
	int sum = 0;
	float ang, ang1;
	int angle = 5;
	ang = (float)(5 * 3.14 / 180);
	ang1 = (float)(-5 * 3.14 / 180);
	int flag = 0;
	while (1)
	{
		Sleep(200);
		glClear(GL_COLOR_BUFFER_BIT);
		sum += angle;
		if (flag == 0)
			rotatepen(ang);
		else
			rotatepen(ang1);
		midpoint(coords[0], coords[1], 20);
		glFlush();
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2d(5, 100);
		glVertex2d(coords[2], coords[3]);
		glEnd();
		glFlush();
		if (sum == 50.0)
		{
			flag = 1;
		}
		if (sum == 100.0)
		{
			flag = 1;
		}
		if (sum == 150.0)
		{
			flag = 0;
		}
		if (sum == 200.0)
		{
			sum = 0.0;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("fish");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 1;
}