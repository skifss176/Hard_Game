#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class cell_skil
{
public:
	//������
	cell_skil* mother;
	//����
	cell_skil* children;
	//���
	char* name;
	//�����
	float hp;
	//������ ����
	Sprite ikon;
	//
	int coordinate[2];
	//������
	float def;
	//�����
	float att;
	//
	int moves_to_recharge;
	//����� ���� ��� ��������
	int need_points_for_pumping;
	//�������� �� �����
	bool pumped;
	//�������� ����� ��� ���
	bool activ;
	cell_skil();
	//
	void set_ikon(Texture *imag, int x, int y);
	void number_of_mothers(int mother_);
	void number_of_children(int children_);
	~cell_skil();
};

