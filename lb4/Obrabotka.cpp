#include "Obrabotka.h"

using namespace std;

void Obrabotka::Draw() {
	float ORT[8], MRV[8];
	int v[8] = { 0 };
	float M = Expectancy();
	float S = SDeviation();
	//ORT[3] = M;
	for (size_t i = 1; i <= 4; i++) {
		ORT[i - 1] = M - S * (4 - i);
		ORT[8 - i] = M + S * (5 - i);
	}
	size_t j;
	for (auto i : _Arr) {
		for (j = 0; j < 8; j++) {
			if (ORT[j] >= i) {
				v[j]++;
				break;
			}
		}
	}
	for (size_t i = 0; i < 8; i++) {
		MRV[i] = (float)v[i] / _Arr.size();
		cout << ORT[i] << " ";
	}
	cout << endl;

	char text[10];
	float maxY = 0;
	for (int i = 0; i < 8; i++) {
		if (MRV[i] > maxY) {
			maxY = MRV[i];
		}

	}
	float KX = 18.0 / 8;
	float KY = 1.0 / maxY -0.1;

	glColor3f(0.0f, 0.0f, 1.0f);
	glLineWidth(1);
	/*x*/
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(20, 0);
	glEnd();
	for (int i = 1; i < 8 + 1; i++) {
		glRasterPos2f(i*KX, -0.05f);
		sprintf(text, "%d", i + 1);
		for (int j = 0; j < strlen(text); j++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, text[j]);
		}
	}
	/*y*/
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glEnd();
	for (float i = 0; i <= 1; i += 0.05) {
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
	for (int i = 1; i < 8 + 1; i++) {
		glRectf((i + 0.1 - 0.5)*KX, MRV[i - 1] * KY, (i + 0.9 - 0.5)*KX, 0);

	}

}

void Obrabotka::Density() {
	float ORT[7];
	int v[7] = {0};
	float M = Expectancy();
	float S = SDeviation();
	ORT[3] = M;
	for (size_t i = 1; i <= 3; i++){
		ORT[i - 1] = M - S * (4 - i);
		ORT[7 - i] = M + S * (4 - i);
	}
	size_t j;
	for (auto i : _Arr) {
		for (j = 0; j < 7; j++) {
			if (ORT[j] >= i) {
				v[j]++;
				break;
			}
		}
	}
	for (size_t i = 0; i < 7; i++) {
		cout << ORT[i] << " ";
	}
	cout << endl;
	for (size_t i = 0; i < 7; i++) {
		cout << v[i] << " ";
	}
	cout << endl;
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
	cout << "size " << _Arr.size() << endl;
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
	cout << "size " << _Arr.size() << endl;
}

Obrabotka::Obrabotka(){

}


Obrabotka::~Obrabotka(){

}
