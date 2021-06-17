#pragma once
#include<vector>
using namespace std;
struct Tocka
{
	bool prepreka = false;
	bool posjecen = false;
	float globalGoal;
	float localGoal;
	int x;
	int y;
	vector<Tocka*> vecSusjedi;
	Tocka* parent;
};