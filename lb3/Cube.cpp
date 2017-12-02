#include "Cube.h"

using namespace std;

int Cube::GetN() {
	return _N;
}
int Cube::Drop() {
	int interval = 1;
	double x;
	x = (double)rand() / RAND_MAX;
	for (int i = 1; i < _N + 1; i++) {
		if (x <= _ORT[i]) {
			interval = i;
			break;
		}
	}
	return interval;
}

float Cube::GetMV(int i) {
	return _MV[i];
}

bool Cube::Validation() {
	float tmp = 0;
	for (int i = 0; i < _N; i++) {
		tmp += _MV[i];
	}
	return tmp == 1;
}

Cube::Cube() {
	//_FillMV(6, NULL, NULL);
}


Cube::~Cube() {
	delete[] _MV;
	delete[] _ORT;
}

Cube::Cube(int N) {
	//_FillMV(N, NULL, NULL);
}

Cube::Cube(int N, int DominantSides, float DominantValue) {
	//_FillMV(N, DominantSides, DominantValue);
}

Cube::Cube(int N, double(*F)(float, float), float A, float B){
	_N = N;
	_MV = new float[_N];
	_ORT = new float[_N];
	float h = (B - A) / _N;
	float x = A, S = 0;
	for (int i = 0; i < _N; i++)
	{
		_MV[i] = F(x, x + h);
		S += _MV[i];
		x += h;
	}
	float correctionFactor = (float)1 / S;
	S = 0;
	for (int i = 0; i < _N - 1; i++)
	{
		_MV[i] *= correctionFactor;
		S += _MV[i];
		_ORT[i] = S;
	}
	_MV[_N - 1] = 1 - S;
	_ORT[_N - 1] = 1;
	cout << endl;
}
