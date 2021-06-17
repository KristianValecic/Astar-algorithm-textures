#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"Tocka.h"
class algoritam
{
private:
	static const int sirina = 30;
	static const int visina = 20;
	Tocka* tocke = nullptr;
	Tocka* cilj = nullptr;
	//SFML
	float dt;
	sf::Clock clock;
	float totalTime;
	float switchTime; // stavi u if
	sf::RectangleShape objStart;
	//
	auto udaljenost(Tocka* a, Tocka *b);
public:
	Tocka* pocetak = nullptr;
	int pocetakX;
	int pocetakY;
	void Astar();
	bool _next_step[sirina * visina];
	algoritam();
	void print();
	void next_step();
	void set_start(int x, int y);
	void set_cilj(int x, int y);
	void set_prepreka(int x, int y);
	/*int get_start_x();
	int get_start_y();*/
};

