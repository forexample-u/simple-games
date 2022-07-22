#pragma once
#include "games/2048/plane2048.cpp"

namespace ListGame
{
	void _2048()
	{
		Plane plane;
		Console cmd;
		Plane2048 game;
		Move move;
		cmd.resize_small_screen(Size(120, 30));

		srand(time(0));
		cmd.sleep(100);
		Size screen_size = cmd.get_size_screen();

		//settings:
		Coord pos = Coord((screen_size.width - 55) / 2, (screen_size.height - 28) / 2);
		Size padding = Size(2, 1);

		//plane
		plane.set_pos(pos);
		plane.set_size(Size(55, 27));
		plane.set_border_padding(padding);
		plane.set_color_plane(Color(15, 15));
		plane.set_color_border(Color(7, 7));
		plane.set_color_bg(Color(0, 0));

		//2048
		game.set_pos(Coord(pos.x + padding.width * 2, pos.y + padding.height * 2));

		//print
		cmd.sleep(50);
		plane.print();
		game.print();
		while (1)
		{
			game.move(move);
			if (move.now.get_button() != false)
			{
				game.print();
			}
			if (game.is_die())
			{
				break;
			}
			if (move.now.get_escape())
			{
				break;
			}
		}
		cmd.pause();
	}
}