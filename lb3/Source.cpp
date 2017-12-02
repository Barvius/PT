#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include "Cube.h"

#define I_A -3.0
#define I_B 3.0

#define M_PI 3.14
#define M_E 2.71
#define M_ALPH 0.0
#define M_SGM 1.0
#define eps 0.001

using namespace std;

double Normal_distribution(double x) {
	double E = pow(M_E, -(powf(x - M_ALPH, 2) / (2 * pow(M_SGM, 2))));
	return (1.0 / (M_SGM*sqrt(2.0 * M_PI)))*E;
}

double Integral(float A, float B) {
	double S1, x;
	double h = B - A;
	double S = Normal_distribution(A) * h;
	do {
		h = h / 2;
		S1 = S;
		S = 0;
		for (x = A; x <= B - h / 2; x += h)
			S += Normal_distribution(x);
		S *= h;
	} while (fabs(S1 - S) > eps);
	return S;
}

int main() {
	setlocale(0,"rus");
	int Selection, Interval;

	do {
		cout << "Выборка: ";
		cin >> Selection;
		if (Selection < 80 || Selection > 150) {
			cout << "Вы ввели число выходящие за диапазон 80-150!" << endl;
			continue;
		}
		else break;
	} while (true);
	do {
		cout << "Кол-во интервалов: ";
		cin >> Interval;
		if (Interval < 11 || Interval > 17) {
			cout << "Вы ввели число выходящие за диапазон 11-17!" << endl;
			continue;
		}
		else break;
	} while (true);
	Cube c(Interval,Integral,I_A,I_B);
	float h = (float)(I_B - I_A) / Interval;
	float *x = new float[Selection];
	int nom;
	float a1; 

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);

	ofstream f("out.txt", ios_base::trunc);
	for (int i = 0; i < Selection; i++) {
		x[i] = I_A + (c.Drop() - 1) * h + h * (double)rand() / RAND_MAX;
		cout << setw(10) << setprecision(4) << x[i];
		if (i == Selection - 1) { 
			f << x[i]; 
		}
		else { 
			f << x[i] << endl; 
		}
	}
	cout << endl;
	f.close();
	delete[] x;
	system("pause");
	return 0;
}