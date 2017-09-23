#include <iostream>
#include "Cube.h"

using namespace std;

int main() {
	setlocale(0, "rus");
	int NumberOfSides, DominantSides, NumberOfShots, Menu;
	cout << "Введите количество граней кубика:";
	cin >> NumberOfSides;
	Cube cube(NumberOfSides);
	cout << "1 - Равновероятные грани" << endl;
	cout << "2 - Разновероятные грани" << endl;
	cin >> Menu;
	switch (Menu) {
	case 1:
		cube.Equiprobable();
		break;
	case 2:
		cout << "Номер доминирующей грани:";
		cin >> DominantSides;
		cube.Unlikely(DominantSides);
		break;
	default:
		cout << "sdsdc";
		break;
	}
	cout << "Количество бросков:";
	cin >> NumberOfShots;
	cube.Drop(NumberOfShots);
	cube.Info();
	system("pause");
	return 0;
}