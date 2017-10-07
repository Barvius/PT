#include <iostream>
#include <iomanip>
#include "Cube.h"

using namespace std;

int main() {
	setlocale(0, "rus");
	int NumberOfSides, DominantSides, NumberOfShots, Menu;
	int *AmountOfFallout;
	float *MV;
	cout << "Введите количество граней кубика:";
	cin >> NumberOfSides;
	Cube *cube = new Cube;
	cout << "1 - Равновероятные грани" << endl;
	cout << "2 - Разновероятные грани" << endl;
	cin >> Menu;
	switch (Menu) {
	case 1:
		cube = new Cube(NumberOfSides);
		break;
	case 2:
		cout << "Номер доминирующей грани:";
		cin >> DominantSides;
		cube = new Cube(NumberOfSides, DominantSides, 0.5);
		break;
	default:
		exit(0);
	}
	if (!cube->Validation()) {
		cout << "Сумма всех вероятностей не равна 1!" << endl;
		system("pause");
		exit(0);
	}
	cout << "Количество бросков:";
	cin >> NumberOfShots;
	AmountOfFallout = new int[NumberOfSides] {NULL};
	MV = new float[NumberOfSides];
	MV = cube->GetMV();
	for (int i = 0; i < NumberOfShots; i++){
		AmountOfFallout[cube->Drop()] += 1;
	}
	cout.fill('-');
	cout << "+" << setw(8) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	cout << "| № гр. | Теор.вероятность | Кол-во выпадений грани | Практ. вероятность |" << endl;
	cout << "+" << setw(8) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	cout.fill(' ');
	for (int i = 0; i < 6; i++) {
		cout << "|" << setw(7) << i + 1 << "|" << setw(17) << MV[i] << " |"
			<< setw(24) << AmountOfFallout[i] << "|"
			<< setw(19) << static_cast<float>(AmountOfFallout[i]) / NumberOfShots << " |" << endl;
	}
	cout.fill('-');
	cout << "+" << setw(8) << "+" << setw(19) << "+" << setw(25) << "+" << setw(21) << "+" << endl;
	system("pause");
	return 0;
}