#pragma once
#include <iostream>
#include <cassert>
#include "move.h"
#include "console.h"
#include "shape.h"

namespace test {
	void move_player() {
		Console cmd;
		Plane plane;
		Move move;
		plane.set_size(Size(40, 10));
		plane.set_pos(Coord(30, 10));
		plane.set_border_padding(Size(0, 0));
		plane.set_color_bg(Color(3, 3));
		plane.set_color_plane(Color(12, 12));
		plane.set_color_border(Color(15, 15));
		plane.set_symbol_plane(' ');
		plane.set_symbol_border('.');
		std::cout << "Press any key...";
		while (true) {
			move.move();
			int dir_x = move.now.get_dir_x() * 2;
			int dir_y = -move.now.get_dir_y();
			plane.add_pos(Coord(dir_x, dir_y));

			//get info
			Coord plane_pos = plane.get_offset();
			Size plane_size = plane.get_size();
			Size screen_size = cmd.get_size_screen();

			//border collision
			if (plane_pos.x < 0) {
				plane.set_pos(Coord(0, plane_pos.y));
			}
			if (plane_pos.y < 0) {
				plane.set_pos(Coord(plane_pos.x, 0));
			}
			if ((plane_pos.x + plane_size.width) > screen_size.width-1) {
				plane.set_pos(Coord(screen_size.width - plane_size.width - 2, plane_pos.y));
			}
			if ((plane_pos.y + plane_size.height) > screen_size.height-1) {
				plane.set_pos(Coord(plane_pos.x, screen_size.height - plane_size.height - 1));
			}

			//print
			if (move.now.get_button() != false) {
				plane.print_plane();
				plane.print_bg();
			}
			if (move.now.get_escape() == true) {
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
		std::cout << "Test completed! Press any key...";
		cmd.pause();
	}
}