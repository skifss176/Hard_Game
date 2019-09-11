#include "stdafx.h"
#include "skill_tree.h"


cell_skil::cell_skil()
{
	name = new char[80];
	pumped = false;
}

void cell_skil::number_of_mothers(int mother_)
{
	mother = new cell_skil[mother_];
}

void cell_skil::number_of_children(int children_)
{
	children = new cell_skil[children_];
}

void cell_skil::set_ikon(Texture *imag, int x, int y)
{
	ikon.setTexture(*imag);
	int x_y[2];
	x_y[0] = (x * 32);
	x_y[1] = (y * 32);
	ikon.setTextureRect(IntRect(x_y[0], x_y[1], 31, 31));
	//ikon.setPosition(x, y);
}

cell_skil::~cell_skil()
{
	delete[] name;
}
