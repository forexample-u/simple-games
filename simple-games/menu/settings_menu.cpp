#pragma once
#include "gui/makemenu.cpp"

namespace ListMenu
{
	void main_menu();

	void settings_menu()
	{
		Console cmd;
		std::vector<std::string> list_settings{
			"Team",
			"Back",
		};
		MakeMenu menu;
		std::string choice = menu.center_menu(list_settings);

		cmd.color_reset();
		cmd.clear();

		if (choice == "Team")
		{
			int color_bg = rand() % 16;
			Color color_button = Color(rand() % 16, rand() % 16);
			Color color_selected = Color(rand() % 16, rand() % 16);

			menu.set_style(Color(color_bg, color_bg), color_button, color_selected);
			settings_menu();
		}
		if (choice == "Back")
		{
			main_menu();
		}
	}
}