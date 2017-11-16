#pragma once

#include<iostream>
#include<random>

class Cube {
private:
	int _N;
	float* _MV;
	float* _ORT;
	int _DominantSides=NULL;
	float _DominantValue=NULL;
	void _FillMV(int N, int DominantSides, float DominantValue);
public:
	int GetN();
	int GetDS();
	float GetDV();
	int Drop();
	float* GetMV();
	float GetMV(int);
	bool Validation();
	Cube();
	Cube &Cube::operator = (Cube &obj);
	Cube(Cube&);
	Cube(int N);
	Cube(int N, int DominantSides, float DominantValue);
	~Cube();
};
