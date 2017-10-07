#pragma once

#include<iostream>
#include<random>

class Cube{
private:
	int _N;
	float* _MV;
	float* _ORT;
	void _FillMV(int N, int DominantSides, float DominantValue);
public:
	int Drop();
	float* GetMV();
	bool Validation();
	Cube();
	Cube(int N);
	Cube(int N, int DominantSides, float DominantValue);
	~Cube();
};

