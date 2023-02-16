#pragma once
#include "games/2048/plane2048.cpp"

namespace ListGame
{
	void _2048()
	{
		Plane plane;
		Console cmd;
		Plane2048 plane2048;
		KeyboardMove move;
		cmd.resize_small_screen(Size(120, 30));

		srand(time(0));
		cmd.sleep(100);
		Size screen_size = cmd.get_size_screen();
		Coord pos = Coord((screen_size.width - 55) / 2, (screen_size.height - 28) / 2);
		Size padding = Size(2, 1);

		plane.set_pos(pos);
		plane.set_size(Size(55, 27));
		plane.set_border_padding(padding);
		plane.set_color_plane(Color(ColorBit::White, ColorBit::White));
		plane.set_color_border(Color(ColorBit::Gray, ColorBit::Gray));
		plane.set_color_bg(Color(ColorBit::Black, ColorBit::Black));

		plane2048.set_pos(Coord(pos.x + padding.width * 2, pos.y + padding.height * 2));

		cmd.sleep(50);
		plane.print();
		plane2048.print();
		while (true)
		{
			move.detect_button();
			plane2048.move(move);
			if (move.get_button_toupper() != false)
			{
				plane2048.print();
			}
			if (plane2048.is_die())
			{
				break;
			}
			if (move.get_button_toupper() == 27)
			{
				break;
			}
		}
		cmd.pause();
	}
}