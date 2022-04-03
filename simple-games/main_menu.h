#pragma once
#include "interface.h"
#include "move.h"


void main_menu() {
	std::vector<std::string> list_menu{
	"Start",
	"Test",
	"Settings",
	"Quit"
	};

	std::string choice = MakeMenu::center_menu(list_menu, Color(0, 0), Color(0, 11), Color(0, 12), 5, 3, 4, 0.375);
	if (choice == "Start") {
		//TODO: start menu
	}
	if (choice == "Test") {
		//TODO: test menu
	}
	if (choice == "Settings") {
		//TODO: settings menu
	}
	if (choice == "Quit") {
		return;
	}
}
