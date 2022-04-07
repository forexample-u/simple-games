#pragma once
#include <deque>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include "interface.h"
#include "move.h"
#include "core.h"
#include "console.h"
#include "main_menu.h"


class Game_2048 {
private:
	void die_condition() {
		size_t row_len = nums[0].size();
		size_t col_len = nums.size();
		if (full_plane()) { 
			return;
		}

		for (size_t col = 0; col != col_len; col++) {
			for (size_t row = 0; row != row_len - 1; row++) {
				if (nums[col][row] == nums[col][row + 1]) {
					return;
				}
			}
		}

		for (size_t row = 0; row != row_len; row++) {
			for (size_t col = 0; col != col_len - 1; col++) {
				if (nums[col][row] == nums[col + 1][row]) {
					return;
				}
			}
		}
		die = true;
	}

	bool full_plane() {
		for (size_t i = 0; i < nums.size(); i++) {
			for (size_t j = 0; j < nums[i].size(); j++) {
				if (nums[i][j] == 0) {
					return true;
				}
			}
		}
		return false;
	}

	void move_dir(Dir dir_move) {
		size_t row_len = nums[0].size();
		size_t col_len = nums.size();

		if (dir_move.x == -1) {
			for (size_t col = 0; col != col_len; col++) {
				for (size_t row = 0; row != row_len - 1; row++) {
					if (nums[col][row] == 0) {
						std::swap(nums[col][row], nums[col][row + 1]);
					}
				}
			}
		}
		if (dir_move.x == 1) {
			for (size_t col = 0; col != col_len; col++) {
				for (size_t row = row_len - 1; row != 0; row--) {
					if (nums[col][row] == 0) {
						std::swap(nums[col][row], nums[col][row + -1]);
					}
				}
			}
		}
		if (dir_move.y == 1) {
			for (size_t row = 0; row != row_len; row++) {
				for (size_t col = 0; col != col_len - 1; col++) {
					if (nums[col][row] == 0) {
						std::swap(nums[col][row], nums[col + 1][row]);
					}
				}
			}
		}
		if (dir_move.y == -1) {
			for (size_t row = 0; row != row_len; row++) {
				for (size_t col = col_len - 1; col != 0; col--) {
					if (nums[col][row] == 0) {
						std::swap(nums[col][row], nums[col + -1][row]);
					}
				}
			}
		}
	}

	void concatenate_dir(Dir dir_, int animaion_ms) {
		size_t row_len = nums[0].size();
		size_t col_len = nums.size();

		if (dir_.x == -1) { // left
			for (size_t col = 0; col != col_len; col++) {
				for (size_t row = 0; row != row_len - 1; row++) {
					if (nums[col][row] == nums[col][row + 1]) {
						nums[col][row + 1] = nums[col][row + 1] + nums[col][row];
						nums[col][row] = 0;
					}
				}
			}
		}

		if (dir_.x == 1) { //right
			for (size_t col = 0; col != col_len; col++) {
				for (size_t row = row_len - 1; row != 0; row--) {
					if (nums[col][row] == nums[col][row + -1]) {
						nums[col][row] = nums[col][row + -1] + nums[col][row];
						nums[col][row + -1] = 0;
					}
				}
			}
		}

		if (dir_.y == -1) { //up
			for (size_t row = 0; row != row_len; row++) {
				for (size_t col = col_len - 1; col != 0; col--) {
					if (nums[col][row] == nums[col + -1][row]) {
						nums[col][row] = nums[col + -1][row] + nums[col][row];
						nums[col + -1][row] = 0;
					}
				}
			}
		}

		if (dir_.y == 1) { //down
			for (size_t row = 0; row != row_len; row++) {
				for (size_t col = 0; col != col_len - 1; col++) {
					if (nums[col][row] == nums[col + 1][row]) {
						nums[col][row] = nums[col + 1][row] + nums[col][row];
						nums[col + 1][row] = 0;
					}
				}
			}
		}
	}

public:
	Game_2048() {
		nums.assign(count_button.height, std::vector<int>(count_button.width));
		buttons.create(count_button, Size(10, 5), Coord(2, 1), Color(0, 7), Color(0, 0));
		buttons.set_pos_center(true, 1);
		create_rand_num();
	}

