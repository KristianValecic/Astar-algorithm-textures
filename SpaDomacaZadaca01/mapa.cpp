#include"mapa.h"
#include"tocka.h"
#include"algoritam.h"
#include<SFML/Graphics.hpp>
#include<ctime>
#include<sstream>
#include<dos.h> 
#include <conio.h> 
//-----TODO--------
//napravi da se pomice blok po blok (igraj se s parentima i updateima)


//mozda dodaj travu (visak vremena)
//prepravi ime u teksture
//prepravi teksturu trave
//popravi teksturu kamena (rubovi)
//dodaj poruku za upute i komentar


void mapa::draw(sf::RenderTarget& target, sf::RenderStates states)  const
{
	window.clear(sf::Color(112, 125, 6));
	states.texture = &texture;
	target.draw(polje, states); 

	//ZA TESTIRANJE PRIKAZ KURSORA:
	std::stringstream ss;
	system("cls");
	ss<<  mousePosGrid.x << " " << mousePosGrid.y << "\n";
	std::cout << ss.str();
	std::cout << visina << endl;

	target.draw(pozadinaIzbornika);
	target.draw(prepreka);
	target.draw(pocetak);
		
	target.draw(cilj);
	target.draw(text);
	target.draw(text1);
	target.draw(text2);
	if (ispisiPoruku)
	{
	target.draw(upute);
	target.draw(uputeT);
	}

	target.draw(border);
}

void mapa::getMousePos()
{
	border.setPosition(mousePosGrid.x * VelicinaKocke, mousePosGrid.y * VelicinaKocke); // 

	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(mousePosWindow);
	if (mousePosView.x >= 0.f)
	{
		mousePosGrid.x = mousePosView.x / (unsigned)VelicinaKocke;
	}
	if (mousePosView.y >= 0.f)
	{
		mousePosGrid.y = mousePosView.y / (unsigned)VelicinaKocke;
	}
	dt = clock.restart().asSeconds();
	totalTime += dt;




}



void mapa::update_pocetak(int x, int y)
{

				polje[(x * visina + y) * 4].texCoords = sf::Vector2f((VelicinaTeksture * 2) + 30, 7);
				polje[(x * visina + y) * 4 + 1].texCoords = sf::Vector2f((VelicinaTeksture * 3) + 30, 7);
				polje[(x * visina + y) * 4 + 2].texCoords = sf::Vector2f((VelicinaTeksture * 3) + 30, VelicinaTeksture + 7);
				polje[(x * visina + y) * 4 + 3].texCoords = sf::Vector2f((VelicinaTeksture * 2) + 30, VelicinaTeksture + 7);

}
//postavi otiske koraka
void mapa::update_trava(int x, int y)
{
	polje[(x * visina + y) * 4].texCoords = sf::Vector2f((VelicinaTeksture * 4) +60, 7);
	polje[(x * visina + y) * 4 + 1].texCoords = sf::Vector2f((VelicinaTeksture * 5) + 60, 7);
	polje[(x * visina + y) * 4 + 2].texCoords = sf::Vector2f((VelicinaTeksture * 5) + 60, VelicinaTeksture+7);
	polje[(x * visina + y) * 4 + 3].texCoords = sf::Vector2f((VelicinaTeksture * 4) + 60, VelicinaTeksture+7);
}


