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
	// ����������� � �������� ���������� ������
	Cube(int N);
	// ����������� � �������� ���������� ������ � ������������ �����
	Cube(int N, int DominantSides, float DominantValue);
private:
	// ���������� ������� ����������� � ��������� ������
	void _FillMV(int N, int DominantSides, float DominantValue);
public:
	// ������ ������
	int Drop();
	float* GetMV();
};

