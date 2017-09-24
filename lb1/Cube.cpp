#include "Cube.h"

void Cube::FillOrt() {
	float val = 0;
	for (int i = 0; i < _NumberOfSides; i++){
		_Ort[i] = val;
		val += _Probability[i];
	}
	_Ort[_NumberOfSides] = val;
}

void Cube::Unlikely(int Sides) {
	float tmp = 1.0 - _DominantValue;
	tmp /= (_NumberOfSides - 1);
	for (int i = 0; i < _NumberOfSides; i++) {
		_Probability[i] = tmp;
	}
	_Probability[Sides - 1] = _DominantValue;
}

void Cube::Equiprobable() {
	float tmp = 1.0 / _NumberOfSides;
	for (int i = 0; i < _NumberOfSides; i++)
		_Probability[i] = tmp;
}

void Cube::Info() {
	cout.fill('-');
	cout << "+" << setw(8) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	cout << "| № гр. | Теор.вероятность | Кол-во выпадений грани | Практ. вероятность |" << endl;
	cout << "+" << setw(8) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	cout.fill(' ');
	for (int i = 0; i < _NumberOfSides; i++) {
		cout << "|" << setw(7) << i + 1 << "|" << setw(16) << _Probability[i] * 100 << " %|"
			<< setw(24) << _AmountOfFallout[i] << "|"
			<< setw(18) << _AmountOfFallout[i] * 100 / _NumberOfShots << " %|" << endl;
	}
	cout.fill('-');
	cout << "+" << setw(8) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
}

void Cube::Drop(int NumberOfShots) {
	_NumberOfShots = NumberOfShots;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0, 1);
	for (int i = 0; i < NumberOfShots; i++) {
		float interval = dis(gen);
		for (int j = 0; j < _NumberOfSides; j++) {
			if (_Ort[j] < interval && _Ort[j + 1] >= interval) {
				_AmountOfFallout[j]++;
				break;
			}
		}
	}
}

bool Cube::Validation() {
	double eps = 1e-7;
	double tmp = 0;
	for (int i = 0; i < _NumberOfSides; i++) {
		tmp += _Probability[i];
	}	
	return fabs(tmp - 1.0)<eps;
}

Cube::Cube(int NumberOfSides) {
	_NumberOfSides = NumberOfSides;
	_Probability = new float[NumberOfSides];
	_AmountOfFallout = new int[NumberOfSides];
	_Ort = new float[NumberOfSides+1];
	for (int i = 0; i < NumberOfSides; i++) {
		_AmountOfFallout[i] = NULL;
	}
}

Cube::~Cube() {
	delete[] _Probability;
	delete[] _AmountOfFallout;
	delete[] _Ort;
}