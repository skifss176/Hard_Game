#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
//����� �����
class item
{
public:
	//������ �� ����
	float def;	
	//����� �� ����
	float att;		
	//
	int number_mass;
	//
	int hp;
	//��� ����
	char* name;
	//������ ����
	Sprite ikon;
	//
	int coordinate[2];
	//
	int number;
	//
	int coordinate_[2];
	//������ ����
	//(0 - ���, 1 - ������, 2 - �����, 3 - ����, 4 - �����)
	int element; 
	//��� ����
	//(110 - �����, 1 - �����, 2 - ����������, 3- ��������,  4 - ����������,
	//5 - ������, 7 - ������(���� ������), 8 - ������(���� ������), 9 - ����, 10 - �����)
	int tip;	
	item();
	//
	void set_ikon(Texture *imag, int x, int y);
	void set_ikon();
	//
	~item();
};

