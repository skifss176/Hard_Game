// Xyuna(TG).cpp: определяет точку входа для консольного приложения.
//

//подключение модулей
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "bot.h"
#include "item.h"
#include <ctime>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
using namespace sf;


//константы
const char module_file[80] = "information/module.txt";
const bool give_items = 1;
const char name_game[80] = "Hard_Game";
const int number_of_classes = 4;

//функции

//начальная загрузка
void initial_load(item* item_initial_load, char** world, Player &user, Texture *imag, char** world_language, int &tree);

//прогрузка мира
void level_load(char** world, Player &user, bot* bots_initial_load, Texture *imag, float &Hard);

//Выбор класса персонажа
bool class_selection(Player &user, RenderWindow &window, Event &event, Texture *imag);

//Прорисовка боя
void fight_show(Player &user, bot* bots, RenderWindow &window, char** world, char** world_language);

//Прорисовка инвентaря
void inv_show(Player &user, RenderWindow &window, char** world_language, Event &event, bool &down_button, Texture *png);

//Прорисовка дерева навыков
void tree_show(Player &user, RenderWindow &window, char** world_language, int tree);

//Прорисовка уровня
void lvl_show(Player &user, bot* bots, RenderWindow &window, char** world, int *qwerty, int *number_items, Sprite *world_image);

//Главное меню
int main_menu(RenderWindow &window, Player &user, Event &event, bool begin_game);

//Обзор версий
void version_review(RenderWindow &window, Player &user);

//Настройки
void settings(RenderWindow &window, Player &user, Event &event, bot *bots, int number_items, bool &down_button, bool &rand_lvl, float &Hard);

//Ввод имени
void create_name(Player &user, RenderWindow &window, Event &event, bool &down_button);

//Рандомная карта
void random_map_begin(int x, int y, int lvl_number);
void random_map(int schet, int x, int y, char** world);

//Создание кнопки
bool create_button(Player &user, RenderWindow &window, Event &event, bool &down_button, int x, int y, string txt);



