#pragma once
#include "item.h"
#include "bot.h"
#include "skill_tree.h"
#include <windows.h> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
using namespace std;
using namespace sf;

//константа

//кол-во €чеек в инвентаре
const int number_of_things = 16; 
//кол-во €чеек дл€ брони и оружи€
const int amount_of_equipment = 8; 
//кол-во €чеек дл€ активных навыков
const int amount_of_active_skills = 4;
//начальный уровень
const int begin_lvl = 3;
//”роков в обучении
const int scholl_element = 15;


//ѕропустить обучение(0 - нет)(1 - да)
const bool pass_scholl = false;

//класс игрока
class Player
{
public:
	Vector2f pos;
	item null;
	Clock clock;
	//жизни
	float hp;	
	float max_hp;
	//им€
	string name;
	int name_sim;
	//
	string name_class;
	//иконка
	char GP;	
	//
	int Go[amount_of_active_skills];
	//
	int down_def;
	//иконка граф
	Sprite ikon;
	//
	Sprite inv_graf;
	//защита
	float def;
	//
	int lvl_map;
	//атака
	float att;	   	 
	//уровень
	int lvl;	
	//очки прокачки
	int pumping_points;
	//опыт
	float xp;	
	//
	ostringstream PSS;
	//
	bool lvl_up_map;
	//
	int scholl[scholl_element];
	//
	bool open_inv_;
	bool open_fight_;
	bool open_tree_;
	int fight_bot;
	//
	Text txt;
	int schet;
	//опыт до следущего уровн€
	int xp_up_lvl;    
	//инвентарь
	item* inv;		
	item inv_null;
	//ƒерево прокачки
	cell_skil* the_skill_tree;
	//Ќулева€ мать
	cell_skil the_skill_tree_null;
	//
	cell_skil* the_fight_activ_skills;
	//снар€га
	item* equipment;  
	//координаты
	int coordinate[2];
	Player(int number_of_cells, Texture *imag, Texture *png);
	//открытие инвентор€
	void open_inv();
	void delete_item(Texture *png);
	//
	void set_ikon(Texture *imag, int x,int y);
	//ƒерево прокачки
	void open_the_skill_tree(int tree);
	//’од
	void course(char** world, int tree);
	//бой с ботами
	void fight(bot &bot_, char** world);
	//¬ывод харов во врем€ игры
	void characteristic();
	//проверка есть ли враг р€дом
	void search_for_enemies(int number_items, char** world, bot* bots);
	//вывод хар
	void characteristic_show(int x, int y, char* name_, int znach);
	void characteristic_show(int x, int y, char* name_, char* znach);
	void characteristic_show(int x, int y, char* name_, int znach1, char* znach2, int znach3);
	void characteristic_show(int x, int y, char* name_, float znach);
	void characteristic_show(int x, int y, int name_, char* znach);
	//использование зелье€ хр
	void health_potion();
	//ненужны€ херн€
	void number_health_point();
	//
	void lvl_up();
	//смерть персонажа
	void deat_player();
	//
	void null_user(int number_of_cells, Texture *imag, Texture *png);
	void skill_tree_null(int number_of_cells, Texture *imag);
	//вывод надпесей
	void labal_show(int x, int y, char* str);
	void labal_show(int x, int y, int str);
	void labal_show(int x, int y, String str);
	//
	void down_hp();
	~Player();
};

