#include "Cube.h"

void Cube::_FillOrt() {
	int j = 0;
	float i = 0.0;
	while (i <= 1.0) {
		_Ort[j] = i;
		if (i < 1.0)
			i += _Probability[j];
		else
			break;
		j++;
	}

}

void Cube::Unlikely(int Sides) {
	float chanceTemp = 1.0 - _DominantValue;
	chanceTemp /= (_NumberOfSides - 1);
	for (int i = 0; i < _NumberOfSides; i++) {
		_Probability[i] = chanceTemp;
	}
	_Probability[Sides - 1] = _DominantValue;
}

void Cube::Equiprobable() {
	float chanceTemp = 1.0 / _NumberOfSides;
	for (int i = 0; i < _NumberOfSides; i++)
		_Probability[i] = chanceTemp;
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
	_FillOrt();
	random_device rd;  //Will be used to obtain a seed for the random number engine
	mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	uniform_real_distribution<> dis(0, 1);

	for (int i = 0; i < NumberOfShots; i++) {
		float chanceTemp = dis(gen);
		for (int j = 1; j < _NumberOfSides + 1; j++) {
			if (_Ort[j] >= chanceTemp && _Ort[j - 1] < chanceTemp) {
				_AmountOfFallout[j - 1]++;
				break;
			}
		}
	}
}

bool Cube::Validation() {
	float tmp = 0;
	for (int i = 0; i < _NumberOfSides; i++) {
		tmp += _Probability[i];
	}	
	return tmp != 1;

}
Cube::Cube(int NumberOfSides) {
	_NumberOfSides = NumberOfSides;
	_Probability = new float[NumberOfSides];
	_AmountOfFallout = new int[NumberOfSides];
	_Ort = new float[NumberOfSides];
	for (int i = 0; i < NumberOfSides; i++) {
		_AmountOfFallout[i] = NULL;
	}
}

Cube::~Cube() {
	delete[] _Probability;
	delete[] _AmountOfFallout;
	//delete[] _Ort;
}