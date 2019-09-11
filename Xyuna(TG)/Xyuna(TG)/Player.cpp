#include "stdafx.h"
#include "Player.h"


Player::Player(int number_of_cells, Texture *imag, Texture *png)
{
	//------Обнуление инвенторя------------------------------------------------------------------------------------
	inv = new item[number_of_things];
	for (int i = 0; i < number_of_things; i++)
	{
		inv[i].att = 0;
		inv[i].def = 0;
		inv[i].hp = 0;
		inv[i].element = 0;
		inv[i].name = "";
		inv[i].tip = 0;
		inv[i].number = 0;
		inv[i].set_ikon(png, 6, 25);
		inv[i].coordinate[0] = 548 + ((i % 4) * 32);
		inv[i].coordinate[1] = 155 + ((i / 4) * 32);
		inv[i].ikon.setPosition(inv[i].coordinate[0], inv[i].coordinate[1]);
	}
	//-------------------------------------------------------------------------------------------------------
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
	//------Обнуление обмундирования------------------------------------------------------------------------------------
	equipment = new item[amount_of_equipment];
	for (int i = 0; i < amount_of_equipment; i++)
	{
		equipment[i].att = 0;
		equipment[i].def = 0;
		equipment[i].hp = 0;
		equipment[i].element = 0;
		equipment[i].name = "";
		equipment[i].tip = 0;
		equipment[i].number = 0;
		equipment[i].set_ikon(png, 6, 25);
		equipment[i].coordinate[0] = 77;
		equipment[i].coordinate[1] = 48 + (i * 32);
		equipment[i].ikon.setPosition(equipment[i].coordinate[0], equipment[i].coordinate[1]);
	}
	//--------------------------------------------------------------------------------------------------------

	//------Обнуление дерева скилов------------------------------------------------------------------------------------
	the_skill_tree = new cell_skil[number_of_cells];
	for (int i = 0; i < number_of_cells; i++)
	{
		the_skill_tree[i].att = 0;
		the_skill_tree[i].def = 0;
		the_skill_tree[i].name = "";
		the_skill_tree[i].need_points_for_pumping = 0;
		the_skill_tree[i].moves_to_recharge = 0;
		the_skill_tree[i].set_ikon(png, 6, 25);
		the_skill_tree[i].coordinate[0] = (i / 4) * 32;
		the_skill_tree[i].coordinate[1] = 25 + ((i % 4) * 32);
		the_skill_tree[i].ikon.setPosition(the_skill_tree[i].coordinate[0], the_skill_tree[i].coordinate[1]);
		the_skill_tree[i].pumped = false;
	}
	//--------------------------------------------------------------------------------------------------------
	the_skill_tree_null.att = 0;
	the_skill_tree_null.def = 0;
	the_skill_tree_null.need_points_for_pumping = 0;
	the_skill_tree_null.name = "";
	the_skill_tree_null.moves_to_recharge = 0;
	the_skill_tree_null.pumped = true;

	//------Обнуление активных навыков--------------------------------------------------------------------------------------------------
	the_fight_activ_skills = new cell_skil[amount_of_active_skills];
	for (int i = 0; i < amount_of_active_skills; i++)
	{
		the_fight_activ_skills[i] = the_skill_tree_null;
		the_fight_activ_skills[i].pumped = false;
		the_fight_activ_skills[i].set_ikon(png, 6, 25);
		the_fight_activ_skills[i].coordinate[0] = 71 + (32 * i);
		the_fight_activ_skills[i].coordinate[1] = 300;
		the_fight_activ_skills[i].ikon.setPosition(the_fight_activ_skills[i].coordinate[0], the_fight_activ_skills[i].coordinate[1]);
	}
	//--------------------------------------------------------------------------------------------------------

	for (int i = 0; i < amount_of_active_skills; i++)
		Go[i] = 0;

	for (int i = 0; i < scholl_element; i++)
		scholl[i] = pass_scholl;
	//------Назначение основных характиристик------------------------------------------------------------------------------------
	name = "          ";
	lvl = 1; att = 1; def = 1;
	xp = 0; xp_up_lvl = 10;
	hp = 100; pumping_points = 1;
	GP = '@';
	inv_graf.setTexture(*imag);
	open_inv_ = false;
	open_fight_ = false;
	open_tree_ = false;
	schet = 0; fight_bot = 0;
	lvl_map = begin_lvl; lvl_up_map = false;
	//------------------------------------------------------------------------------------------------------
}

