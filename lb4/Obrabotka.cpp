#include "Obrabotka.h"
#include<windows.h>

#define M_PI 3.14
#define M_E 2.71
#define M_ALPH 0.0
#define M_SGM 1.0
#define M_EPS 0.01

using namespace std;

float Obrabotka::Kolmogorov() {
	int K = 1 + (3.32*log10(_Arr.size()));
	float DMax = -100;
	for (int i = 0; i < K; i++) {
		if (DMax < fabs(P[i] - PV[i])) {
			DMax = fabs(P[i] - PV[i]);
		}
	}
	int n = _Arr.size();
	return (DMax*sqrt((n*n) / (n + n)));
}

double Obrabotka::Func_Laplace(double a, double precision) {
	int k = 1;
	if (a < 0) {
		a = fabs(a);
		k = -1;
	}
	double result = 0;
	for (double i = 0; i < a; i += precision) {
		result += precision*fabs(pow(M_E, -.5*pow(i, 2)) + pow(M_E, -.5*pow((i + precision), 2))) / 2.0;
	}
	result *= 1.0 / pow(2 * M_PI, .5);
	return result*k;

}

void Obrabotka::Draw() {
	int K = 1 + (3.32*log10(_Arr.size()));
	//делим на 4 части
	glColor3f(0.0f, 0.0f, 0.0f);
	//glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(0, 10);
	glVertex2f(20, 10);
	glVertex2f(10, 0);
	glVertex2f(10, 20);
	glEnd();

	int coordX = 11;
	int coordY = 11;

	float maxY;
	string title;
	vector<float>Histogram;
	vector<float>Line;
	vector<float>Line2;
	for (int q = 0; q < 3; q++) {
		maxY = 0;
		Histogram.clear();
		Line.clear();
		Line2.clear();
		switch (q){
		case 0:
			for (int i = 0; i < K; i++){
				Histogram.push_back(F[i]);
				Line2.push_back(Fe[i]);
				Line.push_back(PzFV[i]);
			}
			coordX = 1;
			coordY = 1;
			title = "Pr. zn. empir funkcii verojatnosti";
			break;
		case 1:
			for (int i = 0; i < K; i++) {
				Histogram.push_back(Fe[i]);
				Line.push_back(F[i]);
			}
			coordX = 1;
			coordY = 11;
			title = "Teor znac empir verojatnosti S.V";
			break;
		case 2:
			for (int i = 0; i < K; i++) {
				Histogram.push_back(PV[i]);
				Line.push_back(P[i]);
			}
			coordX = 11;
			coordY = 11;
			title = "Teor ver S.V";
			break;
		default:
			break;
		}

		glColor3f(0.0f, 0.0f, 1.0f);
		glRasterPos2f(coordX + 2, coordY + 8.25);
		for (int j = 0; j < title.length(); j++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[j]);
		}

		for (int i = 0; i < K; i++) {
			if (Histogram[i] > maxY) {
				maxY = Histogram[i];
			}
			if (Line[i] > maxY) {
				maxY = Line[i];
			}
		}

		float KX = 8.0 / K;
		float KY = 8.0 / maxY ;
		char text[10];
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(coordX - 0.3, coordY);
		glVertex2f(coordX - 0.3, coordY + 8);
		glVertex2f(coordX - 0.3, coordY);
		glVertex2f(coordX + 8, coordY);
		glEnd();
		float Dx;
		if (maxY <= 60) {
			Dx = 5;
		}
		if (maxY <= 40) {
			Dx = 4;
		}
		if (maxY <= 20) {
			Dx = 2;
		}
		if (maxY <= 10) {
			Dx = 1;
		}
		if (maxY <= 1) {
			Dx = 0.1;
		}
		if (maxY <= 0.5) {
			Dx = 0.05;
		}

		for (float i = 0; i <= maxY + Dx/2; i += Dx) {
			glBegin(GL_LINES);
			glVertex2f(coordX - 0.4, coordY + i*KY);
			glVertex2f(coordX - 0.3, coordY + i*KY);
			glEnd();
			glRasterPos2f(coordX - 0.8, 0.1 + coordY + i*KY);
			sprintf(text, "%1.2f", i);
			for (int j = 0; j < strlen(text); j++) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text[j]);
			}
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(1, 0x00F0);
			glBegin(GL_LINES);
			glVertex2f(coordX, coordY + i*KY);
			glVertex2f(coordX + 8, coordY + i*KY);
			glEnd();
			glDisable(GL_LINE_STIPPLE);
		}
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
		for (int i = 0; i < K; i++) {
			glRectf((coordX + i)*KX, coordY + Histogram[i] * KY, (coordX + i + 1)*KX, coordY);
		}
		
		glColor4f(1.0f, 0.0f, 0.0f, 0.9f);
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < K; i++) {
			glVertex2f(coordX + i*KX + 0.5, coordY + Line[i] * KY);

		}
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i < K; i++) {
			glVertex2f(coordX + i*KX + 0.5, coordY + Line[i] * KY);
		}
		glEnd();
		if(Line2.size()){
		glColor4f(0.0f, 1.0f, 0.0f, 0.9f);
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < K; i++) {
			glVertex2f(coordX + i*KX + 1, coordY + Line2[i] * KY);

		}
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
		for (int i = 0; i < K; i++) {
			glVertex2f(coordX + i*KX +1, coordY + Line2[i] * KY);
		}
		glEnd();
		}
		glDisable(GL_BLEND);
	}
}

