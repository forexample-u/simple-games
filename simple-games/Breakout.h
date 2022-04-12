#pragma once
#include <iostream>
#include <vector>
#include "core.h"
#include "console.h"
#include "move.h"
#include "shape.h"
#include "collider.h"
#include <ctime>

class Ball : public Collider {
public:
	void add_move() {
		pos_ball.x += dir_ball.x;
		pos_ball.y += dir_ball.y;
	}

	//print
	void print() const {
		std::string row(size_ball.width, char_ball);

		cmd.color(color_bg);
		for (int y = 0; y < size_ball.height; y++) {
			cmd.gotoxy(pos_ball.x, pos_ball.y + y);
			std::cout << row << std::flush;
		}

		pos_ball.x += dir_ball.x;
		pos_ball.y += dir_ball.y;

		cmd.color(color_ball);
		for (int y = 0; y < size_ball.height; y++) {
			cmd.gotoxy(pos_ball.x, pos_ball.y + y);
			std::cout << row << std::flush;
		}
		cmd.color(color_bg);
		cmd.gotoxy(pos_ball);
	}

	void detect_collision(Coord collision_pos, Size collision_size) {
		collide.create(collision_size, collision_pos, size_ball, pos_ball);
		if (collide.get_bounce().x != 0) {
			set_dir(Dir(collide.get_bounce().x, dir_ball.y));
		}
		if (collide.get_bounce().y != 0) {
			set_dir(Dir(dir_ball.x, collide.get_bounce().y));
		}
	}

	//set
	void set_pos(Coord new_pos) {
		pos_ball = new_pos;
	}

	void set_size(Size new_size) {
		size_ball = new_size;
	}

	void set_dir(Dir new_dir) {
		dir_ball = new_dir;
	}

	void set_color_ball(Color new_color) {
		color_ball = new_color;
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_symbol_ball(char new_ch) {
		char_ball = new_ch;
	}

	//get
	Coord get_pos() const {
		return pos_ball;
	}

	Size get_size() const {
		return size_ball;
	}

	Dir get_dir() const {
		return dir_ball;
	}

private:
	mutable Coord pos_ball;
	Size size_ball = Size(1, 1);
	Dir dir_ball = Dir(1, 1);
	Color color_ball = Color(0, 15);
	Color color_bg;
	char char_ball = ' ';
	Console cmd;
	std::vector<Block> collisions;
};



class Board {
public:
	void move(Move& move) {
		move.move();
		last_pos_board = pos_board; //save_pos
		dir_board = Dir(0, 0);
		dir_board.x = move.now.get_dir_x();
		dir_board.y = move.now.get_dir_y();
		pos_board.x += dir_board.x * move_step_board.x;
		pos_board.y -= dir_board.y * move_step_board.y;
	}

	void set_border(Coord border_pos, Size border_size) {
		int collision_left = border_pos.x + 1;
		int collision_right = border_pos.x + border_size.width - size_board.width - 1;
		int collision_up = border_pos.y + 1;
		int collision_down = border_pos.y + border_size.height - size_board.height - 1;
		if (collision_left > pos_board.x) { pos_board.x = collision_left; }
		if (collision_right < pos_board.x) { pos_board.x = collision_right; }
		if (collision_down < pos_board.y) { pos_board.y = collision_down; }
		if (collision_up > pos_board.y) { pos_board.y = collision_up; }
	}

	void set_border(IShape& shape) {
		set_border(shape.get_pos(), shape.get_size());
	}

	//set
	void set_pos(Coord new_pos) {
		last_pos_board = pos_board;
		pos_board = new_pos;
	}

	void set_size(Size new_size) {
		size_board = new_size;
	}

	void set_step(Coord new_step) {
		move_step_board = new_step;
	}

	void set_symbol_board(char new_ch) {
		char_board = new_ch;
	}