void Player::null_user(int number_of_cells, Texture *imag, Texture *png)
{
	//------Обнуление инвенторя------------------------------------------------------------------------------------
	inv = new item[number_of_things];
	for (int i = 0; i < number_of_things; i++)
	{
		inv[i].att = 0;
		inv[i].def = 0;
		inv[i].hp = 0;
		inv[i].element = 0;
		inv[i].name = "";
		inv[i].tip = 0;
		inv[i].number = 0;
		inv[i].set_ikon(png, 6, 25);
		inv[i].coordinate[0] = 548 + ((i % 4) * 32);
		inv[i].coordinate[1] = 155 + ((i / 4) * 32);
		inv[i].ikon.setPosition(inv[i].coordinate[0], inv[i].coordinate[1]);
	}
	//-------------------------------------------------------------------------------------------------------
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
	//------Обнуление обмундирования------------------------------------------------------------------------------------
	equipment = new item[amount_of_equipment];
	for (int i = 0; i < amount_of_equipment; i++)
	{
		equipment[i].att = 0;
		equipment[i].def = 0;
		equipment[i].hp = 0;
		equipment[i].element = 0;
		equipment[i].name = "";
		equipment[i].tip = 0;
		equipment[i].number = 0;
		equipment[i].set_ikon(png, 6, 25);
		equipment[i].coordinate[0] = 77;
		equipment[i].coordinate[1] = 48 + (i * 32);
		equipment[i].ikon.setPosition(equipment[i].coordinate[0], equipment[i].coordinate[1]);
	}
	//--------------------------------------------------------------------------------------------------------

	//------Обнуление дерева скилов------------------------------------------------------------------------------------
	the_skill_tree = new cell_skil[number_of_cells];
	for (int i = 0; i < number_of_cells; i++)
	{
		the_skill_tree[i].att = 0;
		the_skill_tree[i].def = 0;
		the_skill_tree[i].name = "";
		the_skill_tree[i].need_points_for_pumping = 0;
		the_skill_tree[i].moves_to_recharge = 0;
		the_skill_tree[i].set_ikon(png, 6, 25);
		the_skill_tree[i].coordinate[0] = (i / 4) * 32;
		the_skill_tree[i].coordinate[1] = 25 + ((i % 4) * 32);
		the_skill_tree[i].ikon.setPosition(the_skill_tree[i].coordinate[0], the_skill_tree[i].coordinate[1]);
		the_skill_tree[i].pumped = false;
	}
	//--------------------------------------------------------------------------------------------------------
	the_skill_tree_null.att = 0;
	the_skill_tree_null.def = 0;
	the_skill_tree_null.need_points_for_pumping = 0;
	the_skill_tree_null.name = "";
	the_skill_tree_null.moves_to_recharge = 0;
	the_skill_tree_null.pumped = true;

	//------Обнуление активных навыков--------------------------------------------------------------------------------------------------
	the_fight_activ_skills = new cell_skil[amount_of_active_skills];
	for (int i = 0; i < amount_of_active_skills; i++)
	{
		the_fight_activ_skills[i] = the_skill_tree_null;
		the_fight_activ_skills[i].pumped = false;
		the_fight_activ_skills[i].set_ikon(png, 6, 25);
		the_fight_activ_skills[i].coordinate[0] = 71 + (32 * i);
		the_fight_activ_skills[i].coordinate[1] = 300;
		the_fight_activ_skills[i].ikon.setPosition(the_fight_activ_skills[i].coordinate[0], the_fight_activ_skills[i].coordinate[1]);
	}
	//--------------------------------------------------------------------------------------------------------

	for (int i = 0; i < amount_of_active_skills; i++)
		Go[i] = 0;

	for (int i = 0; i < scholl_element; i++)
		scholl[i] = pass_scholl;
	//------Назначение основных характиристик------------------------------------------------------------------------------------
	lvl = 1; att = 1; def = 1;
	xp = 0; xp_up_lvl = 10;
	hp = 100; pumping_points = 1;
	GP = '@';
	inv_graf.setTexture(*imag);
	open_inv_ = false;
	open_fight_ = false;
	open_tree_ = false;
	schet = 0; fight_bot = 0;
	lvl_map = begin_lvl; lvl_up_map = false;
	//------------------------------------------------------------------------------------------------------
}

