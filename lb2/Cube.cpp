#include "Cube.h"

using namespace std;

void Cube::_FillMV(int N, int DominantSides, float DominantValue) {
	int Nd = _N = N;
	_MV = new float[N];
	_ORT = new float[N];
	float S = 0, V;
	if (DominantSides) {
		_DominantSides = DominantSides;
		_DominantValue = DominantValue;
		Nd--;
	}
	V = (1.0 - DominantValue) / (Nd);
	for (int i = 0; i < _N - 1; i++) {
		if (i + 1 == DominantSides && DominantSides) {
			_MV[i] = DominantValue;
		}
		else {
			_MV[i] = V;
		}
		S += _MV[i];
	}
	_MV[N - 1] = 1.0 - S;
	float val = 0;
	for (int i = 0; i < _N; i++) {
		val += _MV[i];
		_ORT[i] = val;
	}
}

int Cube::Drop() {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	float val = dis(gen);
	for (int i = 0; i < _N; i++) {
		if (_ORT[i] >= val) {
			return i + 1;
		}
	}
	return 0;
}

float* Cube::GetMV() {
	return _MV;
}

bool Cube::Validation() {
	float tmp = 0;
	for (int i = 0; i < _N; i++) {
		tmp += _MV[i];
	}
	return tmp == 1;
}

Cube::Cube() {
	
}

Cube::Cube(Cube &obj) {
	_FillMV(obj.GetN(), obj.GetDS(), obj.GetDV());
}

Cube::~Cube() {
	delete[] _MV;
	delete[] _ORT;
}

Cube::Cube(int N) {
	_FillMV(N, NULL, NULL);
}

Cube::Cube(int N, int DominantSides, float DominantValue) {
	_FillMV(N, DominantSides, DominantValue);
}

int Cube::GetN() {
	return _N;
}

int Cube::GetDS() {
	return _DominantSides;
}

float Cube::GetDV() {
	return _DominantValue;
}

float Cube::GetMV(int i) {
	return _MV[i];
}

Cube &Cube::operator = (Cube &obj) {
	_FillMV(obj.GetN(), obj.GetDS(), obj.GetDV());
	return Cube(*this);
}