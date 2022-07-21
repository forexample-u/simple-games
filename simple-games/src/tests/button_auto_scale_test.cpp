#pragma once
#include "utils/console.cpp"
#include "move.cpp"
#include "gui/button.cpp"

namespace ListTest
{
	void button_auto_scale_test()
	{
		Console cmd;
		Move move;
		Button button;
		Size screen = cmd.get_size_screen();
		Size screen_buf = Size(screen.width - 10, screen.height);
		Color color_bg = Color(13, 13);
		Color color_button = Color(0, 14);
		cmd.resize_screen(Size(120, 30));
		button.set_color_bg(color_bg);
		std::string row_screen(screen.width, ' ');
		cmd.color(color_bg);
		for (int y = 0; y < screen.height; y++)
		{
			std::cout << row_screen << '\n';
		}

		while (true)
		{
			screen = cmd.get_size_screen();
			if ((button.get_pos().x + button.get_size().width + 2 >= screen.width))
			{
				cmd.color(Color(button.get_color_bg()));
				cmd.clear();
			}

			if ((screen.width <= screen_buf.width - 10 || screen.width >= screen_buf.width + 10) || (screen.height <= screen_buf.height - 5 || screen.height >= screen_buf.height + 5))
			{
				if (screen_buf.width <= 30)
				{
					cmd.color(button.get_color_bg());
					cmd.clear();
				}
				button.set_color_button(button.get_color_bg());
				button.set_text("");
				button.set_symbol_bg(' ');
				button.print();

				button.set_color_button(color_button);
				button.set_text("Hello! I'm button! Resize screen!");
				button.set_symbol_bg('.');
				button.set_size(Size(screen.width / 2, 5));
				button.set_pos_center(true, true);
				Coord pos_button = button.get_pos();
				button.set_pos(Coord(pos_button.x - 2, pos_button.y));
				button.print();

				if ((pos_button.x - 2) > 0)
				{
					std::string row(pos_button.x - 2, ' ');
					for (int y = 0; y < button.get_size().height; y++)
					{
						cmd.gotoxy(Coord(0, pos_button.y + y));
						std::cout << row;
					}
				}
				screen_buf.height = screen.height;
				screen_buf.width = screen.width;
			}

			move.move();
			if (move.now.get_button() != false)
			{
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
		cmd.pause();
	}
}