#pragma once
#include "interface.h"
#include "move.h"

namespace ListMenu {
	void main_menu();

	void settings_menu() {
		Console cmd;
		std::vector<std::string> list_settings{
			"Team",
			"Back",
		};
		MakeMenu menu;
		std::string choice = menu.center_menu(list_settings);

		cmd.color_reset();
		cmd.clear();

		int style_index = 0;
		if (choice == "Team") {
			int color_bg = 0;
			Color color_button = Color(0, 12);
			Color color_selected = Color(0, 11);

			color_bg = rand() % 16;
			color_button = Color(rand()%16, rand()%16);
			color_selected = Color(rand()%16, rand()%16);
			
			menu.set_style(Color(color_bg, color_bg), color_button, color_selected);
			ListMenu::settings_menu();
		}
		if (choice == "Back") {
			ListMenu::main_menu();
		}
	}
}