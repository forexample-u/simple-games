#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <ctime>
#include "move.h"
#include "console.h"
#include "shape.h"
#include "collider.h"
#include "interface.h"
#include "Breakout.h"

namespace test {
	void move_player() {
		Console cmd;
		Plane plane;
		Move move;
		cmd.resize_screen(Size(120, 30));
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
		while (true) {
			move.move();
			int dir_x = move.now.get_dir_x() * 2;
			int dir_y = -move.now.get_dir_y();
			plane.add_pos(Coord(dir_x, dir_y));

			//get info
			Coord plane_pos = plane.get_pos();
			Size plane_size = plane.get_size();
			Size screen_size = cmd.get_size_screen();

			//border collision
			if (plane_pos.x < 0) {
				plane.set_pos(Coord(0, plane_pos.y));
			}
			if (plane_pos.y < 0) {
				plane.set_pos(Coord(plane_pos.x, 0));
			}
			if ((plane_pos.x + plane_size.width) > screen_size.width - 4) {
				plane.set_pos(Coord(screen_size.width - plane_size.width - 4, plane_pos.y));
			}
			if ((plane_pos.y + plane_size.height) > screen_size.height-1) {
				plane.set_pos(Coord(plane_pos.x, screen_size.height - plane_size.height - 1));
			}

			if (old_screen_size.width != screen_size.width || old_screen_size.height != screen_size.height) {
				cmd.clear();
				old_screen_size = screen_size;
				plane.print();
				cmd.sleep(1);
			}

			//print
			if (move.now.get_button() != false) {
				plane.print();
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
		cmd.resize_screen(Size(120, 30));
		ball.set_color_ball(Color(11, 11));
		srand(time(0));
		if (rand() % 2) { 
			ball.set_dir(Dir(-1,-1));
		}
		ball.set_pos(Coord(1 + rand() % 50, 2 + rand() % 6));
		ball.set_size(Size(1 + rand() % 10, 1 + rand() % 3));

		std::vector<Plane> planes;
		Plane plane;
		plane.set_color_border(Color(15, 15));
		plane.set_color_plane(Color(0, 0));
		plane.set_size(Size(118, 29));
		plane.set_pos(Coord(0, 0));
		plane.print_border();
		plane.print_plane();
		planes.push_back(plane);

		plane.set_color_border(Color(12, 12));
		plane.set_size(Size(30, 10));
		plane.set_pos(Coord(15, 11));
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
				ball.collide.create(plane_.get_size(), plane_.get_pos(), ball.get_size(), ball.get_pos());
				if (ball.collide.get_bounce().y != 0) {
					ball.set_dir(Dir(ball.get_dir().x, ball.collide.get_bounce().y));
				}
				if (ball.collide.get_bounce().x != 0) {
					ball.set_dir(Dir(ball.collide.get_bounce().x, ball.get_dir().y));
				}
			}
			cmd.sleep(60);
			move.move();
			if (move.now.get_button() != false) {
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
		std::cout << "Test completed! Press any key...";
		cmd.pause();
	}

	void button_auto_scale() {
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
		for (int y = 0; y < screen.height; y++) {
			std::cout << row_screen << '\n';
		}

		while (1) {
			screen = cmd.get_size_screen();
			if ((button.get_pos().x + button.get_size().width + 2 >= screen.width)) {
				cmd.color(Color(button.get_color_bg()));
				cmd.clear();
			}

			if ((screen.width <= screen_buf.width - 10 || screen.width >= screen_buf.width + 10) || (screen.height <= screen_buf.height - 5 || screen.height >= screen_buf.height + 5)) {
				if (screen_buf.width <= 30) {
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

				if ((pos_button.x - 2) > 0) {
					std::string row(pos_button.x - 2, ' ');
					for (int y = 0; y < button.get_size().height; y++) {
						cmd.gotoxy(Coord(0, pos_button.y + y));
						std::cout << row;
					}
				}
				screen_buf.height = screen.height;
				screen_buf.width = screen.width;
			}

			move.move();
			if (move.now.get_button() != false) {
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
		std::cout << "Test completed! Press any key...";
		cmd.pause();
	}

	void menu_test() {
		Console cmd;
		Button button;
		Menu menu;
		Move move;
		cmd.resize_screen(Size(50, 25));
		button.set_size(Size(20, 3));
		std::vector<std::string> menu_list{
			"Start",
			"Settings",
			"Test",
			"Quit"
		};

		button.set_pos(Coord(15, 0));
		for (const auto& text : menu_list) {
			button.add_pos(Coord(0, button.get_size().height + 1));
			button.set_color_button(Color(0, 13));
			button.set_text(text);
			menu.push_button(button);
		}

		menu.set_selected_color(Color(0, 15));

		while (1) {
			menu.move(move);
			menu.print();
			if (move.now.get_space() || move.now.get_enter()) {
				break;
			}
			if (move.now.get_escape()) {
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

		cmd.color_reset();
		cmd.clear();
		std::cout << "Test completed! Press any key...";
		cmd.pause();
	}
}

namespace test {
	void move_to_point() {
		Coord point_pos = Coord();

		Block block;
		block.set_pos(Coord());


	}
}