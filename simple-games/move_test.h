#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include "move.h"
#include "console.h"
#include "shape.h"
#include "collider.h"

class Ball: public Collider {
public:
	//print
	void print() {
		cmd.gotoxy(pos);
		cmd.color(color_bg);
		std::cout << ' ';

		pos.x += dir.x;
		pos.y += dir.y;

		cmd.gotoxy(pos);
		cmd.color(color_ball);
		std::cout << ' ';
	}

	//set
	void set_color_ball(Color new_color) {
		color_ball = new_color;
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_dir(Dir new_dir) {
		dir = new_dir;
	}

	void set_pos(Coord new_pos) {
		pos = new_pos;
	}

	//get
	Dir get_dir() const {
		return dir;
	}

	Coord get_pos() const {
		return pos;
	}

private:
	Color color_ball;
	Color color_bg;
	Coord pos;
	Dir dir = {1, 1};
	Console cmd;
};

namespace test {
	void move_player() {
		Console cmd;
		Plane plane;
		Move move;
		plane.set_size(Size(40, 10));
		plane.set_pos(Coord(30, 10));
		plane.set_border_padding(Size(2, 1));
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
				plane.print_border();
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

	void collide_test() {
		Console cmd;
		Move move;
		Ball ball;
		ball.set_color_ball(Color(11, 11));
		ball.set_pos(Coord(7, 3));

		std::vector<Plane> planes;
		Plane plane;
		plane.set_color_border(Color(15, 15));
		plane.set_size(Size(118, 29));
		plane.print_border();
		planes.push_back(plane);

		plane.set_color_border(Color(12, 12));
		plane.set_size(Size(30, 10));
		plane.set_pos(Coord(15, 5));
		plane.print_border();
		planes.push_back(plane);

		plane.set_color_border(Color(13, 13));
		plane.set_size(Size(20, 13));
		plane.set_pos(Coord(61, 12));
		plane.print_border();
		planes.push_back(plane);

		plane.set_color_border(Color(11, 11));
		plane.set_size(Size(10, 5));
		plane.set_pos(Coord(107, 1));
		plane.print_border();
		planes.push_back(plane);

		while (1) {
			ball.print();
			for (const auto& plane_ : planes){
				ball.collide.create(plane_.get_size(), plane_.get_offset(), { 0, 0 }, ball.get_pos());
				if (ball.collide.border().y == -1) {
					ball.set_dir({ ball.get_dir().x, -1 });
				}
				if (ball.collide.border().y == 1) {
					ball.set_dir({ ball.get_dir().x, 1 });
				}
				if (ball.collide.border().x == -1) {
					ball.set_dir({ -1, ball.get_dir().y });
				}
				if (ball.collide.border().x == 1) {
					ball.set_dir({ 1, ball.get_dir().y });
				}
			}
			cmd.sleep(60);
			move.move();
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