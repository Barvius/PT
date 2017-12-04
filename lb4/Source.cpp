#include <iostream>
#include <glut.h>
#include <windows.h>
#include "Obrabotka.h"

using namespace std;

Obrabotka O;

void Draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	O.Draw();

	glFlush();
}

int main(int argc, char** argv) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("mode con cols=90 lines=25");

	O = Obrabotka("out.txt");
	O.Kalculate();
	cout << "Мат ожидание " << O.Expectancy() << endl;
	cout << "Дисперсия " << O.Dispersion() << endl;
	cout << "СКО " << O.SDeviation() << endl;
	cout << "Критерий Колмогорова " << O.Kolmogorov() << endl;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(960, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Grafik");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 20, 0, 20);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_RGBA_MODE);
	glutDisplayFunc(Draw);
	glutMainLoop();
	
	system("pause");
	return 0;
}