void Player::skill_tree_null(int number_of_cells, Texture *png)
{
	//------Обнуление дерева скилов------------------------------------------------------------------------------------
	the_skill_tree = new cell_skil[number_of_cells];
	for (int i = 0; i < number_of_cells; i++)
	{
		the_skill_tree[i].att = 0;
		the_skill_tree[i].def = 0;
		the_skill_tree[i].name = "";
		the_skill_tree[i].need_points_for_pumping = 0;
		the_skill_tree[i].moves_to_recharge = 0;
		the_skill_tree[i].set_ikon(png, 6, 25);
		the_skill_tree[i].coordinate[0] = (i / 4) * 32;
		the_skill_tree[i].coordinate[1] = 25 + ((i % 4) * 32);
		the_skill_tree[i].ikon.setPosition(the_skill_tree[i].coordinate[0], the_skill_tree[i].coordinate[1]);
		the_skill_tree[i].pumped = false;
	}
	//--------------------------------------------------------------------------------------------------------
	the_skill_tree_null.att = 0;
	the_skill_tree_null.def = 0;
	the_skill_tree_null.need_points_for_pumping = 0;
	the_skill_tree_null.name = "";
	the_skill_tree_null.moves_to_recharge = 0;
	the_skill_tree_null.pumped = true;
}

void Player::set_ikon(Texture *imag, int x, int y)
{
	ikon.setTexture(*imag);
	int x_y[2];
	x_y[0] = (x * 32);
	x_y[1] = (y * 32);
	ikon.setTextureRect(IntRect(x_y[0], x_y[1], 31, 31));
	x_y[0] = ((coordinate[1]) * 32);
	x_y[1] = ((coordinate[0]) * 32);
	ikon.setPosition(x_y[0], x_y[1]);
}

void Player::open_inv()
{
	open_inv_ = true;
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{ 
		{ if (open_inv_) open_inv_ = false; scholl[5] = 1; return; };
	}
	scholl[2] = 1;
	
	int co[2];
	char* name_ = new char[80];
	int tip = 0;
		for (int id = 0; id<number_of_things; id++)
		if ((pos.x >= inv[id].coordinate[0]) && (pos.x <= inv[id].coordinate[0] + 31))
			if ((pos.y >= inv[id].coordinate[1]) && (pos.y <= inv[id].coordinate[1] + 31))	
		{ 
				for (int i = 0; i < number_of_things; i++)
					inv[i].ikon.setColor(Color::White);
				inv[id].ikon.setColor(Color::Green);
				scholl[3] = 1;
				if (Keyboard::isKeyPressed(Keyboard::P))
				{
					if ((inv[id].tip > 0) && (inv[id].tip < 110) && (inv[id].tip != 10))
					{
						scholl[4] = 1;
						inv[id].tip--;
						att = att - equipment[inv[id].tip].att;
						def = def - equipment[inv[id].tip].def;

						name_ = equipment[inv[id].tip].name;
						equipment[inv[id].tip].name = inv[id].name;
						inv[id].name = name_;

						co[0] = equipment[inv[id].tip].coordinate_[0];
						co[1] = equipment[inv[id].tip].coordinate_[1];
						equipment[inv[id].tip].coordinate_[0] = inv[id].coordinate_[0];
						equipment[inv[id].tip].coordinate_[1] = inv[id].coordinate_[1];
						inv[id].coordinate_[0] = co[0];
						inv[id].coordinate_[1] = co[1];

						co[0] = equipment[inv[id].tip].att;
						co[1] = equipment[inv[id].tip].def;
						equipment[inv[id].tip].att = inv[id].att;
						equipment[inv[id].tip].def = inv[id].def;
						inv[id].att = co[0];
						inv[id].def = co[1];

						co[0] = equipment[inv[id].tip].tip;
						co[1] = equipment[inv[id].tip].element;
						equipment[inv[id].tip].tip = inv[id].tip;
						equipment[inv[id].tip].element = inv[id].element;
						inv[id].element = co[1];
						co[1] = co[0];
						co[0] = inv[id].tip;
						inv[id].tip = co[1];

						att = att + equipment[co[0]].att;
						def = def + equipment[co[0]].def;
						inv[id].ikon.setColor(Color::White);
						equipment[co[0]].ikon.setColor(Color::White);
						equipment[co[0]].set_ikon();
						inv[id].set_ikon();
						pos.x = 0; pos.y = 0;
						equipment[inv[id].tip].tip++;
					}
					else
					if (schet == 0)
					{
						health_potion();
						schet++;
					}
				}

		}
			

}

