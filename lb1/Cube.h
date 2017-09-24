#pragma once

#include <iostream>
#include <iomanip>
#include <random>

using namespace std;

class Cube{
private:
	int _NumberOfSides;
	float* _Probability;
	float* _Ort;
	float _DominantValue = 0.5;
	int* _AmountOfFallout;
	int _NumberOfShots;
public:
	void FillOrt();
	void Unlikely(int);
	void Equiprobable();
	void Info();
	void Drop(int);
	bool Validation();
	Cube(int);
	~Cube();

};
