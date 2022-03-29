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
		plane.set_size(40, 10);
		plane.set_pos(30, 10);
		plane.set_color_bg(Color(3, 3));
		plane.set_color_plane(Color(12, 12));
		plane.set_color_border(Color(15, 15));
		plane.set_symbol_plane(' ');
		plane.set_symbol_border('.');
		plane.set_border_padding(0, 0);
		std::cout << "Press any key...";
		while (true) {
			move.move();
			int dir_x = move.now.get_dir_x() * 2;
			int dir_y = -move.now.get_dir_y();
			plane.add_pos(dir_x, dir_y);

			//get info
			int plane_pos_x = plane.get_offset_x();
			int plane_pos_y = plane.get_offset_y();
			int plane_size_x = plane.get_size_x();
			int plane_size_y = plane.get_size_y();
			int width_screen = cmd.get_width();
			int height_screen = cmd.get_height();

			//border collision
			if (plane_pos_x < 0) {
				plane.set_pos(0, plane_pos_y);
			}
			if (plane_pos_y < 0) {
				plane.set_pos(plane_pos_x, 0);
			}
			if ((plane_pos_x + plane_size_x) > width_screen-1) {
				plane.set_pos(width_screen - plane_size_x - 2, plane_pos_y);
			}
			if ((plane_pos_y + plane_size_y) > height_screen-1) {
				plane.set_pos(plane_pos_x, height_screen - plane_size_y - 1);
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