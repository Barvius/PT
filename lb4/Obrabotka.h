#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <glut.h>

class Obrabotka
{
private:
	std::vector<float> _Arr;
	float _N;
public:
	void Draw();
	void Density();
	float SDeviation();
	float Dispersion();
	float Expectancy();
	Obrabotka(char*);
	Obrabotka();
	~Obrabotka();
};

