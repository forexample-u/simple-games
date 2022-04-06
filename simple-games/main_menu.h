#pragma once
#include "interface.h"
#include "settings_menu.h"
#include "game_menu.h"
#include "test_menu.h"

namespace ListMenu {
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
			ListMenu::game_menu();
		}
		if (choice == "Test") {
			ListMenu::test_menu();
		}
		if (choice == "Settings") {
			ListMenu::settings_menu();
		}
		if (choice == "Quit") {
			cmd.color_reset();
			cmd.clear();
			return;
		}
	}
}