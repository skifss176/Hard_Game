#pragma once
#include "item.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int number_of_things_ = 1;   //кол-во ячеек в инвентаре

class bot
{
public:
	//жизни
	float hp;		 
	//иконка
	char GP;	
	//
	item inv_null;
	//защита
	float def;	
	//иконка граф
	Sprite ikon;
	//
	char** stori;
	int number_stori;
	//
	bool vize;
	//атака
	float att;	   	  
	//уровень
	int lvl;
	//инвентарь
	item* inv;		  
	//координаты
	int coordinate[2];
	//стихия бота
	int element;	  
	//опыт c бота
	float xp;		 
	//имя бота
	char* name;		  
	bot();
	//
	void item_null_create(Texture *png);
	//При смерти удаляет бота
	void deat();
	//
	void set_ikon(Texture *imag, int x, int y);
	//Во время боя выводит характиристики
	void characteristic();
	//Рандомные предметы
	void random_item(item* items);
	//
	void hard_bust(float hard);
	//
	~bot();
};

