#include <iostream>
#include <glut.h>
#include "Obrabotka.h"

using namespace std;

Obrabotka O;

void Draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	O.Draw();

	glFlush();
}

int main(int argc, char** argv) {
	setlocale(0,"rus");
	O = Obrabotka("a.txt");
	cout << "Мат ожидание " << O.Expectancy() << endl;
	cout << "Дисперсия " << O.Dispersion() << endl;
	//O.Density();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(960, 480);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Grafik");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 20, -0.1, 1);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glutDisplayFunc(Draw);
	glutMainLoop();

	system("pause");
	return 0;
}