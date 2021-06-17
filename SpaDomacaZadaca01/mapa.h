#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"algoritam.h"

class mapa : public sf::Drawable
{
private:
	sf::RenderWindow &window;
	sf::VertexArray obojano;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
	sf::RectangleShape border;
	sf::RectangleShape prepreka;
	sf::RectangleShape pocetak;
	sf::RectangleShape objStart;
	sf::RectangleShape cilj;
	sf::RectangleShape pozadinaIzbornika;
	sf::RectangleShape upute;
	sf::Texture texture;
	sf::Texture pozadina;
	sf::Texture preprekaT;
	sf::Texture startT;
	sf::Texture ciljT;
	sf::Font font;
	sf::Text text;
	sf::Text text1;
	sf::Text text2;
	sf::Text uputeT;
	int sirina;
	int visina;
	float VelicinaKocke;
	bool odabrana_prepreka;
	bool odabran_start;
	bool odabran_cilj;
	bool stavljen_start;
	bool stavljen_cilj;
	sf::Event event;
	algoritam algoritamA;
	float dt;
	sf::Clock clock;
	float totalTime;
	float switchTime;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; // sf::RenderTarget& target
	bool ispisiPoruku;
public:
	float VelicinaTeksture;
	sf::VertexArray polje;
	mapa(int sirina, int visina, float VelicinaKocke,float VelicinaTeksture, sf::RenderWindow& window);
	void getMousePos();
	void click(sf::Event event);
	void crtaj();
	bool je_prepreka();
	void update_pocetak(int x, int y);//int x, int y
	void update_trava(int x, int y); //int x, int y
};

