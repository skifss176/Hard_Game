#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//класс вещей
class item
{
public:
	//защита от вещи
	float def;	
	//атака от вещи
	float att;		
	//
	int number_mass;
	//
	int hp;
	//имя вещи
	char* name;
	//иконка граф
	Sprite ikon;
	//
	int coordinate[2];
	//
	int number;
	//
	int coordinate_[2];
	//стихия вещи
	//(0 - нет, 1 - воздух, 2 - земля, 3 - вода, 4 - огонь)
	int element; 
	//Тип вещи
	//(110 - зелья, 1 - шлемы, 2 - нагрудники, 3- перчатки,  4 - наплечники,
	//5 - кольца, 7 - оружие(одно ручное), 8 - оружие(двух ручное), 9 - шиты, 10 - ключи)
	int tip;	
	item();
	//
	void set_ikon(Texture *imag, int x, int y);
	void set_ikon();
	//
	~item();
};

