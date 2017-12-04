#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <glut.h>

class Obrabotka
{
private:
	std::vector<float> _Arr;
	std::vector<float> Intervals;//2-3
	std::vector<float> Xp;//4
	std::vector<int> Ni;//5
	std::vector<float> PV;//6
	std::vector<float> PzFV;//8
	std::vector<float> P;//9
	std::vector<float> F;//10
	std::vector<float> Fe;//10
	double Func_Laplace(double,double);
public:
	void Draw();
	void Kalculate();
	float Kolmogorov();
	float SDeviation();
	float Dispersion();
	float Expectancy();
	Obrabotka(char*);
	Obrabotka();
	~Obrabotka();
};