//handle-anje eventa
void mapa::click(sf::Event event) {

	this->event = event;
	//postavlja start
	if (event.type == sf::Event::MouseButtonPressed && odabran_start && stavljen_start)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			//Promijenio koordinate teksutre da radi
		polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4].texCoords = sf::Vector2f((VelicinaTeksture * 2)+30, 7);
		polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 1].texCoords = sf::Vector2f((VelicinaTeksture * 3) + 30, 7);
		polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 2].texCoords = sf::Vector2f((VelicinaTeksture * 3) + 30, VelicinaTeksture+7);
		polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 3].texCoords = sf::Vector2f((VelicinaTeksture * 2) + 30, VelicinaTeksture+7);


			algoritamA.set_start(mousePosGrid.x, mousePosGrid.y);

			stavljen_start = false;
		}
	}
	//postavlja cilj
	if (event.type == sf::Event::MouseButtonPressed && odabran_cilj && stavljen_cilj)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4].texCoords = sf::Vector2f((VelicinaTeksture * 3) + 40, 7);
			polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 1].texCoords = sf::Vector2f((VelicinaTeksture * 4) + 40, 7);
			polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 2].texCoords = sf::Vector2f((VelicinaTeksture * 4) + 40, VelicinaTeksture+7);
			polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 3].texCoords = sf::Vector2f((VelicinaTeksture * 3) + 40, VelicinaTeksture+7);

			algoritamA.set_cilj(mousePosGrid.x, mousePosGrid.y);

			stavljen_cilj = false;
		}
	}

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{

			cout << "Space\n";

				cout << totalTime << endl;

				algoritamA.Astar();

					if (algoritamA.pocetak != nullptr)
					{
						Tocka* p = algoritamA.pocetak;
						while (p->parent != nullptr)
						{
							totalTime -= switchTime;
							Tocka* p1 = p->parent;
							
								update_pocetak(p1->x, p1->y);
								window.draw(objStart);
								update_trava(p->x, p->y);
	
							p = p1;
						}

					}
					ispisiPoruku = 0;
		}

	}

		if (mousePosGrid.x == 2 && mousePosGrid.y == 17 && event.mouseButton.button == sf::Mouse::Left) // prepreka
		{
		
			prepreka.setOutlineThickness(1.f);
			prepreka.setOutlineColor(sf::Color::White);

			pocetak.setOutlineThickness(0.f);
			cilj.setOutlineThickness(0.f);
	
			odabrana_prepreka = true;
			odabran_start = false;
			odabran_cilj = false;

		}
		else if (mousePosGrid.x == 5 && mousePosGrid.y == 17 && event.mouseButton.button == sf::Mouse::Left)// start 
		{
		
			pocetak.setOutlineThickness(1.f);
			pocetak.setOutlineColor(sf::Color::White);

			prepreka.setOutlineThickness(0.f);
			cilj.setOutlineThickness(0.f);

			odabrana_prepreka = false;
			odabran_start = true;
			odabran_cilj = false;
			

		}
		else if (mousePosGrid.x == 8 && mousePosGrid.y ==17 && event.mouseButton.button == sf::Mouse::Left)// cilj 
		{
		
			cilj.setOutlineThickness(1.f);
			cilj.setOutlineColor(sf::Color::White);

			prepreka.setOutlineThickness(0.f);
			pocetak.setOutlineThickness(0.f);

			odabrana_prepreka = false;
			odabran_start = false;
			odabran_cilj = true;
		}
}

//boja polja, postavlja prepreku
void mapa::crtaj()
{
	polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4].texCoords = sf::Vector2f(VelicinaTeksture+12, 7);
	polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 1].texCoords = sf::Vector2f((VelicinaTeksture+12)*2, 7);
	polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 2].texCoords = sf::Vector2f((VelicinaTeksture+12)*2, VelicinaTeksture+7);
	polje[(mousePosGrid.x * visina + mousePosGrid.y) * 4 + 3].texCoords = sf::Vector2f((VelicinaTeksture+12), VelicinaTeksture+7);

	algoritamA.set_prepreka(mousePosGrid.x, mousePosGrid.y);
}


bool mapa::je_prepreka()
{
	if (odabrana_prepreka)
	{
	return true;
	}
	else {
	return false;
	}
}

