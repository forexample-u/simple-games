#pragma once
#include "gui/makemenu.cpp"
#include "tests/listtest.cpp"

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
		ListTest test;
		if (choice == "Collide - test")
		{
			test.collide_test();
		}
		if (choice == "Menu - test")
		{
			test.menu_test();
		}
		if (choice == "Button - test")
		{
			test.button_auto_scale_test();
		}
		if (choice == "Move - test")
		{
			test.move_player();
		}
		if (choice == "Back")
		{
			main_menu();
		}
	}
}