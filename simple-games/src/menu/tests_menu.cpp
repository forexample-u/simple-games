#pragma once
#include "gui/makemenu.cpp"
#include "tests/collide_test.cpp"
#include "tests/button_auto_scale_test.cpp"
#include "tests/move_player_test.cpp"
#include "tests/menu_test.cpp"

namespace ListMenu
{
	void main_menu();
	
	void tests_menu()
	{
		Console cmd;
		std::vector<std::string> list_menu{
			"Collide - test",
			"Menu - test",
			"Button - test",
			"Move - test",
			"Back"
		};
		MakeMenu menu;
		std::string choice = menu.center_menu(list_menu);

		cmd.color_reset();
		cmd.clear();
		if (choice == "Collide - test")
		{
			ListTest::collide_test();
		}
		if (choice == "Menu - test")
		{
			ListTest::menu_test();
		}
		if (choice == "Button - test")
		{
			ListTest::button_auto_scale_test();
		}
		if (choice == "Move - test")
		{
			ListTest::move_player_test();
		}
		if (choice == "Back")
		{
			main_menu();
		}
	}
}