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

//���������

//���-�� ����� � ���������
const int number_of_things = 16; 
//���-�� ����� ��� ����� � ������
const int amount_of_equipment = 8; 
//���-�� ����� ��� �������� �������
const int amount_of_active_skills = 4;
//��������� �������
const int begin_lvl = 3;
//������ � ��������
const int scholl_element = 15;


//���������� ��������(0 - ���)(1 - ��)
const bool pass_scholl = false;

//����� ������
class Player
{
public:
	Vector2f pos;
	item null;
	Clock clock;
	//�����
	float hp;	
	float max_hp;
	//���
	string name;
	int name_sim;
	//
	string name_class;
	//������
	char GP;	
	//
	int Go[amount_of_active_skills];
	//
	int down_def;
	//������ ����
	Sprite ikon;
	//
	Sprite inv_graf;
	//������
	float def;
	//
	int lvl_map;
	//�����
	float att;	   	 
	//�������
	int lvl;	
	//���� ��������
	int pumping_points;
	//����
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
	//���� �� ��������� ������
	int xp_up_lvl;    
	//���������
	item* inv;		
	item inv_null;
	//������ ��������
	cell_skil* the_skill_tree;
	//������� ����
	cell_skil the_skill_tree_null;
	//
	cell_skil* the_fight_activ_skills;
	//�������
	item* equipment;  
	//����������
	int coordinate[2];
	Player(int number_of_cells, Texture *imag, Texture *png);
	//�������� ���������
	void open_inv();
	void delete_item(Texture *png);
	//
	void set_ikon(Texture *imag, int x,int y);
	//������ ��������
	void open_the_skill_tree(int tree);
	//���
	void course(char** world, int tree);
	//��� � ������
	void fight(bot &bot_, char** world);
	//����� ����� �� ����� ����
	void characteristic();
	//�������� ���� �� ���� �����
	void search_for_enemies(int number_items, char** world, bot* bots);
	//����� ���
	void characteristic_show(int x, int y, char* name_, int znach);
	void characteristic_show(int x, int y, char* name_, char* znach);
	void characteristic_show(int x, int y, char* name_, int znach1, char* znach2, int znach3);
	void characteristic_show(int x, int y, char* name_, float znach);
	void characteristic_show(int x, int y, int name_, char* znach);
	//������������� ������ ��
	void health_potion();
	//�������� �����
	void number_health_point();
	//
	void lvl_up();
	//������ ���������
	void deat_player();
	//
	void null_user(int number_of_cells, Texture *imag, Texture *png);
	void skill_tree_null(int number_of_cells, Texture *imag);
	//����� ��������
	void labal_show(int x, int y, char* str);
	void labal_show(int x, int y, int str);
	void labal_show(int x, int y, String str);
	//
	void down_hp();
	~Player();
};

