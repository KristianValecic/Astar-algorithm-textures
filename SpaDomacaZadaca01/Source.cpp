#include<SFML/Graphics.hpp>
#include<iostream>
#include"mapa.h"

using namespace std;

const int sirina = 900;
const int visina = 600;

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(sirina, (visina)), "Astariusov put", sf::Style::Default, settings);
	window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(1);
	

	//mapa map((sirina /20), (visina /20), pocetak, kraj, window);
	const float velicinaKocke = 30.f;
	const float VelicinaTeksture = 60.0f;

	mapa map((sirina / velicinaKocke), (visina / velicinaKocke),  velicinaKocke, VelicinaTeksture, window);

	bool inside;

	float dt;

	sf::Clock clock;

	while (window.isOpen())
	{

		map.getMousePos();
	

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			map.click(event);

			if (event.type == sf::Event::MouseEntered)
			{
				std::cout << "\nuso";
				inside = 1;
			}
			else if (event.type == sf::Event::MouseLeft)
			{
				std::cout << "\nizaso";
				inside = 0;

			}
		}
		window.clear();

		dt = clock.restart().asSeconds();

		window.draw(map);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && inside && map.je_prepreka())
		{
			map.crtaj();
		}

		window.display();
	}

	return 0;
}