	void set_color_board(Color new_color) {
		color_board = new_color;
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	//print
	void print() const {
		std::string row(size_board.width, char_board);

		//backround
		if (!(pos_board == last_pos_board)) {
			cmd.color(color_bg);
			for (int y = 0; y < size_board.height; y++) {
				cmd.gotoxy(last_pos_board.x, last_pos_board.y + y);
				std::cout << row;
			}
		}

		//border
		cmd.color(color_board);
		for (int y = 0; y < size_board.height; y++) {
			cmd.gotoxy(pos_board.x, pos_board.y + y);
			std::cout << row << std::flush;
		}
		cmd.color(color_bg);
		cmd.gotoxy(pos_board);		
	}

	//get
	Coord get_pos() const {
		return pos_board;
	}

	Size get_size() const {
		return size_board;
	}

private:
	Coord pos_board;
	Coord last_pos_board;
	Size size_board = Size(10, 1);
	Dir dir_board = Dir(1, 0);
	Color color_board = Color(7, 7);
	Coord move_step_board = Coord(3, 0);
	char char_board = ' ';

	Color color_bg;
	Console cmd;
};



namespace ListGame {
	void breakout() {
		Move move;
		Console cmd;
		Plane plane;

		Ball ball;
		Block block;
		Board player;
		cmd.resize_small_screen(Size(137, 41));
		cmd.sleep(100);
		Size screen = cmd.get_size_screen();

		//settings:
		Size player_size = Size(38, 1);
		Size plane_size = Size(128, 39);
		Coord plane_pos = Coord((screen.width - plane_size.width)/2, (screen.height - plane_size.height)/2);
		Size block_count = Size(11, 5);
		Size block_size = Size(8, 2);
		Size block_padding = Size(2, 1);
		Coord player_step = Coord(3, 0);
		Coord block_offset = Coord(10, 2);
		int color_bg = 15;
		int color_plane = 0;
		int color_border = 15;
		int color_ball = 15;
		

		//color
		plane.set_color_bg(Color(color_bg, color_bg));
		plane.set_color_border(Color(color_border, color_border));
		plane.set_color_plane(Color(color_plane, color_plane));
		ball.set_color_ball(Color(color_ball, color_ball));
		ball.set_color_bg(Color(color_plane, color_plane));
		block.set_color_block(Color(7, 7));
		player.set_color_board(Color(12, 12));
		player.set_color_bg(Color(color_plane, color_plane));

		//calc settings
		block_padding.width += block_size.width;
		block_padding.height += block_size.height;

		//plane
		plane.set_pos(plane_pos);
		plane.set_size(plane_size);

		//player
		player.set_pos(Coord(plane_pos.x + (rand() % (plane_size.width - player_size.width - 1)) + 1, plane_pos.y + plane_size.height - player_size.height - 1));
		player.set_size(player_size);
		player.set_step(player_step);

		//ball
		ball.set_pos(Coord(player.get_pos().x, player.get_pos().y - player_size.height - 2));
		ball.set_size(Size(2, 1));
		ball.set_dir(Dir(1 + (rand() % 2) * -2, -1));

		//blocks
		block.set_size(block_size);
		std::vector<Block> blocks;
		for (int y = 0; y < block_count.height; y++) {
			block.set_pos(block_offset);
			block.add_pos(Coord(0, block_padding.height * y));
			block.add_pos(plane_pos);
			for (int x = 0; x < block_count.width; x++) {
				blocks.push_back(block);
				block.add_pos(Coord(block_padding.width, 0));
			}
		}

		plane.print();
		for (const auto& block : blocks) {
			block.print();
		}

		clock_t clock_old = std::clock();
		clock_t clock_now = std::clock();
		clock_t clock_first = std::clock();
		clock_t speed_add = 2;
		clock_t sleep_ball_ms = ((block_count.width * block_count.height) * speed_add) - 20;
		clock_t first_sleep_ms = 2500;
		while (true) {
			player.move(move);
			player.set_border(plane);
			player.print();

			cmd.sleep(30);
			clock_now = std::clock();
			if ((clock_old + sleep_ball_ms < clock_now) && (clock_first + first_sleep_ms < clock_now)) {
				for (size_t i = 0; i < blocks.size(); i++) {
					ball.detect_collision(blocks[i].get_pos(), blocks[i].get_size());
					if (ball.collide.is_any()) {
						blocks[i].set_color_block(plane.get_color_plane());
						blocks[i].print();
						blocks.erase(blocks.begin() + i);
						if (speed_add + 10 <= sleep_ball_ms) {
							sleep_ball_ms -= speed_add;
						}

					}
				}
				ball.detect_collision(player.get_pos(), player.get_size());
				ball.detect_collision(plane.get_pos(), plane.get_size());
				ball.print();
				clock_old = std::clock();
			}
			if (clock_first + first_sleep_ms > clock_now) {
				cmd.sleep(100);
			}

			if (ball.get_pos().y >= plane_pos.y + plane_size.height - 2) { // die
				break;
			}
			if (blocks.empty()) { // win
				break;
			}
			if (move.now.get_escape()) {
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
	}
}
