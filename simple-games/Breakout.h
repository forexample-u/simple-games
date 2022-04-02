#pragma once
#include <iostream>
#include <vector>
#include "core.h"
#include "console.h"
#include "move.h"
#include "shape.h"
#include "collider.h"


class Ball : public Collider {
public:
	//print
	void print() {
		std::string row(size_ball.width, trail_char);

		cmd.color(color_bg);
		for (int y = 0; y < size_ball.height; y++) {
			cmd.gotoxy(pos_ball.x, pos_ball.y + y);
			std::cout << row;
		}

		pos_ball.x += dir_ball.x;
		pos_ball.y += dir_ball.y;
		cmd.color(color_ball);
		for (int y = 0; y < size_ball.height; y++) {
			cmd.gotoxy(pos_ball.x, pos_ball.y + y);
			std::cout << row;
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

	void set_trail_char(char new_ch) {
		trail_char = new_ch;
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
	Color color_ball;
	Color color_bg;
	Coord pos_ball;
	Size size_ball = Size(1, 1);
	Dir dir_ball = Dir(1, 1);
	char trail_char = ' ';
	Console cmd;
};

class Board {
public:
	void move(Move& move) {
		move.move();
		last_pos_board = pos_board; //save_pos
		dir_board = Dir(0, 0);
		dir_board.x = move.now.get_dir_x();
		dir_board.y = move.now.get_dir_y();
		pos_board.x += dir_board.x * move_padding.x;
		pos_board.y -= dir_board.y * move_padding.y;
	}

	//set
	void set_pos(Coord new_pos) {
		last_pos_board = Coord(pos_board.x + (move_padding.x * -dir_board.x), pos_board.y);
		pos_board = new_pos;
	}

	void set_step(Coord step = Coord(3, 0)) {
		move_padding = step;
	}

	void set_size(Size new_size) {
		size_board = new_size;
	}

	void set_symbol_board(char new_ch) {
		char_board = new_ch;
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_color_board(Color new_color) {
		color_board = new_color;
	}

	void print() const {
		std::string row(size_board.width, char_board);

		//backround
		cmd.color(color_bg);
		for (int y = 0; y < size_board.height; y++) {
			cmd.gotoxy(last_pos_board.x, last_pos_board.y + y);
			std::cout << row;
		}

		//border
		cmd.color(color_board);
		for (int y = 0; y < size_board.height; y++) {
			cmd.gotoxy(pos_board.x, pos_board.y + y);
			std::cout << row;
		}
	}
	//get
	Coord get_pos() const {
		return pos_board;
	}

	Size get_size() const {
		return size_board;
	}

private:
	Coord last_pos_board;
	Coord pos_board;
	Size size_board = Size(10, 1);
	Dir dir_board = Dir(1, 0);
	Color color_board = Color(7, 7);
	Color color_bg;
	Coord move_padding = Coord(3, 0);
	char char_board = ' ';

	Console cmd;
};



void breakout() {
	Move move;
	Console cmd;
	Plane plane;
	
	Ball ball;
	Block block;
	Board player;
	cmd.resize_screen(Size(220, 55));

	//color
	plane.set_color_bg(Color(15, 15));
	plane.set_color_border(Color(15, 15));
	plane.set_color_plane(Color(0, 0));
	ball.set_color_ball(Color(15, 15));
	ball.set_color_bg(Color(0, 0));
	block.set_color_block(Color(7, 7));
	player.set_color_board(Color(12, 12));

	//plane
	plane.set_pos(Coord(10, 3));
	plane.set_size(Size(201, 50));
	plane.print();

	//player
	player.set_size(Size(15, 2));
	player.set_pos(Coord(rand()%60, plane.get_size().height - player.get_size().height+2));
	
	//ball
	ball.set_dir(Dir(1, -1));
	ball.set_pos(Coord(player.get_pos().x, player.get_pos().y - player.get_size().height));
	ball.set_size(Size(2, 1));
	
	//block
	block.set_pos(Coord(12, 12));
	block.set_size(Size(16, 3));

	//blocks
	std::vector<Block> blocks;
	blocks.assign(10, block);
	size_t size = blocks.size();
	for (size_t i = 0; i < size; i++) {
		blocks[i].add_pos(Coord(i * 20, 0));
	}
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < size; j++) {
			block = blocks[j + (i * size)];
			block.add_pos(Coord(0, 5));
			blocks.push_back(block);
		}
	}
	for (const auto& block : blocks) {
		block.print();
	}
	


	while (true) {
		for (size_t i = 0; i < blocks.size(); i++) {
			ball.collide.create(blocks[i], ball.get_size(), ball.get_pos());
			if (ball.collide.is_any()) {
				if (ball.collide.get_bounce().x != 0) {
					ball.set_dir(Dir(ball.collide.get_bounce().x, ball.get_dir().y));
				}
				if (ball.collide.get_bounce().y != 0) {
					ball.set_dir(Dir(ball.get_dir().x, ball.collide.get_bounce().y));
				}
				blocks[i].set_color_block(Color(0, 0));
				blocks[i].print();
				blocks.erase(blocks.begin() + i);
			}
		}
		ball.collide.create(plane, ball.get_size(), ball.get_pos());
		if (ball.collide.get_bounce().x != 0) {
			ball.set_dir(Dir(ball.collide.get_bounce().x, ball.get_dir().y));
		}
		if (ball.collide.get_bounce().y != 0) {
			ball.set_dir(Dir(ball.get_dir().x, ball.collide.get_bounce().y));
		}
		ball.collide.create(player.get_size(), player.get_pos(), ball.get_size(), ball.get_pos());
		if (ball.collide.get_bounce().x != 0) {
			ball.set_dir(Dir(ball.collide.get_bounce().x, ball.get_dir().y));
		}
		if (ball.collide.get_bounce().y != 0) {
			ball.set_dir(Dir(ball.get_dir().x, ball.collide.get_bounce().y));
		}

		player.move(move);
		if (player.get_pos().x <= plane.get_pos().x + 1) {
			Coord new_pos = Coord(plane.get_pos().x + 1, player.get_pos().y);
			player.set_pos(new_pos);
		}
		if ((player.get_pos().x + player.get_size().width) > plane.get_pos().x + plane.get_size().width - 1) {
			Coord new_pos = Coord(plane.get_pos().x + plane.get_size().width  - player.get_size().width - 1, player.get_pos().y);
			player.set_pos(new_pos);
		}

		ball.print();
		player.print();

		cmd.sleep(50);
		if (ball.get_pos().y >= plane.get_size().height) { // die
			break;
		}
		if (blocks.size() == 0) { // win
			break;
		}
		if (move.now.get_escape()) {
			break;
		}
	}
	cmd.color_reset();
	cmd.clear();
}