void Player::delete_item(Texture *png)
{
	for (int i = 0; i < 16; i++)
	{
		if (inv[i].ikon.getColor() == Color::Green)
		{
			inv[i] = inv_null;
			inv[i].set_ikon(png, 6, 25);
			inv[i].coordinate[0] = 548 + ((i % 4) * 32);
			inv[i].coordinate[1] = 155 + ((i / 4) * 32);
			inv[i].ikon.setPosition(inv_null.coordinate[0], inv_null.coordinate[1]);
		}
	}
}

void Player::course(char** world, int tree)
{
	world[coordinate[0]][coordinate[1]] = ' ';
	if (schet == 0)
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			{ if ((world[coordinate[0] - 1][coordinate[1]] == ' ') || (world[coordinate[0] - 1][coordinate[1]] == 'd')) { coordinate[0]--; schet++; } scholl[0] = 1; };
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			{ if ((world[coordinate[0] + 1][coordinate[1]] == ' ') || (world[coordinate[0] + 1][coordinate[1]] == 'd')) { coordinate[0]++; schet++; } scholl[0] = 1; };
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			{ if ((world[coordinate[0]][coordinate[1] - 1] == ' ') || (world[coordinate[0]][coordinate[1] - 1] == 'd')) { coordinate[1]--; schet++; } scholl[0] = 1; };
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			{ if ((world[coordinate[0]][coordinate[1] + 1] == ' ') || (world[coordinate[0]][coordinate[1] + 1] == 'd')) { coordinate[1]++; schet++; } scholl[0] = 1; };
		}
		if (Keyboard::isKeyPressed(Keyboard::I))
		{
			if(!open_tree_) { open_inv(); schet++; };
		}
		if (Keyboard::isKeyPressed(Keyboard::K))
		{
			if (!open_inv_){ open_the_skill_tree(tree); schet++; }
		}
	}
	world[coordinate[0]][coordinate[1]] = GP;
}

void Player::characteristic()
{
	/*cout << "Жизни: " << hp << endl;
	cout << "Атака: " << att << endl;
	cout << "Защита: " << def << endl;
	cout << "Уровень: " << lvl << endl;
	cout << "Опыт " << xp << " из "<< xp_up_lvl << endl;*/

}

void Player::lvl_up()
{
	if (xp >= xp_up_lvl)
	{
		lvl++;
		pumping_points++;
		xp = xp - xp_up_lvl;
	}
}

void Player::characteristic_show(int x, int y, char* name_, int znach)
{
	PSS.str("");
	txt.setCharacterSize(20);
	PSS << znach;
	txt.setString(name_ + PSS.str());
	txt.setPosition(x, y);
}

void Player::characteristic_show(int x, int y, char* name_, float znach)
{
	PSS.str("");
	txt.setCharacterSize(20);
	PSS << znach;
	txt.setString(name_ + PSS.str());
	txt.setPosition(x, y);
}

void Player::characteristic_show(int x, int y, char* name_, int znach1, char* znach2, int znach3)
{
	PSS.str("");
	txt.setCharacterSize(20);
	PSS << znach1;
	PSS << znach2;
	PSS << znach3;
	txt.setString(name_ + PSS.str());
	txt.setPosition(x, y);
}

void Player::characteristic_show(int x, int y, char* name_, char* znach)
{
	PSS.str("");
	txt.setCharacterSize(20);
	PSS << znach;
	txt.setString(name_ + PSS.str());
	txt.setPosition(x, y);
}

void Player::characteristic_show(int x, int y, int name_, char* znach)
{
	PSS.str("");
	txt.setCharacterSize(20);
	PSS << name_;
	PSS << znach;
	txt.setString(PSS.str());
	txt.setPosition(x, y);
}

void Player::labal_show(int x, int y, char* str)
{
	PSS.str("");
	txt.setCharacterSize(20);
	txt.setString(str);
	txt.setPosition(x, y);
}

void Player::labal_show(int x, int y, int str)
{
	PSS.str("");
	txt.setCharacterSize(20);
	PSS << str;
	txt.setString(PSS.str());
	txt.setPosition(x, y);
}

