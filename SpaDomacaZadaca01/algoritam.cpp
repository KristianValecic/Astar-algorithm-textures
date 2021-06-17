#include "algoritam.h"
#include "mapa.h"
#include<iostream>
#include<list>
#include"Tocka.h"
using namespace std;

auto algoritam::udaljenost(Tocka* a, Tocka* b)
{
	return sqrtf((a->x-b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y));
}

algoritam::algoritam()
{
	//kreiram polje tocaka u headeru


	//punim prazne tocke
	tocke = new Tocka[sirina * visina]; // logika je x(i)*sirna + y(j)
	for (int i = 0; i < sirina; i++)				// logika je x(i)*sirna + y(j)
	{
		for (int j = 0; j < visina; j++)
		{
			tocke[i + j * sirina].x = i;
			tocke[i + j * sirina].y = j;
			tocke[i + j * sirina].prepreka = false;
			tocke[i + j * sirina].parent = nullptr;
			tocke[i + j * sirina].posjecen = false;
		}
	}
	//kreiram pocetak i cilj u headeru	 
	
	//kreiram prepreku
	/*for (int i = 0; i < 14; i++)
	{
		tocke[i * sirina + 17].prepreka = true; // tocke: (0,7) (1,7) (2,7) (3,7) (4,7)
	}*/

	//spajam veze medu tockama
	for (int i = 0; i < sirina; i++)
	{
		for (int j = 0; j < visina; j++)
		{
			if (j > 0)
			{
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(i + 0) + (j - 1) * sirina]);	//						sjever
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(i + 1) + (j - 1) * sirina]);	//						sjevero istok
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(i - 1) + (j - 1) * sirina]);	//	(0,0)(1,0)(2,0)		sjevero zapad
			}																					//	(0,1)(1,1)(2,1)
			if (j < visina - 1)																	//	(0,2)(1,2)(2,2)	
			{																					//	(0,3)(1,3)(2,3)
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(i + 0) + (j + 1) * sirina]);	//	(0,4)(1,4)(2,4)		jug
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(i + 1) + (j + 1) * sirina]);	//						jug istok
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(i - 1) + (j + 1) * sirina]);	//						jug zapad
			}

			if (i > 0)
			{
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(i - 1) + (j + 0) * sirina]);	//						zapad
			}
			if (i < sirina - 1)
			{
				tocke[j * sirina + i].vecSusjedi.push_back(&tocke[(j + 0) * sirina + (i + 1)]);//						istok
			}
		}
	}

	//pocetak = &tocke[0 + 1 * sirina];	//upis pocetka
	//cilj = &tocke[27 + 3 * sirina];		//upis cilja

}
// i = x ili sirina, j = y ili visina
void algoritam::print()
{
	Astar();
	
	system("cls");
	for (int j = 0; j < visina; j++)
	{
		for (int i = 0; i < sirina; i++)
		{
			if (pocetak == &tocke[i + j * sirina] /*|| _next_step[i + j * sirina]*/)
			{
				cout << "A";
			}
			else if (cilj == &tocke[i + j * sirina])
			{
				cout << "B";
			}
			else if (tocke[i + j * sirina].prepreka == 1)
			{
				cout << "X";
			}
			else if (_next_step[i + j*sirina])
			{
				/*pocetakX = i;
				pocetakY = j;*/
				/*map.objStart.setPosition(sf::Vector2f(i, j) * 30.f);
				map.update_pocetak(i, j);*/
				cout << "*";
			}
			else if (!_next_step[(i + j * sirina) - 1])
			{
				cout << "-";
			}
			else /*if (tocke[i + j * sirina].prepreka == 0)*/
			{
				cout << "-";
			}			
		}
		cout << endl;
	}

	//return 1;
	switchTime = 0.01f;

	dt = clock.restart().asSeconds();
}

void algoritam::set_start(int x, int y)
{
	pocetak = &tocke[x + y * sirina];	//upis pocetka
}

void algoritam::set_cilj(int x, int y)
{
	cilj = &tocke[x + y * sirina];
}

void algoritam::set_prepreka(int x, int y) //ako ne valja mat. onda pogledaj mat u domu
{
	tocke[x + y * sirina].prepreka = true;
}

/*int algoritam::get_start_x()
{
	return pocetak->x;
}
int algoritam::get_start_y()
{
	return pocetak->y;
}*/

void algoritam::next_step()//sf::Time dt
{
	totalTime += dt;

	if (pocetak != nullptr)
	{
		Tocka* p = pocetak;
		while (p->parent != nullptr)			// radi ali sporo, switchtime mora biti jako malen i tada dode samo do pola
		{
			//if (totalTime > switchTime)
			
			_next_step[p->x + p->y * sirina] = 1;
			//cout << totalTime << endl;
			//totalTime -= switchTime;
			print();
			
			pocetakX = p->x;
			pocetakY = p->y;
			
			//map.update_pocetak(p->x, p->y);
			
			_next_step[(p->x + p->y * sirina)] = 0;
			
			
			p = p->parent;
		}
	}

}
//switchtime 0.3
//dt = cloclk.restart.asseconds
//total time = += dt
void algoritam::Astar()
{
	for (int i = 0; i < sirina; i++)
	{
		for (int j = 0; j < visina; j++)
		{
			tocke[i + j * sirina].posjecen = false;
			tocke[i + j * sirina].globalGoal = 9999;
			tocke[i + j * sirina].localGoal = 9999;
			tocke[i + j * sirina].parent = nullptr;
		}
	}

	Tocka* sadasnja = cilj;
	cilj->localGoal = 0.0f;
	cilj->globalGoal = udaljenost(pocetak, cilj);

	list<Tocka*> listaNeProvjerenih;
	listaNeProvjerenih.push_back(cilj);

	while (!listaNeProvjerenih.empty())
	{
		listaNeProvjerenih.sort([](const Tocka* lhs, const Tocka* rhs) {
			return lhs->globalGoal < rhs->globalGoal;
			});

		while (!listaNeProvjerenih.empty() && listaNeProvjerenih.front()->posjecen)
		{
			listaNeProvjerenih.pop_front();
		}
		if (listaNeProvjerenih.empty())
		{
			break;
		}

		sadasnja = listaNeProvjerenih.front();
		sadasnja->posjecen = true;

		for (auto ITsusjed : sadasnja->vecSusjedi)
		{
			if (!ITsusjed->posjecen && ITsusjed->prepreka == 0)
			{
				listaNeProvjerenih.push_back(ITsusjed);
			}

			float moguceKraciPut = sadasnja->localGoal + udaljenost(sadasnja, ITsusjed);

			if (moguceKraciPut < ITsusjed->localGoal)
			{
				ITsusjed->parent = sadasnja;
				ITsusjed->localGoal = moguceKraciPut;

				ITsusjed->globalGoal = ITsusjed->localGoal + udaljenost(ITsusjed, pocetak);
			}

		}
	}
}