mapa::mapa(int sirina, int visina, float VelicinaKocke, float VelicinaTeksture, sf::RenderWindow& window): window(window) // sf::RenderWindow& window
{
	srand(time(nullptr));

	this->sirina = sirina;
	this->visina= visina;

	this->VelicinaKocke = VelicinaKocke;
	this->VelicinaTeksture = VelicinaTeksture;

	stavljen_cilj = true;
	stavljen_start = true;

	//switchTime = 0.1f;

	ispisiPoruku = 1;

	polje.setPrimitiveType(sf::Quads);	

	if (!texture.loadFromFile("teksture.png")) //prepreavi ime u teksture 
	{
		std::cout << "Greska s travom";
		
	}
	if (!pozadina.loadFromFile("pozadinaIzbornika.png"))
	{
		std::cout << "Greska s teksturom izbornikom";
		
	}
	if (!preprekaT.loadFromFile("prepreka.jpg"))
	{
		std::cout << "Greska s teksturom izbornikom";

	}
	if (!startT.loadFromFile("start.png"))
	{
		std::cout << "Greska s teksturom izbornikom";

	}
	if (!ciljT.loadFromFile("cilj.png"))
	{
		std::cout << "Greska s teksturom izbornikom";

	}
	
	if (!font.loadFromFile("RobotoMono-Italic-VariableFont_wght.ttf"))//RobotoMono - Italic - VariableFont_wght
	{
		std::cout << "greska s fontom;";
	}	
	
	text.setFont(font);
	text.setString("Prepreka");
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(15);
	//text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(2.f * VelicinaKocke +(VelicinaKocke/4), 16.f * VelicinaKocke + (VelicinaKocke / 4)) ); //greska
	text.setOrigin(sf::Vector2f(25.f, 0.f));

	text1.setFont(font);
	text1.setString("Start");
	text1.setFillColor(sf::Color::Black);
	text1.setCharacterSize(15);
	//text1.setStyle(sf::Text::Bold);
	text1.setPosition(sf::Vector2f(5.f * VelicinaKocke + (VelicinaKocke / 4), 16.f * VelicinaKocke + (VelicinaKocke / 4)));
	text1.setOrigin(sf::Vector2f(12.f,0.f));
	
	text2.setFont(font);
	text2.setString("Cilj");
	text2.setFillColor(sf::Color::Black);
	text2.setCharacterSize(15);
	//text2.setStyle(sf::Text::Bold);
	text2.setPosition(sf::Vector2f(8.f * VelicinaKocke + (VelicinaKocke / 4), 16.f * VelicinaKocke + (VelicinaKocke / 4)));
	text2.setOrigin(sf::Vector2f(10.f, 0.f));

	uputeT.setFont(font);
	uputeT.setString("Kada ste postavili viteza Astariusa na svoje\npochetno mjesto i odredili mu cilj, kliknite tipku\nspace kako bi on pronasao najbrzi put do svoje kule.\nChvrsto postavite zidine, vitez je vitak i moze\nse provuci kroz rupe");
	uputeT.setFillColor(sf::Color::Black);
	uputeT.setCharacterSize(15);
	//text2.setStyle(sf::Text::Bold);
	uputeT.setPosition(sf::Vector2f(12.f * VelicinaKocke + (VelicinaKocke / 4), 16.f * VelicinaKocke + (VelicinaKocke / 4)));
	uputeT.setOrigin(sf::Vector2f(10.f, 0.f));

	for (int i = 0; i < (sirina); i++)
	{
		for (int j = 0; j < (visina); j++)
		{	
			polje.append(sf::Vertex(sf::Vector2f(0.0f,			 0.0f) + sf::Vector2f((float)i, (float)j) * VelicinaKocke, sf::Vector2f(5, 8)));
			polje.append(sf::Vertex(sf::Vector2f(VelicinaKocke,	 0.0f) + sf::Vector2f((float)i, (float)j) * VelicinaKocke, sf::Vector2f(VelicinaTeksture+5, 8))); // namjestit po koordinatama teksturu 
			polje.append(sf::Vertex(sf::Vector2f(VelicinaKocke,	 VelicinaKocke) + sf::Vector2f((float)i, (float)j) * VelicinaKocke, sf::Vector2f(VelicinaTeksture+5, VelicinaTeksture+8))); // Yellow
			polje.append(sf::Vertex(sf::Vector2f(0.0f, VelicinaKocke) + sf::Vector2f((float)i, (float)j) * VelicinaKocke, sf::Vector2f(5, VelicinaTeksture+8))); //sf::Vector2f(0, VelicinaTeksture))
			
		}
	}
	//x - pocetak.first
	//y - pocetak.second
	
	//oblikuje broder od kursora
	border.setSize(sf::Vector2f(VelicinaKocke, VelicinaKocke));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(1.f);
	border.setOutlineColor(sf::Color::White);

	//oblikujem izbornik 
	prepreka.setPosition(sf::Vector2f(2.f, 17.f )*VelicinaKocke);
	//prepreka.setFillColor(sf::Color(40,40,40));
	prepreka.setSize(sf::Vector2f(VelicinaKocke, VelicinaKocke));
	prepreka.setTexture(&preprekaT);

	pocetak.setPosition(sf::Vector2f(5.f, 17.f) * VelicinaKocke);
	pocetak.setSize(sf::Vector2f(VelicinaKocke, VelicinaKocke));
	//pocetak.setFillColor(sf::Color::Red);
	pocetak.setTexture(&startT);


	cilj.setPosition(sf::Vector2f(8.f, 17.f ) * VelicinaKocke);
	//cilj.setFillColor(sf::Color::Green);
	cilj.setSize(sf::Vector2f(VelicinaKocke, VelicinaKocke));
	cilj.setTexture(&ciljT);
	
	pozadinaIzbornika.setPosition(sf::Vector2f(1.f , 16.f ) * VelicinaKocke);			//* VelicinaKocke,  promijeni na matematiku grida 
	//pozadinaIzbornika.setFillColor(sf::Color(125, 100, 0));
	pozadinaIzbornika.setSize(sf::Vector2f(9.f, 3.f) * VelicinaKocke);
	pozadinaIzbornika.setTexture(&pozadina);
	//pozadinaIzbornika.setOrigin(175.f, -25.f);

	upute.setPosition(sf::Vector2f((11.f * VelicinaKocke), (16.f * VelicinaKocke)-12));			//* VelicinaKocke,  promijeni na matematiku grida 
	//pozadinaIzbornika.setFillColor(sf::Color(125, 100, 0));
	upute.setSize(sf::Vector2f(17.f * VelicinaKocke, (4.f * VelicinaKocke)+10));
	upute.setTexture(&pozadina);
}




