#pragma once
#include "interface.h"
#include "game_menu.h"
#include "test_menu.h"
#include "settings_menu.h"

namespace ListMenu {
	void game_menu();
	void test_menu();
	void settings_menu();
	
	void main_menu() {
		Console cmd;
		std::vector<std::string> list_menu{
			"Start",
			"Test",
			"Settings",
			"Quit"
		};

		MakeMenu menu;
		std::string choice = menu.center_menu(list_menu);

		cmd.color_reset();
		cmd.clear();
		if (choice == "Start") {
			game_menu();
		}
		if (choice == "Test") {
			test_menu();
		}
		if (choice == "Settings") {
			settings_menu();
		}
		if (choice == "Quit") {
			exit(0);
		}
	}
}