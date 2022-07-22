#pragma once
#include "utils/console.cpp"
#include "shape/plane.cpp"
#include "move.cpp"

namespace ListTest
{
	void move_player_test()
	{
		Console cmd;
		Plane plane;
		Move move;
		cmd.resize_small_screen(Size(120, 30));
		plane.set_size(Size(30, 10));
		plane.set_pos(Coord(20, 10));
		plane.set_border_padding(Size(2, 1));
		plane.set_bg_padding(Size(3, 0));
		plane.set_color_bg(Color(3, 3));
		plane.set_color_plane(Color(12, 12));
		plane.set_color_border(Color(15, 15));
		plane.set_symbol_plane(' ');
		plane.set_symbol_border('.');
		plane.print();
		Size old_screen_size = cmd.get_size_screen();
		while (true)
		{
			move.move();
			int dir_x = move.now.get_dir_x() * 2;
			int dir_y = -move.now.get_dir_y();
			plane.add_pos(Coord(dir_x, dir_y));

			//get info
			Coord plane_pos = plane.get_pos();
			Size plane_size = plane.get_size();
			Size screen_size = cmd.get_size_screen();

			//border collision
			if (plane_pos.x < 0)
			{
				plane.set_pos(Coord(0, plane_pos.y));
			}
			if (plane_pos.y < 0)
			{
				plane.set_pos(Coord(plane_pos.x, 0));
			}
			if ((plane_pos.x + plane_size.width) > screen_size.width - 4)
			{
				plane.set_pos(Coord(screen_size.width - plane_size.width - 4, plane_pos.y));
			}
			if ((plane_pos.y + plane_size.height) > screen_size.height - 1)
			{
				plane.set_pos(Coord(plane_pos.x, screen_size.height - plane_size.height - 1));
			}

			if (old_screen_size.width != screen_size.width || old_screen_size.height != screen_size.height)
			{
				cmd.clear();
				old_screen_size = screen_size;
				plane.print();
				cmd.sleep(1);
			}

			//print
			if (move.now.get_button() != false)
			{
				plane.print();
			}
			if (move.now.get_escape() == true)
			{
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
	}
}