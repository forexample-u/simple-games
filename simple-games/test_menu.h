#pragma once
#include "interface.h"
#include "move_test.h"

void test_menu() {
	Console cmd;
	std::vector<std::string> list_menu {
		"Collide - test",
		"Menu - test",
		"Button - test",
		"Move - test",
		"Quit"
	};
	std::string choice = MakeMenu::center_menu(list_menu, Color(0, 0), Color(0, 11), Color(0, 12), 5, 3, 4, 0.375);

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
	if (choice == "Quit") {
		cmd.color_reset();
		cmd.clear();
		return;
	}
}