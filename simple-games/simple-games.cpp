#include <iostream>
#include "main_menu.h"
#include "start_menu.h"

int main() {
	ListMenu::start_menu();
	while (true) {
		ListMenu::main_menu();
	}
}