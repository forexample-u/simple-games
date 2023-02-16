#pragma once
#include <string>
#include "utils/console.cpp"
#include "shape/plane.cpp"
#include "entity/ball.cpp"

namespace ListMenu
{
	void main_menu();

	void start_menu()
	{
		Console cmd;
		Plane plane;

		//settings
		ColorBit color_text = ColorBit::White;
		Color color_ball = Color(ColorBit::Black, ColorBit::Black);
		Color color_bg = Color(ColorBit::White, ColorBit::White);
		int center_pos_y = 24;

		cmd.resize_small_screen(Size(80, 24));
		cmd.sleep(100);
		plane.set_size(Size(0, 0));
		plane.set_color_bg(color_bg);
		plane.print_bg();
		Size screen = cmd.get_size_screen();

		std::string label = "by @for_example";
		int length_label = static_cast<int>(label.length());
		Coord center_text = Coord(screen.width / 2 - length_label / 2 - 2, center_pos_y / 2);

		Ball ball;
		ball.set_pos(Coord(center_text.x - 31, 5));
		ball.set_color_bg(color_bg);
		ball.set_color_ball(color_ball);
		while (true)
		{
			if (ball.get_pos().y >= center_pos_y - 1)
			{
				ball.set_dir(Dir(1, -1));
			}
			if (ball.get_pos().y < center_pos_y / 2 + 2)
			{
				if (ball.get_pos().x >= screen.width / 2 - length_label - 2)
				{
					ball.print();
					cmd.sleep(100);
					break;
				}
				ball.set_dir(Dir(1, 1));
			}
			ball.print();
			cmd.sleep(50);
		}
		plane.set_color_bg(color_ball);
		plane.print_bg();
		ball.print();
		cmd.gotoxy(ball.get_pos().x - 1, ball.get_pos().y + 1);
		cmd.sleep(1000);
		cmd.color(Color(color_text, ColorBit::Black));
		cmd.gotoxy(center_text);
		for (const auto& ch : label)
		{
			std::cout << ch << std::flush;
			cmd.sleep(100);
		}
		std::cout << ' ' << std::flush;
		cmd.sleep(2100);
		plane.print_bg();
		cmd.sleep(900);
		cmd.resize_small_screen(Size(50, 30));
		cmd.sleep(100);
		main_menu();
	}
}