	void move(Move& move) {
		move.move();
		dir_move.x = move.now.get_dir_x();
		dir_move.y = move.now.get_dir_y();

		int animaion_ms = 25;

		auto tmp_nums = nums;

		//move
		if (dir_move.x != 0) { // left/right
			for (size_t i = 0; i < nums[0].size(); i++) {
				move_dir(dir_move);
				print();
				cmd.sleep(animaion_ms);
			}
		}
		if (dir_move.y != 0) { // up/down
			for (size_t i = 0; i < nums.size(); i++) {
				move_dir(dir_move);
				print();
				cmd.sleep(animaion_ms);
			}
		}

		concatenate_dir(dir_move, animaion_ms);
		cmd.sleep(animaion_ms * 2);

		//move
		if (dir_move.x != 0) { // left/right
			for (size_t i = 0; i < nums[0].size() / 2; i++) {
				move_dir(dir_move);
				print();
				cmd.sleep(animaion_ms);
			}
		}
		if (dir_move.y != 0) { // up/down
			for (size_t i = 0; i < nums.size() / 2; i++) {
				move_dir(dir_move);
				print();
				cmd.sleep(animaion_ms);
			}
		}

		die_condition();
		if (!dir_move.is_zero()) { // dir not zero
			if (tmp_nums != nums) { // not equals 
				cmd.sleep(100);
				create_rand_num();
			}
		}
	}

	void create_rand_num() {
		if (full_plane()) {
			while (true) {
				int row = rand() % static_cast<int>(nums[0].size());
				int col = rand() % static_cast<int>(nums.size());
				if (nums[col][row] == 0) {
					nums[col][row] = 2 * (1 + rand() % 2);
					break;
				}
			}
		}
	}

	//set
	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_color_button(int num = 4, Color new_color = Color(7, 7)) {
		color_num[num] = new_color;
	}

	//print
	void print() {
		for (size_t i = 0; i < buttons.size(); i++) {
			for (size_t j = 0; j < buttons[0].size(); j++) {
				int num = nums[i][j];
				std::string num_str = std::to_string(num);
				buttons[i][j].set_text(num_str);
				buttons[i][j].set_color_button(color_num[num]);
			}
		}
		buttons.print(true);
	}

	bool is_die() const {
		return die;
	}

private:
	std::vector<std::vector<int>> nums;

	bool die = false;
	MultiButtons buttons;
	Size count_button = Size(4, 4);
	Color color_bg = Color(0, 0);
	Dir dir_move;

	//color button
	std::map<int, Color> color_num{
		{0,  Color(7, 7)},
		{2,  Color(0, 11)},
		{4,  Color(0, 12)},
		{8,  Color(15, 8)},
		{16, Color(15, 9)},
		{32, Color(15, 2)},
		{64, Color(15, 13)},
		{128, Color(0, 6)},
		{256, Color(0, 14)},
		{512, Color(0, 3)},
		{1024, Color(0, 1)},
		{2048, Color(0, 15)}
	};
	
	Console cmd;
};

namespace ListGame {
	void _2048() {
		Plane plane;
		Console cmd;
		Game_2048 game;
		Move move;
		cmd.resize_screen(Size(120, 30));
		srand(time(0));
		plane.set_pos(Coord(33, 1));
		plane.set_size(Size(55, 27));
		plane.set_border_padding(Size(2, 1));
		plane.set_color_plane(Color(15, 15));
		plane.set_color_border(Color(7, 7));
		plane.set_color_bg(Color(0, 0));
		plane.print();

		game.print();
		while (1) {
			game.move(move);
			if (move.now.get_button() != false) {
				game.print();
			}
			if (game.is_die()) {
				break;
			}
			if (move.now.get_escape()) {
				break;
			}
		}
		cmd.pause();
		ListMenu::main_menu();
	}
}