void Player::labal_show(int x, int y, String str)
{
	PSS.str("");
	txt.setCharacterSize(20);
	txt.setString(str);
	txt.setPosition(x, y);
}

void Player::health_potion()
{
	for (int i = 0; i < number_of_things; i++)
	{
		if (hp < max_hp)
		{
			if ((inv[i].tip == 110))
			{
				hp = hp + inv[i].hp;
				inv[i] = inv_null;
				inv[i].coordinate[0] = 548 + ((i % 4) * 32);
				inv[i].coordinate[1] = 155 + ((i / 4) * 32);
				inv[i].ikon.setPosition(inv[i].coordinate[0], inv[i].coordinate[1]);
				if (hp > max_hp)
					hp = max_hp;
				return;
			}
		}
	}
}

void Player::number_health_point()
{
	for (int i = 0; i < number_of_things; i++)
	{
		if ((inv[i].tip == 110) && (inv[i].number > 0))
		{
			PSS.str("");
			PSS << inv[i].number;
			txt.setString(PSS.str());
			txt.setCharacterSize(15);
			txt.setPosition(inv[i].coordinate[0],inv[i].coordinate[1] + 15);
		}
	}
}

void Player::fight(bot &bot_, char** world)
{ 
	bool atak_bots = false;
	scholl[11] = 1;
	int dop_att = 0;
	open_fight_ = true;
	int active_skill = amount_of_active_skills + 5;

	for (int i = 0; i < amount_of_equipment; i++)
	{
		if ((hp <= ((hp / 100) * 40)) && (equipment[i].tip = 1))
		{
			dop_att = att + ((att / 100) * 35);
		}
	}

	//------Сам бой----------------------------------------------------------------------------------------
	if (schet == 0)
	{
		if ((Keyboard::isKeyPressed(Keyboard::Q)) && (!atak_bots))
		{
			bot_.hp = bot_.hp - att - (bot_.def / 10) + dop_att;
			scholl[12] = 1;
			schet++; atak_bots = true;
		}

		if ((Keyboard::isKeyPressed(Keyboard::W)) && (!atak_bots))
		{
			active_skill = 0;
		}

		if ((Keyboard::isKeyPressed(Keyboard::E)) && (!atak_bots))
		{
			active_skill = 1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::R)) && (!atak_bots))
		{
			active_skill = 2;
		}

		if ((Keyboard::isKeyPressed(Keyboard::T)) && (!atak_bots))
		{
			active_skill = 3;
		}

		if (active_skill < amount_of_active_skills)
		{
			if (Go[active_skill] >= the_fight_activ_skills[active_skill].moves_to_recharge)
			{
				scholl[13] = 1;
				if (the_fight_activ_skills[active_skill].att != 0)
				{
					bot_.hp = bot_.hp - the_fight_activ_skills[active_skill].att + -(bot_.def / 10) + dop_att;
				}

				if (the_fight_activ_skills[active_skill].hp != 0)
				{
					hp = hp + the_fight_activ_skills[active_skill].hp;
				}

				if (the_fight_activ_skills[active_skill].def != 0)
				{
					def = def + the_fight_activ_skills[active_skill].def;
					down_def = 0;
				}

				schet++; atak_bots = true; Go[active_skill] = 0;
			}
		}

		if (down_def == 3)
		{
			def = def - the_fight_activ_skills[0].def;
		}

		if (atak_bots)
		{
			hp = hp - bot_.att - (def / 10);
			atak_bots = false; Go[0]++;
			Go[1]++; Go[2]++; Go[3]++;
			down_def++;
		}
		deat_player();
	}
	//-----------------------------------------------------------------------------------------------------
	int coor[2];
	//------После смерти бота------------------------------------------------------------------------------------
	if ((bot_.hp <= 0) && (bot_.coordinate[0] > 0))
	{
		if ((bot_.GP != 'D')/* || (bot_.GP != 'd')*/)
		if (bot_.GP != 'd')
		if ((bot_.element < 6) || (bot_.element == 8))
		{
			world[bot_.coordinate[0]][bot_.coordinate[1]] = ' ';
			bot_.deat();
			bool hp_chek;
			xp = xp + bot_.xp;
			for (int i = 0; i < number_of_things; i++)
			{
				{
					if ((inv[i].name == ""))
					{
						coor[0] = inv[i].coordinate[0];
						coor[1] = inv[i].coordinate[1];
						inv[i] = bot_.inv[0];
						inv[i].coordinate[0] = coor[0];
						inv[i].coordinate[1] = coor[1];
						inv[i].set_ikon();
						open_fight_ = false;

						scholl[1] = 1;

						return;
					}
					/*if ((inv[i].name != "") && (i == 15))
						cout << "Ваш инвентарь полон" << endl;*/
				}
			}
		}

		if ((bot_.element == 6) || (bot_.element == 7))
		{
			bot_.vize = true;
		}

		if (bot_.GP == 'D')
		{
			for (int i = 0;i<number_of_things;i++)
				if (inv[i].tip == 10)
				{
					bot_.GP = 'd';
					inv[i] = inv_null;
					inv[i].coordinate[0] = 548 + ((i % 4) * 32);
					inv[i].coordinate[1] = 155 + ((i / 4) * 32);
					inv[i].ikon.setPosition(inv[i].coordinate[0], inv[i].coordinate[1]);
					bot_.ikon.setTextureRect(sf::IntRect(96, 800, 32, 32));
					world[bot_.coordinate[0]][bot_.coordinate[1]] = 'd';
					open_fight_ = false;
					return;
				}
		}
		open_fight_ = false;
	}
	//---------------------------------------------------------------------------------------------------------
}