void main()
{

	srand(time(0));//Установка рандома

	random_map_begin(1, 1, 3);
	random_map_begin(1, 1, 4);
	random_map_begin(1, 1, 5);
	random_map_begin(1, 1, 6);

	setlocale(LC_ALL, "rus");
	//------Кол-во различный переменных------------------------------------------------------------------------------------

	ifstream items_;//файл
	
	items_.open("information/items.txt");
	int number_items_ = 0;
	int number_items = 0;//кол-во вещей
	items_ >> number_items_;
	item* items = new item[number_items_];//массив вещей(общий)
	items_.close();

	Texture gif;//Текстура инвенторя
	gif.loadFromFile("information/inv_.gif");

	int tree = 1;//масив навыков

	Font font;//шрифт 
	font.loadFromFile("information/evochronfont2.ttf");

	Texture png;//Текстура общего спрайта
	png.loadFromFile("information/nethack.gif");
	Player user(tree, &gif, &png);

	ostringstream lvl_map_up;
	lvl_map_up << "information/world/lvl_";
	lvl_map_up << user.lvl_map;
	lvl_map_up << ".txt";
	items_.open(lvl_map_up.str());
	int* qwerty = new int [2];
	items_ >> qwerty[0];
	items_ >> qwerty[1];
	items_ >> number_items;
	items_ >> number_items;
	items_ >> number_items;
	bot* bots = new bot[number_items];//Враги
	items_.close();
	char** world = new char*[qwerty[0]];//Мир
	for (int i = 0; i < qwerty[0]; i++) { world[i] = new char[qwerty[1]]; }
	
	char** word_language;//Общий запас всех слов
	int language_world;
	items_.open("information/language_rus.txt");
	items_ >> language_world;
	items_.close();
	word_language = new char*[language_world];
	for (int i = 0; i < language_world; i++)
	{
		word_language[i] = new char[80];
	}

	Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый

	for (int i = 0; i < number_items_; i++)
	{
		items[i].number_mass = number_items_;
	}

	Sprite world_image;//Ячека мира
	world_image.setTexture(png);
	world_image.setTextureRect(IntRect(6 * 32, 25 * 32, 31, 31));

	Clock clock;//Время
	float time;//Время

	bool begin_game_ = false;
	int go_in_game = 10000000;

	Event event;//эвент(событие)

	//--------------------------------------------------------------------------------------------------------------

	RenderWindow window(sf::VideoMode(800, 576), name_game);//создание окна

	//--------Переменные для настроек-------------------------------------------------------------------------------------------------
	bool down_button_ = false;
	bool random_lvl = false;
	float hard = 1;

	bool down_button_key = false;
	//---------------------------------------------------------------------------------------------------------

	//---Окончательная прогрузка всего-----------------------------------------------------------------------------------------------------------
	initial_load(items, world, user, &png, word_language,tree);
	
	level_load(world, user, bots, &png,hard);

	user.set_ikon(&png, 0, 10);
	user.txt = text;
	//--------------------------------------------------------------------------------------------------------------

	//------Радномайзер предметов с врагов------------------------------------------------------------------------------------
	for (int i = 0; i < number_items; i++)
	{
		bots[i].item_null_create(&png);
		bots[i].random_item(items);
	}
	//----------------------------------------------------------------------------------------------------------
	if (give_items)
	{
		int* coor = new int[2];
		int* i = new int[1];
		i[0] = 0;
		coor[0] = user.inv[i[0]].coordinate[0];
		coor[1] = user.inv[i[0]].coordinate[1];
		user.inv[i[0]] = items[0];
		user.inv[i[0]].coordinate[0] = coor[0];
		user.inv[i[0]].coordinate[1] = coor[1];
		user.inv[i[0]].ikon.setPosition(user.inv[i[0]].coordinate[0], user.inv[i[0]].coordinate[1]);
		delete i;
		delete[] coor;
	}

	while (window.isOpen())
	{
		user.txt.setColor(Color::Red);

		time = clock.getElapsedTime().asMicroseconds();
		time = time / 500; //скорость игры

		if (time >= 405)
		{
			clock.restart(); //перезагружает время
			if (give_items) cout << time << "\n";//смотрим как живет время (перезагружается, как видим)
			user.schet = 0;
		}

		Event event;
		//дать прошедшее время в микросекунда
		user.clock = clock;
		//------При выполнении действия------------------------------------------------------------------------------------------------------
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
			if (event.key.code == Mouse::Left)
			{//а именно левая
				Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
				user.pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
			}
		}
		//------------------------------------------------------------------------------------------------------------

		//------Проверка где игрок и перехон на след уровень------------------------------------------------------------------------------------------------------
		for (int i = 0; i < number_items; i++)
		if (bots[i].GP == 'd')
		{
			if ((user.coordinate[0] == bots[i].coordinate[0]) && (user.coordinate[1] == bots[i].coordinate[1]))
			{
				user.lvl_up_map = true;
			}
		}
		//------------------------------------------------------------------------------------------------------------

		//------Перезгузка на новый уровень------------------------------------------------------------------------------------------------------
		if (user.lvl_up_map)
		{
			for (int i = 0; i < number_items; i++)
			{
				if (bots[i].GP == 'd')
				{
					if (bots[i].xp != 2)
						user.lvl_map++;
					else
					{
						user.lvl_map += 2;
						user.down_hp();
					}
				}
			}

			if (user.lvl_map > 8)
			{
				user.lvl_map = 3;
				for (int i = 3; i < 7; i++)
				{
					random_map_begin(1, 1, i);
				}
			}

			ostringstream lvl_map_up;
			lvl_map_up << "information/world/lvl_";
			lvl_map_up << user.lvl_map;
			lvl_map_up << ".txt";
			items_.open(lvl_map_up.str());
			items_ >> qwerty[0];
			items_ >> qwerty[1];
			items_ >> number_items;
			items_ >> number_items;
			items_ >> number_items;
			bots = new bot[number_items];
			items_.close();
			world = new char*[qwerty[0]];
			for (int i = 0; i < qwerty[0]; i++) { world[i] = new char[qwerty[1]]; }
			level_load(world, user, bots, &png, hard);
			for (int i = 0; i < number_items; i++)
			{
				bots[i].item_null_create(&png);
				bots[i].random_item(items);
			}
			user.lvl_up_map = false;
			if (user.scholl[5] != 0)	user.scholl[6] = 1;
			if (user.scholl[13] != 0)	user.scholl[14] = 1;
		}
		//------------------------------------------------------------------------------------------------------------

		//-------Отрисовка всего-----------------------------------------------------------------------------------------------------
		window.clear();

		if (go_in_game == 10000000)
		{
			go_in_game = main_menu(window, user, event,begin_game_);
		}
		switch (go_in_game)
		{
		case 1:
		{
				  if (!begin_game_)
				  {
					  create_name(user, window,event, down_button_);
					  if (class_selection(user, window, event, &png))
					  {
						  initial_load(items, world, user, &png, word_language,tree);
						  //------Радномайзер предметов с врагов------------------------------------------------------------------------------------
						  for (int i = 0; i < number_items; i++)
						  {
							  bots[i].item_null_create(&png);
							  bots[i].random_item(items);
						  }
						  //----------------------------------------------------------------------------------------------------------
						  begin_game_ = true;
					  }
				  }
				  
				  if (begin_game_)
				  {
					  lvl_show(user, bots, window, world, qwerty, &number_items, &world_image);//игрового поля

					  inv_show(user, window, word_language, event, down_button_, &png);//инвенторя

					  fight_show(user, bots, window, world, word_language);//боя
					  if (user.hp <= 0) go_in_game = 100;

					  tree_show(user, window, word_language, tree);//дерева прокачки

					  if (!user.open_tree_) window.draw(user.ikon);//персонажа

					  //------------------------------------------------------------------------------------------------------------

					  //------------------------------------------------------------------------------------------------------------
					  if ((!user.open_inv_) && (!user.open_fight_))
					  {
						  user.search_for_enemies(number_items, world, bots);
					  }
					  //-------------------------------------------------------------------------------------------------------------
					  if ((!user.open_inv_) && (!user.open_fight_))
					  {
						  user.course(world, tree);
					  }

					  user.lvl_up();
				  }
				  //------------------------------------------------------------------------------------------------------------
				  break;
		}
		case 2:
		{
				  user.lvl_map = 1;
				  if (!pass_scholl)
				  for (int i = 0; i < scholl_element; i++)
					  user.scholl[i] = 0;
				  user.lvl_up_map = true;
				  go_in_game = 1;
				  break;
		}
		case 4:
		{
				  version_review(window, user);
				  break;
		}
		case 5:
		{
				  settings(window,user,event,bots,number_items,down_button_,random_lvl,hard);
				  break;
		}
		case 6:
		{
				  return;
				  break;
		}
		case 100:
		{
				  user.labal_show(360, 0, "Вы умерли");
				  user.txt.setCharacterSize(40);
				  window.draw(user.txt);

				  user.labal_show(0, 42, "Чтоб вернуться в главное меню");
				  user.txt.setCharacterSize(20);
				  window.draw(user.txt);

				  user.labal_show(0, 64, "Нажмите Space");
				  user.txt.setCharacterSize(20);
				  window.draw(user.txt);

				  if (Keyboard::isKeyPressed(Keyboard::Space))
				  {
					  user.null_user(tree, &gif, &png);
					  begin_game_ = false;
					  user.lvl_map = 3;
					  user.lvl_up_map = true;
					  go_in_game = 10000000;
				  }

				  break;
		}
		default:
		{
				   break;
		}
		}

		window.display();//вывод на экран

		if ((!user.open_inv_) && (!user.open_fight_) && (!user.open_tree_))
		{
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				go_in_game = 10000000;
			}
		}
	}
	//----------------------------------------------------------------------------------------------------------------
}

