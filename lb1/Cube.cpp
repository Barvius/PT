#include "Cube.h"


Cube::Cube(){
	_FillMV(6, NULL, NULL);
}


Cube::~Cube(){
	delete[] _MV;
	delete[] _ORT;
}


// Конструктор с заданием количества сторон
Cube::Cube(int N){
	_FillMV(N, NULL, NULL);
}


// Конструктор с заданием количества сторон и доминирующей грани
Cube::Cube(int N, int DominantSides, float DominantValue){
	_FillMV(N, DominantSides, DominantValue);
}


// Заполнение массива вероятности и выделение памяти
void Cube::_FillMV(int N, int DominantSides, float DominantValue){
	_N = N;
	_MV = new float[N];
	_ORT = new float[N];
	float S = 0, V;
	V = (1.0 - DominantValue) / (_N - 1);
	for (int i = 0; i < _N - 1; i++) {
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
		val += _MV[i+1];
	}
	cout << "MV ";
	for (int i = 0; i < _N; i++) {
		cout << _MV[i] << " | ";
	}
	cout << endl;
	cout << "ORT ";
	for (int i = 0; i < _N; i++) {
		cout << _ORT[i] << " | ";
	}
	cout << endl;
	//_ORT[_N] = val;
}


// Бросок кубика
int Cube::Drop(){
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0,1);
	for (int i = 1; i < _N; i++){
		float val = dis(gen);
		//cout << val << endl;
		if(_ORT[i-1] < val && _ORT[i]>=val){
			//cout << val << " | " << i+1 <<endl;
			return i;
		}
	}
}


float* Cube::GetMV(){
	return _MV;
}
