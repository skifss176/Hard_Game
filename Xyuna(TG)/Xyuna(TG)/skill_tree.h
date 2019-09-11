#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class cell_skil
{
public:
	//матери
	cell_skil* mother;
	//Дети
	cell_skil* children;
	//Имя
	char* name;
	//жизни
	float hp;
	//иконка граф
	Sprite ikon;
	//
	int coordinate[2];
	//защита
	float def;
	//атака
	float att;
	//
	int moves_to_recharge;
	//очков надо для прокачки
	int need_points_for_pumping;
	//прокачен ли скилл
	bool pumped;
	//активный навык или нет
	bool activ;
	cell_skil();
	//
	void set_ikon(Texture *imag, int x, int y);
	void number_of_mothers(int mother_);
	void number_of_children(int children_);
	~cell_skil();
};