void initial_load(item *item_initial_load, char** world, Player &user, Texture *imag, char** world_language, int &tree)
{
	ifstream items;
	char root[80];
	ifstream module;
	module.open(module_file);
	module.getline(root, 80);
	//------Загрузка предметов------------------------------------------------------------------------------------
	items.open(root);
	int number_items = 0;//кол-во вещей
	int coor[2];

	items >> number_items;

	items >> item_initial_load[0].tip;
	items >> item_initial_load[0].hp;
	items >> coor[0];
	items >> coor[1];
	item_initial_load[0].set_ikon(imag, coor[0], coor[1]);
	items.getline(item_initial_load[0].name, 80);
	
	items >> item_initial_load[1].tip;
	items >> coor[0];
	items >> coor[1];
	item_initial_load[1].set_ikon(imag, coor[0], coor[1]);
	items.getline(item_initial_load[1].name, 80);

	for (int i = 2; i < number_items; i++)
	{
		items >> item_initial_load[i].tip;
		items >> item_initial_load[i].element;
		items >> item_initial_load[i].att;
		items >> item_initial_load[i].def;
		items >> coor[0];
		items >> coor[1];
		item_initial_load[i].set_ikon(imag, coor[0], coor[1]);
		items.getline(item_initial_load[i].name, 80);
	}
	items.close();
	//------------------------------------------------------------------------------------------------------
	module.getline(root, 80);
	//------Загрузка дерева скилов------------------------------------------------------------------------------------

	items.open("information/class/" + user.name_class + "_skill.txt");
	items >> number_items;

	user.skill_tree_null(number_items, imag);
	tree = number_items;

	int m_k;
	int M_K;
	for (int i = 0; i < number_items; i++)
	{
		items >> M_K;
		if (M_K == 0)
		{
			user.the_skill_tree[i].mother = &user.the_skill_tree_null;
		}
		else
		{
			for (int j = 0; j < M_K; j++)
			{
				items >> m_k;
				user.the_skill_tree[i].mother = &user.the_skill_tree[m_k];
				user.the_skill_tree[m_k].children = &user.the_skill_tree[i];
			}
		}
		items >> user.the_skill_tree[i].hp;
		items >> user.the_skill_tree[i].att;
		items >> user.the_skill_tree[i].def;
		items >> user.the_skill_tree[i].need_points_for_pumping;
		items >> user.the_skill_tree[i].activ;
		items >> user.the_skill_tree[i].moves_to_recharge;
		items >> coor[0];
		items >> coor[1];
		user.the_skill_tree[i].set_ikon(imag, coor[0], coor[1]);
		char* der = new char[80];
		items.getline(der, 80);
		user.the_skill_tree[i].name = der;
	}
	items.close();
	//---------------------------------------------------------------------------------------------------------------
	module.getline(root, 80);
	//-----Загруска текста----------------------------------------------------------------------------------------------------------
	ostringstream PSS;
	PSS << root;
	PSS << "rus";
	PSS << ".txt";
	items.open(PSS.str());
	items >> number_items; 

	char t[80];
	items.getline(t, 80);

	for (int i = 0; i < number_items; i++)
	{
		items.getline(world_language[i], 80);
	}
	//---------------------------------------------------------------------------------------------------------------
	module.close();
	return;
}

