#pragma once
#include "gui/makemenu.cpp"
#include "games_menu.cpp"
#include "settings_menu.cpp"
#include "tests_menu.cpp"

namespace ListMenu
{
	void main_menu()
	{
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

		if (choice == "Start")
		{
			games_menu();
		}
		if (choice == "Test")
		{
			tests_menu();
		}
		if (choice == "Settings")
		{
			settings_menu();
		}
		if (choice == "Quit")
		{
			exit(0);
		}
	}
}