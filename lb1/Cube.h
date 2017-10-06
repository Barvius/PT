#pragma once
#include<iostream>
#include<random>
using namespace std;
class Cube{
public:
	Cube();
	~Cube();
private:
	int _N;
	float* _MV;
	float* _ORT;
public:
	// Конструктор с заданием количества сторон
	Cube(int N);
	// Конструктор с заданием количества сторон и доминирующей грани
	Cube(int N, int DominantSides, float DominantValue);
private:
	// Заполнение массива вероятности и выделение памяти
	void _FillMV(int N, int DominantSides, float DominantValue);
public:
	// Бросок кубика
	int Drop();
	float* GetMV();
};