void level_load(char** world, Player &user, bot* bots_initial_load, Texture *imag, float &Hard)
{
	ifstream items;
	int prof_coor_bot = 0;
	bool prof_coor_user = false;
	int number_items;
	int qwerty[2];
	ostringstream lvl_map_up;
	lvl_map_up << "information/world/lvl_";
	lvl_map_up << user.lvl_map;
	lvl_map_up << ".txt";
	items.open(lvl_map_up.str());
	lvl_map_up.str("");
	items >> qwerty[0];
	items >> qwerty[1];
	items >> user.coordinate[1];
	items >> user.coordinate[0];
	world[user.coordinate[0]][user.coordinate[1]] = user.GP;
	items >> number_items;
	for (int i = 0; i <	qwerty[0]; i++)
		items.getline(world[i], 80);
	
	//------------------------------------------------------------------------------------
	int coor[2];
	int do_mena = 0;
	//------Загрузка квестовых нип------------------------------------------------------------------------------------
	items >> number_items;
	for (int i = do_mena; i < number_items + do_mena; i++)
	{
		items >> bots_initial_load[i].element;
		items >> bots_initial_load[i].coordinate[1];
		items >> bots_initial_load[i].coordinate[0];
		items >> bots_initial_load[i].number_stori;
		items >> coor[0];
		items >> coor[1];
		items >> bots_initial_load[i].GP;

		for (int j = 0; j < bots_initial_load[i].number_stori; j++)
		{
			items.getline(bots_initial_load[i].stori[j], 40);
		}

		bots_initial_load[i].name = "NIP";
		bots_initial_load[i].set_ikon(imag, coor[0], coor[1]);
		world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] = bots_initial_load[i].GP;
	}
	do_mena = do_mena + number_items;
	//------------------------------------------------------------------------------------

	//------Загрузка дверей------------------------------------------------------------------------------------
	items >> number_items;
	for (int i = do_mena; i < number_items + do_mena; i++)
	{
		bots_initial_load[i].element = 10;
		bots_initial_load[i].xp = i;
		items >> bots_initial_load[i].coordinate[1];
		items >> bots_initial_load[i].coordinate[0];
		bots_initial_load[i].GP = 'D';
		bots_initial_load[i].name = "Дверь";
		bots_initial_load[i].set_ikon(imag, 5, 25);
		world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] = bots_initial_load[i].GP;
	}
	do_mena = do_mena + number_items;
	//------------------------------------------------------------------------------------

	//------Загрузка сундуков------------------------------------------------------------------------------------
	items >> number_items;
	
	for (int i = do_mena; i < number_items + do_mena; i++)
	{
		items >> bots_initial_load[i].element;
		items >> bots_initial_load[i].lvl;
		items >> bots_initial_load[i].coordinate[1];
		items >> bots_initial_load[i].coordinate[0];

		
		do
		{
			bots_initial_load[i].coordinate[1] = rand() % (qwerty[1] - 3) + 1;
			bots_initial_load[i].coordinate[0] = rand() % (qwerty[0] - 3) + 1;

			for (int x = -1; x < 2; x++)
			{
				for (int y = -1; y < 2; y++)
				{
					if ((user.coordinate[0] + x != bots_initial_load[i].coordinate[0]) && (user.coordinate[1] + y != bots_initial_load[i].coordinate[1]))
					{
						prof_coor_bot++;
					}
				}
			}

			if (prof_coor_bot >= 6)
				prof_coor_user = true;
			else prof_coor_bot = 0;

			if ((world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] == ' ') && (prof_coor_user))
			{

			}
			else
			{
				prof_coor_user = false;
			}

		} while ((!prof_coor_user));
		prof_coor_bot = 0; prof_coor_user = false;


		items >> coor[0];
		items >> coor[1];
		bots_initial_load[i].set_ikon(imag, coor[0], coor[1]);
		items >> bots_initial_load[i].GP;
		items.getline(bots_initial_load[i].name, 80);
		world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] = bots_initial_load[i].GP;
	}
	do_mena =do_mena + number_items;
	//------Загрузка ключей------------------------------------------------------------------------------------
	items >> number_items;
	for (int i = do_mena; i < number_items + do_mena; i++)
	{
		bots_initial_load[i].element = 5;

		do
		{
			bots_initial_load[i].coordinate[1] = rand() % (qwerty[1] - 3) + 1;
			bots_initial_load[i].coordinate[0] = rand() % (qwerty[0] - 3) + 1;

			for (int x = -1; x < 2; x++)
			{
				for (int y = -1; y < 2; y++)
				{
					if ((user.coordinate[0] + x != bots_initial_load[i].coordinate[0]) && (user.coordinate[1] + y != bots_initial_load[i].coordinate[1]))
					{
						prof_coor_bot++;
					}
				}
			}

			if (prof_coor_bot >= 6)
				prof_coor_user = true;
			else prof_coor_bot = 0;

			if ((world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] == ' ') && (prof_coor_user))
			{
							
			}
			else
			{
				prof_coor_user = false;
			}

			} while ((!prof_coor_user));
		prof_coor_bot = 0; prof_coor_user = false;

		bots_initial_load[i].set_ikon(imag, 18, 17);
		items >> bots_initial_load[i].GP;
		bots_initial_load[i].name = "ключ";
		world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] = bots_initial_load[i].GP;
	}
	do_mena = do_mena + number_items;


	int lvl_bot;

	items >> number_items;
	items >> lvl_bot;


	items.close();
	//------Загрузка ботов------------------------------------------------------------------------------------
	if (number_items != 0)
	{
		char number_lvl[5];
		string set_number_lvl;
		ostringstream set_number_lvl_;
		int random_bot, number_bots;

		set_number_lvl_ << lvl_bot << "lvl";
		set_number_lvl = set_number_lvl_.str();

		lvl_map_up << "information/";
		lvl_map_up << "bots";
		lvl_map_up << ".txt";
		items.open(lvl_map_up.str());

		items.getline(number_lvl, 5);

		items >> number_bots;

		if (number_lvl[0] == set_number_lvl[0])
		{

			// Сохранение текущей позиции
			ios::pos_type pos = items.tellg();

			for (int i = do_mena; i < number_items + do_mena; i++)
			{
				random_bot = rand() % number_bots;


				// Переход к позиции, хранящейся в pos 
				items.seekg(pos);
				cout << pos << endl;

				for (int j = 0; j < random_bot + 1; j++)
				{
					items >> bots_initial_load[i].hp;
					items >> bots_initial_load[i].element;
					items >> bots_initial_load[i].att;
					items >> bots_initial_load[i].def;
					bots_initial_load[i].lvl = 1;

					do
					{
						bots_initial_load[i].coordinate[1] = rand() % (qwerty[1] - 3) + 1;
						bots_initial_load[i].coordinate[0] = rand() % (qwerty[0] - 3) + 1;

						for (int x = -1; x < 2; x++)
						{
							for (int y = -1; y < 2; y++)
							{
								if ((user.coordinate[0] + x != bots_initial_load[i].coordinate[0]) && (user.coordinate[1] + y != bots_initial_load[i].coordinate[1]))
								{
									prof_coor_bot++;
								}
							}
						}

						if (prof_coor_bot >= 6)
							prof_coor_user = true;
						else prof_coor_bot = 0;

						if ((world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] == ' ') && (prof_coor_user))
						{

						}
						else
						{
							prof_coor_user = false;
						}

					} while ((!prof_coor_user));
					prof_coor_bot = 0; prof_coor_user = false;

					items >> bots_initial_load[i].xp;
					items >> coor[0];
					items >> coor[1];
					bots_initial_load[i].set_ikon(imag, coor[0], coor[1]);
					items >> bots_initial_load[i].GP;
					items.getline(bots_initial_load[i].name, 80);
				}
				world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] = bots_initial_load[i].GP;
			}
		}
		else
		{
			int i = do_mena;
			for (int j = 0; j < number_bots; j++)
			{
				items >> bots_initial_load[i].hp;
				items >> bots_initial_load[i].element;
				items >> bots_initial_load[i].att;
				items >> bots_initial_load[i].def;

				do
				{
					bots_initial_load[i].coordinate[1] = rand() % (qwerty[1] - 2) + 1;
					bots_initial_load[i].coordinate[0] = rand() % (qwerty[0] - 2) + 1;
				} while (world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] != ' ');

				items >> bots_initial_load[i].xp;
				items >> coor[0];
				items >> coor[1];
				bots_initial_load[i].set_ikon(imag, coor[0], coor[1]);
				items >> bots_initial_load[i].GP;
				items.getline(bots_initial_load[i].name, 80);
			}

			items >> number_bots;
			items.seekg(-1, ios::cur);

			items.getline(number_lvl, 5);

			items >> number_bots;


			if (number_lvl[0] == set_number_lvl[0])
			{

				// Сохранение текущей позиции
				ios::pos_type pos = items.tellg();

				for (int i = do_mena; i < number_items + do_mena; i++)
				{
					random_bot = rand() % number_bots;


					// Переход к позиции, хранящейся в pos 
					items.seekg(pos);

					for (int j = 0; j < random_bot + 1; j++)
					{
						items >> bots_initial_load[i].hp;
						items >> bots_initial_load[i].element;
						items >> bots_initial_load[i].att;
						items >> bots_initial_load[i].def;
						bots_initial_load[i].lvl = 2;

						do
						{
							bots_initial_load[i].coordinate[1] = rand() % (qwerty[1] - 3) + 1;
							bots_initial_load[i].coordinate[0] = rand() % (qwerty[0] - 3) + 1;

							for (int x = -1; x < 2; x++)
							{
								for (int y = -1; y < 2; y++)
								{
									if ((user.coordinate[0] + x != bots_initial_load[i].coordinate[0]) && (user.coordinate[1] + y != bots_initial_load[i].coordinate[1]))
									{
										prof_coor_bot++;
									}
								}
							}

							if (prof_coor_bot >= 6)
								prof_coor_user = true;
							else prof_coor_bot = 0;

							if ((world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] == ' ') && (prof_coor_user))
							{

							}
							else
							{
								prof_coor_user = false;
							}

						} while ((!prof_coor_user));
						prof_coor_bot = 0; prof_coor_user = false;

						items >> bots_initial_load[i].xp;
						items >> coor[0];
						items >> coor[1];
						bots_initial_load[i].set_ikon(imag, coor[0], coor[1]);
						items >> bots_initial_load[i].GP;
						items.getline(bots_initial_load[i].name, 80);
					}
					world[bots_initial_load[i].coordinate[0]][bots_initial_load[i].coordinate[1]] = bots_initial_load[i].GP;
				}
			}
		}
		items.close();
	}
	//---------------------------------------------------------------------------------------------------------------
}

