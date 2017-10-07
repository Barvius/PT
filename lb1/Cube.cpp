#include "Cube.h"

using namespace std;

void Cube::_FillMV(int N, int DominantSides, float DominantValue) {
	int Nd = _N = N;
	_MV = new float[N];
	_ORT = new float[N];
	float S = 0, V;
	if (DominantSides) {
		Nd--;
	}
	V = (1.0 - DominantValue) / (Nd);
	for (int i = 0; i < _N-1; i++) {
		if (i + 1 == DominantSides && DominantSides) {
			_MV[i] = DominantValue;
		} else {
			_MV[i] = V;
		}
		S += _MV[i];
	}
	_MV[N - 1] = 1.0 - S;
	float val = _MV[0];
	for (int i = 0; i < _N; i++) {
		_ORT[i] = val;
		val += _MV[i + 1];
	}
}

int Cube::Drop() {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	for (int i = 0; i < _N; i++) {
		float val = dis(gen);
		if (_ORT[i] >= val) {
			return i;
		}
	}
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

Cube::Cube(){
	_FillMV(6, NULL, NULL);
}


Cube::~Cube(){
	delete[] _MV;
	delete[] _ORT;
}

Cube::Cube(int N){
	_FillMV(N, NULL, NULL);
}

Cube::Cube(int N, int DominantSides, float DominantValue){
	_FillMV(N, DominantSides, DominantValue);
}