void Obrabotka::Kalculate() {
	float min = 100, max = -100;
	for (auto i : _Arr) {
		if (i < min) {
			min = i;
		}
		if (i > max) {
			max = i;
		}
	}

	float R = max - min;
	int K = 1+(3.32*log10(_Arr.size()));
	float h = R / K;
	float S = min;// для заполнения значений границ интервалов
	for (int i = 0; i < K; i++) {
		Xp.push_back(0);
		Ni.push_back(0);
		Intervals.push_back(S);
		S += h;
	}
	Intervals.push_back(max);
	// попадание в интервалы СВ
	for (auto i : _Arr) {
		for (int j = 0; j < K; j++) {
			if (i <= Intervals[j + 1]) {
				Ni[j]++;
				Xp[j] += i;
				break;
			}
			else if (j == K - 1) {
				Ni[0]++;
				Xp[0] += i;
			}
		}
	}
	// попадание в интервалы СВ
	float Mx = Expectancy();
	float Sgm = SDeviation();
	float val = 0, val2=0, P_sum=0,Pi;
	int sm = 0, sm2=0;
	for (int i = 0; i < K; i++) {
		//вычисл 8 столбца
											// тут блять хуйня, доделать//
											/*\/ \/ \/ \/ \/ \/ \/ \/*/
		val = (float)sm / _Arr.size();
		val2 = (float)sm2 / _Arr.size();
		
		Pi = Func_Laplace((Intervals[i + 1] - Mx) / Sgm, M_EPS) - Func_Laplace((Intervals[i] - Mx) / Sgm, M_EPS);
		//P_sum += Pi;
		if (i == K - 1) {
			val += 1.0 - val;
			val2 += 1.0 - val2;
			Pi = 1 - P_sum;
		}
		PzFV.push_back(val);//8
		//вычисл 8 столбца
		PV.push_back((float)Ni[i] / _Arr.size());//6
		//Pi = Func_Laplace((Intervals[i + 1] - Mx) / Sgm, M_EPS) - Func_Laplace((Intervals[i] - Mx) / Sgm, M_EPS);
		P_sum += Pi;
		sm += Ni[i];
		

		P.push_back(Pi);//9
		//F.push_back(floor((P[i] * _Arr.size()) + 0.5));//10
		sm2 += floor((P[i] * _Arr.size()) + 0.5);
		F.push_back(val2);//10
	}
	float Sum = 0;
	for (int i = 0; i < K; i++) {
		Fe.push_back(F[i]);
		Sum += F[i];
	}
	Fe.push_back(1);
	cout.fill('-');
	cout << "+" << setw(4) << "+" << setw(9) << "+" << setw(9) << "+" << setw(10) << "+" << setw(5) << "+" << setw(10) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << endl;
	cout << "| № |   Хл   |   Хп   |   Хпр   | Ni |    Пв   | ДФПРВ  |   F*i  |   Pi   |    F   |" << endl;
	cout << "+" << setw(4) << "+" << setw(9) << "+" << setw(9) << "+" << setw(10) << "+" << setw(5) << "+" << setw(10) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << endl;
	cout.fill(' ');
	cout.fixed;
	cout.precision(4);
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	float Sum_1 = 0, Sum_2=0;
	int Sum_3 = 0;
	for (int i = 0; i < K; i++) {
		if (i % 2) {
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED |FOREGROUND_BLUE |FOREGROUND_GREEN);
		} else {
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN );
		}
		cout << "|" 
			<< setw(3) << i+1 << "|" 
			<< setw(8) << Intervals[i] << "|" 
			<< setw(8) << Intervals[i+1] << "|" << setw(9) << Xp[i]/Ni[i] << "|" 
			<< setw(4) << Ni[i] << "|" 
			<< setw(9) << PV[i] << "|"
			<< setw(8) << PV[i] / h << "|"
			<< setw(8) << PzFV[i] << "|"
			<< setw(8) << P[i] << "|"
			<< setw(8) << F[i] << "|"
			<< endl;
		Sum_1 += PV[i];
		Sum_2 += P[i];
		Sum_3 += Ni[i];
	}
	SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout.fill('-');
	cout << "+" << setw(4) << "+" << setw(9) << "+" << setw(9) << "+" << setw(10) << "+" << setw(5) << "+" << setw(10) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << endl;
	cout.fill(' ');
	cout << "|"
		<< setw(4) << "|"
		<< setw(9) << "|"
		<< setw(9) << "|" 
		<< setw(10) << "|"
		<< setw(4) << Sum_3 << "|"
		<< setw(9) << Sum_1 << "|"
		<< setw(9) << "|"
		<< setw(9) << "|"
		<< setw(8) << Sum_2<< "|"
		<< setw(9) << "|"
		<< endl;
	cout.fill('-');
	cout << "+" << setw(4) << "+" << setw(9) << "+" << setw(9) << "+" << setw(10) << "+" << setw(5) << "+" << setw(10) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << setw(9) << "+" << endl;
	cout.fill(' ');
}

float Obrabotka::SDeviation() {
	return sqrt(Dispersion());
}

float Obrabotka::Dispersion() {
	float D = 0;
	float M = Expectancy();
	for (auto i : _Arr) {
		D += powf((i-M),2);
	}
	D /= _Arr.size();
	return D;
}

float Obrabotka::Expectancy() {
	float S = 0;
	for (auto i : _Arr){
		S += i;
	}
	S /= _Arr.size();
	return S;
}

Obrabotka::Obrabotka(char* fn){
	ifstream f;
	f.open(fn);
	if (!f) {
		cout << "Ошибка открытия файла " << fn << endl;
		system("pause");
		exit(-1);
	}
	float tmp;
	while (!f.eof()){
		f >> tmp;
		_Arr.push_back(tmp);
	}

	f.close();
	cout << "Объем выборки: " << _Arr.size() << endl;
}

Obrabotka::Obrabotka(){

}


Obrabotka::~Obrabotka(){

}
