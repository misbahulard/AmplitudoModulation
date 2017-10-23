// GelombangAM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <glut.h>

static float tick = 0;

typedef struct {
	float x;
	float y;
} point2D_t;

typedef struct {
	float r;
	float g;
	float b;
} color_t;

void setColor(color_t col) {
	glColor3f(col.r, col.g, col.b);
}

void drawPolyline(point2D_t pnt[], int n) {
	int i;
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < n; i++)
	{
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

void drawPolygon(point2D_t pnt[], int n) {
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < n; i++)
	{
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

void fillPolygon(point2D_t pnt[], int n, color_t color) {
	int i;
	setColor(color);
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++)
	{
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

void gradatePolygon(point2D_t pnt[], int n, color_t color) {
	int i;
	glBegin(GL_POLYGON);
	for (i = 0; i < n; i++)
	{
		setColor(color);
		glVertex2f(pnt[i].x, pnt[i].y);
	}
	glEnd();
}

void drawSineWave(point2D_t p[], float tck, int n) {
	for (int i = 0; i < n; i++)
	{
		p[i].x = (float)i;
		p[i].y = 250 * sin((i + tck) / 57.3);
	}

	drawPolyline(p, n);
}

void drawAm(point2D_t p[], float tck, int n) {
	for (int i = 0; i < n; i++)
	{
		p[i].x = (float)i;
		p[i].y = sin(2 * (22/7) * 0.01 * (i + tick)) * (1 + 100 * sin(2 * (22/7) * 2 * (i + tick)));
	}

	drawPolyline(p, n);
}

void userdraw() {
	color_t red = { 1, 0, 1 };
	setColor(red);

	point2D_t p[720];
	int n = 720;
	//drawSineWave(p, tick, n);
	drawAm(p, tick, 720);

	tick += 0.01;

	if (tick > n)
	{
		tick *= 0;
	}

}

void display(void) { //clear screen 
	glClear(GL_COLOR_BUFFER_BIT);
	userdraw();
	glutSwapBuffers();
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void initialize() {
	glClearColor(1, 1, 1, 0);
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Ortho sin
	gluOrtho2D(0., 720., -360, 360);
	// Ortho bunga
	// gluOrtho2D(-1., 1., -1., 1.);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	//Inisialisasi Toolkit 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My Awesome Drawing");
	initialize();
	glutIdleFunc(display);
	glutDisplayFunc(display);
	glutTimerFunc(1, timer, 0);
	glutMainLoop();
	return 0;
}