bool class_selection(Player &user, RenderWindow &window, Event &event, Texture *imag)
{
	ifstream classes;
	Sprite class_;
	int size;
	int numbers = 0;
	Vector2f goor_game;
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	goor_game = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
	string str[number_of_classes + 1];
	int x_show[number_of_classes] = { 9, 11, 13, 15 };
	int x_y[2][number_of_classes] = { { 3, 4, 0, 24 }, { 10, 10, 10, 9 } };
	ostringstream PSS;

	str[0] = "Выбор персонажа";
	str[1] = "Воин";
	str[2] = "Маг ";
	str[3] = "Вор ";
	str[4] = "Лучник";

	size = str[0].length() / 2;
	size = size * 20;
	size = 400 - size;

	user.txt.setColor(Color::Red);

	user.labal_show(size, 0, str[0]);
	user.txt.setCharacterSize(40);
	window.draw(user.txt);

	user.txt.setCharacterSize(20);



	for (int i = 0; i < number_of_classes; i++)
	{
		user.txt.setColor(Color::Red);

		if ((goor_game.x <= (x_show[i] + 1) * 32) && (goor_game.x >= (x_show[i]) * 32))
		{
			if ((goor_game.y <= (3 + 1) * 32) && (goor_game.y >= (2) * 32))
			{
				user.txt.setColor(Color::White);
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left)
					{
						numbers = i + 1;
					}
				}
			}
		}
		class_.setTexture(*imag);

		class_.setTextureRect(IntRect(x_y[0][i] * 32, x_y[1][i] * 32, 31, 31));
		class_.setPosition(x_show[i] * 32, 2 * 32);

		size = str[i + 1].length() / 2;
		size = size * 10;
		size = (x_show[i] * 32) + 16 - size;

		user.labal_show(size, 3 * 32, str[i + 1]);

		window.draw(user.txt);
		window.draw(class_);
	}

	PSS.str("");

	if ((numbers > 0) && (numbers <= number_of_classes))
	{
		switch (numbers)
		{
		case 1:
			{
					  PSS << "warrior";
					  break;
			}
		case 2:
			{
					  PSS << "wizard";
					  break;
			}
		case 3:
			{
					  PSS << "thief";
					  break;
			}
		case 4:
			{
					  PSS << "bowman";
					  break;
			}
		}

		user.name_class = PSS.str();

		PSS << ".txt";
		classes.open("information/class/" + PSS.str());

		classes >> user.hp;
		user.max_hp = user.hp;
		classes >> user.def;
		classes >> user.att;

		user.set_ikon(imag, x_y[0][numbers - 1], x_y[1][numbers - 1]);

		

		return true;
	}


	return false;
}

void fight_show(Player &user, bot* bots, RenderWindow &window, char** world, char** world_language)
{
	if (user.open_fight_)
	{
		int x_user = 71;
		int x_bot = 600;
		int y_draw = 151;
		int y_draw_text = 200;

		user.characteristic_show(x_user, y_draw_text + 00, world_language[0], user.hp);
		window.draw(user.txt);

		user.characteristic_show(x_user, y_draw_text + 22, world_language[1], user.att);
		window.draw(user.txt);

		user.characteristic_show(x_user, y_draw_text + 44, world_language[2], user.def);
		window.draw(user.txt);

		user.characteristic_show(x_user, y_draw_text + 66, world_language[3], user.lvl);
		window.draw(user.txt);

		if ((user.scholl[11] != 0) && (user.scholl[12] == 0))
		{
			user.labal_show(x_user, y_draw_text + 88, "Твой хары");
			window.draw(user.txt);
		}


		user.characteristic_show(x_bot, y_draw_text + 00, world_language[4], bots[user.fight_bot].name);
		window.draw(user.txt);

		user.characteristic_show(x_bot, y_draw_text + 22, world_language[0], bots[user.fight_bot].hp);
		window.draw(user.txt);

		user.characteristic_show(x_bot, y_draw_text + 44, world_language[1], bots[user.fight_bot].att);
		window.draw(user.txt);

		user.characteristic_show(x_bot, y_draw_text + 66, world_language[2], bots[user.fight_bot].def);
		window.draw(user.txt);

		user.characteristic_show(x_bot, y_draw_text + 88, world_language[3], bots[user.fight_bot].lvl);
		window.draw(user.txt);

		if ((user.scholl[11] != 0) && (user.scholl[12] == 0))
		{
			user.labal_show(x_bot, y_draw_text + 110, "Хары врага");
			window.draw(user.txt);
		}

		for (int i = 0; i < 4; i++)
		{
			user.the_fight_activ_skills[i].ikon.setColor(Color::White);
			window.draw(user.the_fight_activ_skills[i].ikon);
			if (user.the_fight_activ_skills[i].moves_to_recharge - user.Go[i] > 0)
			{
				user.labal_show(user.the_fight_activ_skills[i].coordinate[0], user.the_fight_activ_skills[i].coordinate[1] + 32, user.the_fight_activ_skills[i].moves_to_recharge - user.Go[i]);
				window.draw(user.txt);
				if ((user.scholl[11] != 0) && (user.scholl[12] == 0))
				{
					user.labal_show(user.the_fight_activ_skills[i].coordinate[0], user.the_fight_activ_skills[i].coordinate[1] + 55, "Сколько ходов осталось до повторного использования");
					window.draw(user.txt);
				}
			}
		}

		if ((user.scholl[11] != 0) && (user.scholl[12] == 0))
		{
			user.labal_show(0, 500, "А теперь атакуй его нажав 'Q'");
			window.draw(user.txt);
		}
		if ((user.scholl[12] != 0) && (user.scholl[13] == 0) && (user.the_fight_activ_skills[0].moves_to_recharge - user.Go[0] == 0))
		{
			user.labal_show(0, 500, "Теперь нажми 'W', чтобы использовать навык");
			window.draw(user.txt);
		}
		
		user.ikon.setPosition(x_user + 30, y_draw);
		bots[user.fight_bot].ikon.setPosition(x_bot + 30, y_draw);
		user.fight(bots[user.fight_bot], world);
		window.draw(user.txt);
		if (user.hp <= 0) return;
		window.draw(bots[user.fight_bot].ikon);
	}
}

