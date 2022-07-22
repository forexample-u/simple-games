#include "menu/start_menu.cpp"
#include "menu/main_menu.cpp"

int main()
{
	ListMenu::start_menu();
	while (true)
	{
		ListMenu::main_menu();
	}
}