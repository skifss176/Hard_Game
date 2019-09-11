#include "stdafx.h"
#include "bot.h"


bot::bot()
{
	inv = new item[number_of_things_];
	for (int i = 0; i < number_of_things_; i++)
	{
		inv[i].att = 0;
		inv[i].def = 0;
		inv[i].element = 0;
		inv[i].name = "";
		inv[i].tip = 0;
	}

	stori = new char*[10];
	for (int i = 0; i < 10; i++)
		stori[i] = new char[41];

	name = new char[80];
	xp = 0; att = 0;
	element = 0;
	vize = false;
	lvl = 0; def = 0;
	hp = 0;
}

void bot::item_null_create(Texture *png)
{
	inv_null.att = 0;
	inv_null.def = 0;
	inv_null.hp = 0;
	inv_null.element = 0;
	inv_null.name = "";
	inv_null.tip = 0;
	inv_null.number = 0;
	inv_null.set_ikon(png, 6, 25);
	inv_null.coordinate[0] = 548 + ((1 % 4) * 32);
	inv_null.coordinate[1] = 155 + ((1 / 4) * 32);
	inv_null.ikon.setPosition(inv_null.coordinate[0], inv_null.coordinate[1]);
}

void bot::deat()
{
	coordinate[0] = -1000000000;
	coordinate[1] = -1000000000;
}

void bot::characteristic()
{
	cout << "Жизни: " << hp << endl;
	cout << "Атака: " << att << endl;
	cout << "Защита: " << def << endl;
	cout << "Уровень: " << lvl << endl;
	cout << "Опыт " << xp << endl;
}

void bot::random_item(item* items)
{
	 int i;
	 if ((element <= 5) || (element == 8))
	 {
		 i = (rand() % (items[0].number_mass)) + 1;

		 if (i == 2) i = 3;

		 inv[0] = items[i - 1];

		 if (element == 5)
		 {
			 for (int i = 0; i<items[0].number_mass; i++)
			 if (items[i].tip == 10)
				 inv[0] = items[i];
		 }
	 }
	 else
	 {
		 inv[0] = inv_null;
	 }

}

void bot::set_ikon(Texture *imag, int x, int y)
{
	ikon.setTexture(*imag);
	int x_y[2];
	x_y[0] = (x * 32);
	x_y[1] = (y * 32);
	ikon.setTextureRect(IntRect(x_y[0], x_y[1], 31, 31));
	//ikon.setPosition(x, y);
}

void bot::hard_bust(float hard)
{
	xp  =xp * hard;
	att =att * hard;
	def =def * hard;
	hp =hp * hard;
}

bot::~bot()
{
	delete[] inv;
	delete[] name;
}
