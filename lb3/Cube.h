#pragma once

#include<iostream>
#include<random>

class Cube {
private:
	int _N;
	float* _MV;
	float* _ORT;
public:
	int Drop();
	int GetN();
	float GetMV(int);
	bool Validation();
	Cube();
	Cube(int N);
	Cube(int N, int DominantSides, float DominantValue);
	Cube(int, double(*)(float, float), float, float);
	~Cube();
};