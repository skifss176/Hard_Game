#pragma once
#include "item.h"
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int number_of_things_ = 1;   //���-�� ����� � ���������

class bot
{
public:
	//�����
	float hp;		 
	//������
	char GP;	
	//
	item inv_null;
	//������
	float def;	
	//������ ����
	Sprite ikon;
	//
	char** stori;
	int number_stori;
	//
	bool vize;
	//�����
	float att;	   	  
	//�������
	int lvl;
	//���������
	item* inv;		  
	//����������
	int coordinate[2];
	//������ ����
	int element;	  
	//���� c ����
	float xp;		 
	//��� ����
	char* name;		  
	bot();
	//
	void item_null_create(Texture *png);
	//��� ������ ������� ����
	void deat();
	//
	void set_ikon(Texture *imag, int x, int y);
	//�� ����� ��� ������� ��������������
	void characteristic();
	//��������� ��������
	void random_item(item* items);
	//
	void hard_bust(float hard);
	//
	~bot();
};

