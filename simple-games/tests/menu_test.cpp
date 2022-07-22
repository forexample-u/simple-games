#pragma once
#include "core.cpp"
#include "move.cpp"
#include "utils/console.cpp"
#include "gui/button.cpp"
#include "gui/menu.cpp"

namespace ListTest
{
	void menu_test()
	{
		Console cmd;
		Button button;
		Menu menu;
		Move move;
		Size start_screen = cmd.get_size_screen();

		cmd.resize_screen(Size(50, 25));
		button.set_size(Size(20, 3));
		std::vector<std::string> menu_list{
			"Start",
			"Settings",
			"Test",
			"Quit"
		};

		button.set_pos(Coord(15, 0));
		for (const auto& text : menu_list)
		{
			button.add_pos(Coord(0, button.get_size().height + 1));
			button.set_color_button(Color(0, 13));
			button.set_text(text);
			menu.push_button(button);
		}

		menu.set_selected_color(Color(0, 15));

		while (true)
		{
			menu.move(move);
			menu.print();
			if (move.now.get_space() || move.now.get_enter())
			{
				break;
			}
			if (move.now.get_escape())
			{
				break;
			}
			cmd.gotoxy(0, 0);
			std::cout << std::string(40, ' ');
			int index = menu.get_selected_index();
			cmd.gotoxy(0, 0);
			cmd.color(Color(13, 0));
			std::cout << "Your choice: ";
			cmd.color(Color(7, 0));
			std::cout << menu_list[index];
			cmd.sleep(100);
		}

		cmd.resize_screen(start_screen);
		cmd.color_reset();
		cmd.clear();
	}
}