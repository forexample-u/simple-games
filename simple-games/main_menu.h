#pragma once
#include "interface.h"
#include "settings_menu.h"
#include "game_menu.h"
#include "test_menu.h"


void main_menu() {
	Console cmd;
	std::vector<std::string> list_menu{
		"Start",
		"Test",
		"Settings",
		"Quit"
	};
	std::string choice = MakeMenu::center_menu(list_menu, Color(0, 0), Color(0, 11), Color(0, 12), 5, 3, 4, 0.375);
	
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
		cmd.color_reset();
		cmd.clear();
		return;
	}
}
