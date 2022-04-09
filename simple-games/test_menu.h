#pragma once
#include "interface.h"
#include "move_test.h"
#include "main_menu.h"

namespace ListMenu {
	void main_menu();

	void test_menu() {
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
		if (choice == "Collide - test") {
			test::collide_test();
		}
		if (choice == "Menu - test") {
			test::menu_test();
		}
		if (choice == "Button - test") {
			test::button_auto_scale();
		}
		if (choice == "Move - test") {
			test::move_player();
		}
		if (choice == "Back") {
			ListMenu::main_menu();
		}
	}
}
