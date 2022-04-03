#pragma once
#include "interface.h"
#include "move.h"


void settings_menu() {
	Console cmd;
	std::vector<std::string> list_settings {
		"Team",
		"Back",
	};
	std::string choice = MakeMenu::center_menu(list_settings, Color(0, 0), Color(0, 11), Color(0, 12), 5, 3, 4, 0.375);
	
	cmd.color_reset();
	cmd.clear();
	if (choice == "Team") {
		//TODO: color team
	}
	if (choice == "Back") {

	}
}