void Player::search_for_enemies(int number_items, char** world, bot* bots)
{
	for (int i = 0; i < number_items; i++)
	{
		bots[i].vize = false;
		for (int x = -1; x < 2; x++)
		for (int y = -1; y < 2; y++)
		if ((coordinate[0] + x == bots[i].coordinate[0]) && (coordinate[1] + y == bots[i].coordinate[1]))
		{
			fight_bot = i;
			if (bots[fight_bot].element == 8)
			{
				if (Keyboard::isKeyPressed(Keyboard::E))
				{
					fight(bots[fight_bot], world);
				}
			}
			else
			{
				fight(bots[fight_bot], world);
			}
		}
	}
}

void Player::open_the_skill_tree(int tree)
{
	int id=0;
	open_tree_ = true;
	scholl[7] = 1;
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{ 
		{ if (open_tree_) open_tree_ = false; scholl[10] = 1; return; };
	}
	for (int id = 0; id<tree; id++)
	if ((pos.x >= the_skill_tree[id].coordinate[0]) && (pos.x <= the_skill_tree[id].coordinate[0] + 31))
	if ((pos.y >= the_skill_tree[id].coordinate[1]) && (pos.y <= the_skill_tree[id].coordinate[1] + 31))
	{
		for (int i = 0; i < tree; i++)
			the_skill_tree[i].ikon.setColor(Color::White);
		the_skill_tree[id].ikon.setColor(Color::Green);
		scholl[8] = 1;
		if (Keyboard::isKeyPressed(Keyboard::P))
		{
			scholl[9] = 1;
			if (!the_skill_tree[id].activ)
			{
				if (pumping_points >= the_skill_tree[id].need_points_for_pumping)
				{
					if (!the_skill_tree[id].pumped)
					{
						pumping_points = pumping_points - the_skill_tree[id].need_points_for_pumping;
						the_skill_tree[id].pumped = true;
						att = att + the_skill_tree[id].att;
						def = def + the_skill_tree[id].def;
						max_hp = max_hp + the_skill_tree[id].hp;
					}
				}
			}
			else
			{
				if (pumping_points >= the_skill_tree[id].need_points_for_pumping)
				{
					if (!the_skill_tree[id].pumped)
					{
						pumping_points = pumping_points - the_skill_tree[id].need_points_for_pumping;
						the_skill_tree[id].pumped = true;
						for (int i = 0; i < amount_of_active_skills; i++)
						{
							if (the_fight_activ_skills[i].name == "")
							{
								the_fight_activ_skills[i] = the_skill_tree[id];
								the_fight_activ_skills[i].coordinate[0] = 71 + (32 * i);
								the_fight_activ_skills[i].coordinate[1] = 300;
								the_fight_activ_skills[i].ikon.setPosition(the_fight_activ_skills[i].coordinate[0], the_fight_activ_skills[i].coordinate[1]);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void Player::deat_player()
{
	if (hp <= 0)
	{
		labal_show(100,20,"Вы умерли");
	}
}

void Player::down_hp()
{
	max_hp = max_hp - ((max_hp / 100) * 19);
}

Player::~Player()
{
	delete[] inv;
	delete[] equipment;
}