void inv_show(Player &user, RenderWindow &window, char** world_language, Event &event, bool &down_button, Texture *png)
{
	if ((user.open_inv_))
	{
		window.draw(user.inv_graf);
		for (int i = 0; i < number_of_things; i++)
		{
			window.draw(user.inv[i].ikon);
			if (user.inv[i].tip == 0)
			{
				//user.number_health_point();
				window.draw(user.txt);
			}
		}

		if ((user.scholl[2] != 0) && (user.scholl[3] == 0))
		{
			user.labal_show(0, 0, "Выбери пердмет мышкой");
			window.draw(user.txt);
		}
		if ((user.scholl[3] != 0) && (user.scholl[4] == 0))
		{
			user.labal_show(0, 0, "А теперь жми 'P', зелья так же использовать");
			window.draw(user.txt);
		}
		if ((user.scholl[4] != 0) && (user.scholl[5] == 0))
		{
			user.labal_show(0, 0, "Вещь одета, теперь выходим Escape");
			window.draw(user.txt);
		}

		for (int i = 0; i < amount_of_equipment; i++)
		{
			window.draw(user.equipment[i].ikon);
		}
		user.ikon.setPosition(159, 151);

		user.characteristic_show(71, 353, world_language[0], user.hp);
		window.draw(user.txt);

		user.characteristic_show(71, 375, world_language[1], user.att);
		window.draw(user.txt);

		user.characteristic_show(71, 397, world_language[2], user.def);
		window.draw(user.txt);

		user.characteristic_show(71, 419, world_language[3], user.lvl);
		window.draw(user.txt);

		user.characteristic_show(71, 441, world_language[5], user.xp, world_language[6], user.xp_up_lvl);
		window.draw(user.txt);

		for (int id = 0; id<number_of_things; id++)
		if ((user.pos.x >= user.inv[id].coordinate[0]) && (user.pos.x <= user.inv[id].coordinate[0] + 31))
		if ((user.pos.y >= user.inv[id].coordinate[1]) && (user.pos.y <= user.inv[id].coordinate[1] + 31))
		{
			if (user.inv[id].name == "")
			{
				user.characteristic_show(372, 331, world_language[7], " ");
				window.draw(user.txt);
			}
			else
			{
				switch (user.inv[id].tip)
				{
				case 110:
				{
						  user.characteristic_show(372, 331, world_language[8], user.inv[id].name);
						  window.draw(user.txt);

						  user.characteristic_show(372, 353, world_language[9], user.inv[id].hp);
						  window.draw(user.txt);

						  break;
				}

				case 10:
				{
						   user.characteristic_show(372, 331, world_language[8], user.inv[id].name);
						   window.draw(user.txt);

						   break;
				}

				default:
				{
						   user.characteristic_show(372, 331, world_language[8], user.inv[id].name);
						   window.draw(user.txt);

						   user.characteristic_show(372, 353, world_language[1], user.inv[id].att);
						   window.draw(user.txt);

						   user.characteristic_show(372, 375, world_language[2], user.inv[id].def);
						   window.draw(user.txt);
						   if ((user.scholl[3] != 0) && (user.scholl[4] == 0))
						   {
							   user.labal_show(372, 397, "Тут написана инфа про предмет каторый ты выделил");
							   window.draw(user.txt);
						   }
						   break;
				}
				}
			}
		}
		if (create_button(user, window, event, down_button, 372, 520, "Удалить предмет"))
		{
			user.delete_item(png);
		}
		user.open_inv();
	}
}

void tree_show(Player &user, RenderWindow &window, char** world_language, int tree)
{
	if (user.open_tree_)
	{
		user.characteristic_show(0, 0, "Очков прокачки: ", user.pumping_points);
		window.draw(user.txt);
		for (int i = 0; i < tree; i++)
		{
			window.draw(user.the_skill_tree[i].ikon);
			for (int id = 0; id<tree; id++)
			if ((user.pos.x >= user.the_skill_tree[id].coordinate[0]) && (user.pos.x <= user.the_skill_tree[id].coordinate[0] + 31))
			if ((user.pos.y >= user.the_skill_tree[id].coordinate[1]) && (user.pos.y <= user.the_skill_tree[id].coordinate[1] + 31))
			{
				if (!user.the_skill_tree[id].activ)
				{
					user.characteristic_show(0, 331, "Название: ", user.the_skill_tree[id].name);
					window.draw(user.txt);

					user.characteristic_show(0, 331 + 22, "Плюс к жизням: ", user.the_skill_tree[id].hp);
					window.draw(user.txt);

					user.characteristic_show(0, 331 + 44, "Плюс к атаке: ", user.the_skill_tree[id].att);
					window.draw(user.txt);

					user.characteristic_show(0, 331 + 66, "Плюс к защите: ", user.the_skill_tree[id].def);
					window.draw(user.txt);

					user.characteristic_show(0, 331 + 88, "Очков нужно для прокачки: ", user.the_skill_tree[id].need_points_for_pumping);
					window.draw(user.txt);
				}
				else
				{
					user.characteristic_show(0, 331, "Название: ", user.the_skill_tree[id].name);
					window.draw(user.txt);

					if (user.the_skill_tree[id].att != 0)
					{
						user.characteristic_show(0, 331 + 22, "Разово наносит урон: ", user.the_skill_tree[id].att);
						window.draw(user.txt);
					}

					if (user.the_skill_tree[id].def != 0)
					{
						user.characteristic_show(0, 331 + 22, "Плюс к защите: ", user.the_skill_tree[id].def);
						window.draw(user.txt);
					}

					if (user.the_skill_tree[id].hp != 0)
					{
						user.characteristic_show(0, 331 + 22, "Лечит на: ", user.the_skill_tree[id].hp);
						window.draw(user.txt);
					}

					user.characteristic_show(0, 331 + 44, "Перезарядка: ", user.the_skill_tree[id].moves_to_recharge);
					window.draw(user.txt);

					user.characteristic_show(0, 331 + 66, "Очков нужно для прокачки: ", user.the_skill_tree[id].need_points_for_pumping);
					window.draw(user.txt);
				}

				if ((user.scholl[7] != 0) && (user.scholl[8] == 0))
				{
					user.labal_show(0, 462, "Выбери навык мышкой");
					window.draw(user.txt);
				}
				if ((user.scholl[8] != 0) && (user.scholl[9] == 0))
				{
					user.labal_show(0, 462, "Инфа про навык который ты выбрал");
					window.draw(user.txt);
					user.labal_show(0, 484, "Выбери 1 навык и выучи его нажав 'P'");
					window.draw(user.txt);
				}
				if ((user.scholl[9] != 0) && (user.scholl[10] == 0))
				{
					user.labal_show(0, 462, "Нажми 'Escape' чтобы выйти");
					window.draw(user.txt);
				}

				bool der = user.the_skill_tree[id].mother->pumped;
				if (!user.the_skill_tree[id].pumped)
				{
					if (!der)
					{
						user.characteristic_show(0, 331 + 110, "Вы не можете прокачать этот навык пока не прокачаете ", user.the_skill_tree[id].mother->name);
						window.draw(user.txt);
					}
					else
					if (user.pumping_points < user.the_skill_tree[id].need_points_for_pumping)
					{
						user.labal_show(0, 331 + 110, "Не хватает очков прокачки");
						window.draw(user.txt);
					}
				}
				else
				{
					user.labal_show(0, 331 + 110, "Навык уже прокачен");
					window.draw(user.txt);
				}
				
			}
		}
		user.open_the_skill_tree(tree);
	}
	
}

