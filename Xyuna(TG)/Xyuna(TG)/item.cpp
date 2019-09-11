#include "stdafx.h"
#include "item.h"


item::item()
{
	name = new char[80];
}

void item::set_ikon(Texture *imag, int x, int y)
{
	ikon.setTexture(*imag);
	int x_y[2];
	x_y[0] = (x * 32);
	x_y[1] = (y * 32);
	coordinate_[0] = x_y[0];
	coordinate_[1] = x_y[1];
	ikon.setTextureRect(IntRect(coordinate_[0], coordinate_[1], 31, 31));
	//ikon.setPosition(x, y);
}

void item::set_ikon()
{
	ikon.setTextureRect(IntRect(coordinate_[0], coordinate_[1], 31, 31));
	ikon.setPosition(coordinate[0], coordinate[1]);
	//ikon.setPosition(x, y);
}

item::~item()
{
	delete[] name;
}
