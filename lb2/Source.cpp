#include <iostream>
#include <iomanip>
#include "Cube.h"
#include <glut.h>

using namespace std;

int N = 0, NumberOfShots=0;
int *AmountOfFallout;
float *MTV, *MRV;

float Xi_kv() {
	float Xi_Square = 0.0;
	for (int i = 0; i < N; i++) {
		Xi_Square += pow(MTV[i] - MRV[i], 2.0) / MTV[i];
	}
	return Xi_Square *= NumberOfShots;
}

void Draw(void){
	glClear(GL_COLOR_BUFFER_BIT);
	char text[10];
	float maxY = 0;
	for (int i = 0; i < N; i++) {
		if (MTV[i] > maxY) {
			maxY = MTV[i];
		}
		if (MRV[i] > maxY) {
			maxY = MRV[i];
		}
	}
	float KX = 18.0 / N;
	float KY = 1.0 / maxY-0.1;
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(1);
	/*x*/
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(20, 0);
	glEnd();
	for (int i = 1; i < N+1; i++) {
		glRasterPos2f(i*KX, -0.05f);
		sprintf(text, "%d", i+1);
		for (int j = 0; j < strlen(text); j++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text[j]);
		}
	}
	/*y*/
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glEnd();
	for (float i = 0; i <= 1; i+=0.05) {
		glBegin(GL_LINES);
		glVertex2f(-0.2, i*KY);
		glVertex2f(0.2, i*KY);
		glEnd();
		glRasterPos2f(-0.7f, i*KY);
		sprintf(text, "%1.2f", i);
		for (int j = 0; j < strlen(text); j++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text[j]);
		}
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 0x00F0);
		glBegin(GL_LINES);
		glVertex2f(0, i*KY);
		glVertex2f(20, i*KY);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}

	glColor3f(1.0f, 0.5f, 1.0f);
	for (int i = 1; i < N + 1; i++) {
		glRectf((i + 0.1- 0.5)*KX, MTV[i-1] * KY, (i +0.9- 0.5)*KX, 0);
		
	}
	glColor3f(0.0f, 0.5f, 1.0f);
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	for (int i = 1; i < N+1; i++) {
		glVertex2f(i*KX, MRV[i-1]* KY);

	}
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int i = 1; i < N+1; i++) {
		glVertex2f(i*KX, MRV[i - 1] * KY);
	}
	glEnd();

	glFlush();
}

int  main(int argc, char** argv) {
	setlocale(0, "rus");
	int NumberOfSides, DominantSides, Menu, i = 0, tmp;
	bool end;
	Cube *cube = new Cube[2];
	while (i<2){
		cout << "Введите количество граней " << i+1 << " кубика:";
		cin >> NumberOfSides;
		cout << "1 - Равновероятные грани" << endl;
		cout << "2 - Разновероятные грани" << endl;
		cin >> Menu;
		switch (Menu) {
		case 1:
			cube[i] = Cube(NumberOfSides);
			break;
		case 2:
			cout << "Номер доминирующей грани:";
			cin >> DominantSides;
			cube[i] = Cube(NumberOfSides, DominantSides, 0.5);
			break;
		default:
			exit(0);
		}
		if (!cube[i].Validation()) {
			cout << "Сумма всех вероятностей не равна 1!" << endl;
			system("pause");
			exit(0);
		}
		i++;
	}
	N = cube[0].GetN() + cube[1].GetN() - 1;
	AmountOfFallout = new int[N] { NULL };
	MTV = new float[N] { NULL };
	MRV = new float[N] { NULL };
	for (int i = 0; i < cube[0].GetN(); i++) {
		for (int j = 0; j < cube[1].GetN(); j++) {
			MTV[i + j] += cube[0].GetMV(i)*cube[1].GetMV(j);
		}
	}
	cout << "Ручной/Автоматечиский режим бросков" << endl;
	cout << "1 - Автоматический" << endl;
	cout << "2 - Ручной" << endl;
	cin >> Menu;
	switch (Menu) {
	case 1:
		cout << "Количество бросков:";
		cin >> NumberOfShots;
		for (int i = 0; i < NumberOfShots; i++) {
			AmountOfFallout[cube[0].Drop() + cube[1].Drop() - 2] ++;
		}
		break;
	case 2:
		cout << "d-бросок, е-выход с режима" << endl;
		end = true;
		do {
			switch (getchar()){
			case 'd':
				tmp = cube[0].Drop() + cube[1].Drop() - 2;
				cout << "Суммы граней = " << tmp+2 << endl;
				AmountOfFallout[tmp] ++;
				NumberOfShots++;
				break;
			case 'e':
				end = false;
				break;
			default:
				break;
			}
		} while (end);
		break;
	default:
		exit(0);
	}
	for (int i = 0; i < N; i++) {
		MRV[i] = static_cast<float>(AmountOfFallout[i]) / NumberOfShots;
	}
	cout.fill('-');
	cout << "+" << setw(12) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	cout << "| сумма гр. | Теор.вероятность | Кол-во выпадений грани | Практ. вероятность |" << endl;
	cout << "+" << setw(12) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	cout.fill(' ');
	for (int j = 0; j < N; j++) {
		cout << "|" << setw(11) << j + 2 << "|" << setw(17) << MTV[j] << " |"<< setw(24) << AmountOfFallout[j] << "|" << setw(19) << MRV[j] << " |" << endl;
	}
	cout.fill('-');
	cout << "+" << setw(12) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	int Kol = 0;
	float rv = 0, tv = 0;
	for (int j = 0; j < N; j++) {
		Kol += AmountOfFallout[j];
		rv += MRV[j];
		tv += MTV[j];
	}
	cout.fill(' ');
	cout << "|" << setw(12) << "|" << setw(17) << tv << " |" << setw(24) << Kol << "|" << setw(19) << rv << " |" << endl;
	cout.fill('-');
	cout << "+" << setw(12) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	cout << "Хи-квадрат= " << Xi_kv() << endl;
	
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