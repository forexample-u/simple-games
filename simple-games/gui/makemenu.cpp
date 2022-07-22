#pragma once
#include <iostream>
#include <vector>
#include "core.cpp"
#include "move.cpp"
#include "shape/plane.cpp"
#include "utils/console.cpp"
#include "gui/button.cpp"
#include "gui/menu.cpp"

class MakeMenu
{
public:
	std::string center_menu(std::vector<std::string> list_menu)
	{
		Plane plane;
		Move move;
		Console cmd;
		Menu menu;
		Button button;

		menu.set_selected_color(color_selected);
		plane.set_color_bg(color_bg);
		button.set_color_bg(color_bg);
		button.set_color_button(color_button);
		button.set_pos(Coord(0, pos_y));
		Size screen_size = cmd.get_size_screen();
		button.set_size(Size(screen_size.width * scale_x, size_y));
		button.set_pos_center(1, 0);
		for (const auto& button_word : list_menu)
		{
			button.set_text(button_word);
			menu.push_button(button);
			button.add_pos(Coord(0, padding_y));
		}

		plane.set_size(Size(0, 0));
		plane.print_bg();
		menu.print();
		while (true)
		{
			Size screen_size_now = cmd.get_size_screen();
			if (abs(screen_size_now.width - screen_size.width) >= 5 || screen_size_now.width <= 20)
			{
				cmd.clear();
				cmd.color(color_bg);
				for (int y = 0; y < screen_size_now.height; y++)
				{
					cmd.gotoxy(0, y);
					std::cout << '.';
				}

				for (size_t i = 0; i < menu.size(); i++)
				{
					menu[i].set_size(Size(screen_size_now.width * scale_x, menu[i].get_size().height));
					menu[i].set_pos_center(1, 0);
					int pos_x = menu[i].get_pos().x - 4;
					if (pos_x <= 0)
					{
						pos_x = 0;
					}
					menu[i].set_pos(Coord(pos_x, menu[i].get_pos().y));
				}
				menu.print();
				cmd.sleep(20);
				screen_size = cmd.get_size_screen();
			}

			menu.move(move);
			cmd.sleep(60);
			if (move.now.get_button() != false)
			{
				menu.print();
			}
			if (move.now.get_enter() || move.now.get_space())
			{
				menu.print();
				break;
			}
		}
		int index_menu = menu.get_selected_index();
		return list_menu[index_menu];
	}

	void set_style(Color color_bg = Color(0, 0), Color color_button = Color(0, 11),
		Color color_selected = Color(0, 12), int pos_y = 5, int size_y = 3, int padding_y = 4, double scale_x = 0.375)
	{
		this->color_bg = color_bg;
		this->color_button = color_button;
		this->color_selected = color_selected;
		this->pos_y = pos_y;
		this->size_y = size_y;
		this->padding_y = padding_y;
		this->scale_x = scale_x;
	}

private:
	static Color color_bg;
	static Color color_button;
	static Color color_selected;
	static int pos_y;
	static int size_y;
	static int padding_y;
	static double scale_x;
};

Color MakeMenu::color_bg = Color(0, 0);
Color MakeMenu::color_button = Color(0, 11);
Color MakeMenu::color_selected = Color(0, 12);
int MakeMenu::pos_y = 5;
int MakeMenu::size_y = 3;
int MakeMenu::padding_y = 4;
double MakeMenu::scale_x = 0.375;