void lvl_show(Player &user, bot* bots, RenderWindow &window, char** world, int *qwerty, int *number_items, Sprite *world_image)
{
	if ((!user.open_inv_) && (!user.open_fight_) && (!user.open_tree_))
	{
		for (int i = 0; i < qwerty[0]; i++)
		{
			for (int j = 0; j < qwerty[1]; j++)
			{
				if (world[i][j] == ' ')
				{
					world_image[0].setPosition((j - 1) * 32, (i - 1) * 32);
					window.draw(world_image[0]);
				}
				if (world[i][j] == user.GP) user.ikon.setPosition((j - 1) * 32, (i - 1) * 32);
				for (int r = 0; r < number_items[0]; r++)
				{
					if ((bots[r].element == 6) || (bots[r].element == 7))
					{
						if (bots[r].vize)
						{
							for (int f = 0;f < bots[r].number_stori;f++)
							{
								user.labal_show(0, 300 + (22 * f), bots[r].stori[f]);
								window.draw(user.txt);
							}
						}
					}
					if (world[i][j] == bots[r].GP)
					{
						bots[r].ikon.setPosition((j - 1) * 32, (i - 1) * 32);
						window.draw(bots[r].ikon);
					}
				}
			}
		}


		if (user.scholl[0] == 0)
		{
			user.labal_show(0, (qwerty[0] * 32) + 25, "Для ходьбы нажимайте WASD");
			window.draw(user.txt);
			user.labal_show(0, ((qwerty[0] + 1) * 32) + 25, "Для выхода в глав меню нажмите Spase");
			window.draw(user.txt);

		}
		if ((user.scholl[0] != 0) && (user.scholl[1] == 0))
		{
			user.labal_show(0, (qwerty[0] * 32) + 25, "Подойди к сундуку");
			window.draw(user.txt);
			user.labal_show(0, ((qwerty[0] + 1) * 32) + 25, "Чтоб взаимодействовать с сундуком нажми Е");
			window.draw(user.txt);
		}
		if ((user.scholl[1] != 0) && (user.scholl[2] == 0))
		{
			user.labal_show(0, (qwerty[0] * 32) + 25, "Нажми 'I'");
			window.draw(user.txt);
		}
		if ((user.scholl[5] != 0) && (user.scholl[6] == 0))
		{
			user.labal_show(0, (qwerty[0] * 32) + 25, "Подбери ключ и иди в открывшуюся дверь");
			window.draw(user.txt);
		}
		if ((user.scholl[6] != 0) && (user.scholl[7] == 0))
		{
			user.labal_show(0, (qwerty[0] * 32) + 25, "Это новый уровень, продолжим обучение");
			window.draw(user.txt);
			user.labal_show(0, ((qwerty[0] + 1) * 32) + 25, "Теперь нажми 'K'");
			window.draw(user.txt);
		}
		if ((user.scholl[10] != 0) && (user.scholl[11] == 0))
		{
			user.labal_show(0, (qwerty[0] * 32) + 25, "Подойди к врагу");
			window.draw(user.txt);
		}
		if ((user.scholl[13] != 0) && (user.scholl[14] == 0))
		{
			user.labal_show(0, (qwerty[0] * 32) + 25, "Ты закончил обучение, молодец");
			window.draw(user.txt);
			user.labal_show(0, ((qwerty[0] + 1) * 32) + 25, "Теперь перейди на следующий уровень");
			window.draw(user.txt);
		}
	}
}

int main_menu(RenderWindow &window, Player &user, Event &event, bool begin_game)
{

	string str[8];
	int size;
	int x, y;
	int continiuz = 7;
	int radche_str = 25;

	Vector2f goor_game;
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	goor_game = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

	str[0] = name_game;

	str[1] = "Начать игру";
	str[2] = "Обучение";
	str[3] = "Сохранение";
	str[4] = "Обзор обновления";
	str[5] = "Настройки";
	str[6] = "Выход";
	
	str[continiuz] = "Продолжить";

	x = 100; y = 352;
	size = str[0].length() / 2;
	size = size * 20;
	size = 400 - size;
	

	user.txt.setColor(Color::Red);
	
	user.labal_show(size, 0, str[0]);
	user.txt.setCharacterSize(40);
	window.draw(user.txt);
	
	size = 10000000;

	for (int i = 1; i < continiuz; i++)
	{
		user.txt.setColor(Color::Red);
		if ((i == 1) && (begin_game))
		{
			user.labal_show(x, (y + ((radche_str * i) - radche_str)), str[continiuz]);
		}
		else
			user.labal_show(x, (y + ((radche_str * i) - radche_str)), str[i]);

		if ((x - 1 < goor_game.x) && (x + str[i].length() * 10 > goor_game.x))
		{
			if (((y + ((radche_str * i) - radche_str)) - 1 < goor_game.y) && ((y + ((radche_str * i) - radche_str)) + 23 > goor_game.y))
			{
				user.txt.setColor(Color::White);
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left)
					{
						size = i;
					}
				}
			}
		}

		window.draw(user.txt);
	}
	return size;
}

void version_review(RenderWindow &window, Player &user)
{
	ifstream file;
	string str = "Обзор версии";
	char text[54];
	int i = 0;
	file.open("information/version_review.txt");
	i = str.length() / 2;
	i = i * 10;
	i = 400 - i;
	user.labal_show(i, 0, str);
	window.draw(user.txt);
	i = 0;
	while (!file.eof())
	{
		i++;
		file.getline(text, 54);
		user.labal_show(0, i * 25, text);
		window.draw(user.txt);
	}
}

void settings(RenderWindow &window, Player &user, Event &event, bot *bots, int number_items, bool &down_button, bool &rand_lvl, float &Hard)
{
	int size;
	int x, y;
	string str[3];
	string true_false[2];
	true_false[0] = "Вкл";
	true_false[1] = "Выкл";
	x = 100; y = 100;

	Vector2f goor_game;
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	goor_game = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

	str[0] = "Настройки";
	str[1] = "Рандомная карта";
	str[2] = "Хард режим";

	size = str[0].length() / 2;
	size = size * 20;
	size = 400 - size;

	user.txt.setColor(Color::Red);

	user.labal_show(size, 0, str[0]);
	user.txt.setCharacterSize(20);
	window.draw(user.txt);



	if (rand_lvl)
		user.labal_show(700, y, true_false[0]);
	else
		user.labal_show(700, y, true_false[1]);


	if ((x - 1 < goor_game.x) && (x + str[1].length() * 10 > goor_game.x))
	{
		if (((y + ((22 * 1) - 22)) - 1 < goor_game.y) && ((y + ((22 * 1) - 22)) + 23 > goor_game.y))
		{
			user.txt.setColor(Color::White);
			if (event.type == Event::MouseButtonPressed)
			{
					if (event.key.code == Mouse::Left)
					{
						if (down_button)
						{
							if (rand_lvl)
								rand_lvl = false;
							else
								rand_lvl = true;

							down_button = false;
						}
					}

			}
			else down_button = true;
		}
	}

	user.txt.setCharacterSize(20);
	window.draw(user.txt);
	user.labal_show(x, y, str[1]);
	user.txt.setCharacterSize(20);
	window.draw(user.txt);

	user.txt.setColor(Color::Red);

	if (Hard == 2)
		user.labal_show(700, y + 22, true_false[0]);
	else
		user.labal_show(700, y + 22, true_false[1]);

	if ((x - 1 < goor_game.x) && (x + str[1].length() * 10 > goor_game.x))
	{
		if (((y + ((22 * 2) - 22)) - 1 < goor_game.y) && ((y + ((22 * 2) - 22)) + 23 > goor_game.y))
		{
			user.txt.setColor(Color::White);
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					if (down_button)
					{
						if (Hard == 2)
							Hard = 0.5;
						else
							Hard = 2;
						for (int i = 0; i < number_items; i++)
						{
							bots[i].hard_bust(Hard);
						}
						down_button = false;
					}
				}

			}
			else down_button = true;
		}
	}

	user.txt.setCharacterSize(20);
	window.draw(user.txt);
	user.labal_show(x, y + 22, str[2]);
	user.txt.setCharacterSize(20);
	window.draw(user.txt);

	user.txt.setColor(Color::Red);
}

void create_name(Player &user, RenderWindow &window, Event &event, bool &down_button)
{

	string txt = "Задать имя";
	int x, y;
	x = 10; y = 300;

	if (create_button(user, window, event, down_button, x, y, txt))
	{
		system("1.exe");
	}

	char n[80];
	ifstream name;
	name.open("Name.txt");
	name.getline(n, 80);
	user.name = n;
	name.close();

	user.labal_show(x, y + 25, user.name);
	window.draw(user.txt);
}

void random_map_begin(int x, int y, int lvl_number)
{
	ofstream lvl;
	ostringstream lvl_map;
	char** world;
	int numbers_bots = 0;
	world = new char*[10];

	for (int i = 0; i < 10; i++)
		world[i] = new char[11];

	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			world[i][j] = ' ';
			if (i % 2 == 0)
				world[i][j] = '-';

			if (j % 2 == 0)
				world[i][j] = '-';
		}
	}

	random_map(0, x, y, world);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			
			if (i == 1)
				world[i][j] = ' ';

			if ((i == 9) || (i == 0))
				world[i][j] = '-';

			if (j == 0)
				world[i][j] = '<';

			if (j == 9)
				world[i][j] = '>';

			if (j == 10)
				world[i][j] = '\0';

		}
	}

	lvl_map << "information/world/lvl_";
	lvl_map << lvl_number;
	lvl_map << ".txt";

	lvl.open(lvl_map.str());

	lvl << 10 << ' ' << 10 << ' ' << y << ' ' << x << ' ' << 9;

	for (int i = 0; i < 10; i++)
	{
		lvl << world[i] << endl;
	}

	lvl << 0 << endl;
	lvl << 1 << endl;
	lvl << 8 << ' ' << 8 << endl;

	lvl << 1 << endl;
	lvl << 8 << ' ' << 1 << ' ' << 6 << ' ' << 3 << ' ' << 11 << ' ' << 17 << ' ' << ';' << ' ' << "сундук" << endl;

	lvl << 1 << endl;
	lvl << 'п' << endl;

	numbers_bots = (rand() % 6);
	lvl << numbers_bots <<' '<<1<< endl;

	lvl.close();

}

void random_map(int schet,int x, int y, char** world)
{
	int x_y_random;
	bool go = false;
	int cell = 0;
	int go_cell = 0;

	while (true)
	{
		x_y_random = rand() % 2;

		if ((x_y_random == 0) && (x + 1 != 9))
		{
			x += 1;
			world[x][y] = ' ';
			x -= 1;
			break;
		}

		if ((x_y_random == 1) && (y + 1 != 9))
		{
			y += 1;
			world[x][y] = ' ';
			y -= 1;
			break;
		}
	}



	if (y >= 8) { y = 1; x += 2; world[x][9] = '>'; }

	if ((schet == 60) || (x >= 8))
	{
		for (int i = 3; i < 9; i += 2)
		{
			go_cell = 1;
			for (int j = 1; j < 9; j++)
			{
				if (world[i][j] == ' ')
				{
					if (world[i - 1][j] != ' ')
					{
						go = false;
					}

					if (world[i - 1][j] == ' ')
					{
						go = true;
					}
					cell++;
				}

				if ((world[i][j] != ' ') || (j == 8))
				{
					if (!go)
					{
						int rand_go = (rand() % cell) + go_cell;
						world[i - 1][rand_go] = ' ';
					}
					go_cell = j + 1;
					cell = 0;
				}
			}
		}
		return;
	}
	
	random_map(schet + 1, x, y + 2, world);
}

bool create_button(Player &user, RenderWindow &window, Event &event, bool &down_button, int x, int y, string txt)
{
	Vector2f goor_game;
	Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
	goor_game = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
	bool i = false;
	user.txt.setColor(Color::Red);

	if ((goor_game.x > x) && (goor_game.x < x + (txt.size() * 10)))
	{
		if ((goor_game.y > y) && (goor_game.y < y + 25))
		{
			user.txt.setColor(Color::White);
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					if (down_button)
					{
						i = true;

						down_button = false;
					}
				}

			}
			else down_button = true;
		}
	}

	user.labal_show(x, y, txt);
	window.draw(user.txt);

	user.txt.setColor(Color::Red);

	return i;
}
