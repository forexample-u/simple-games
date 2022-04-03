#pragma once
#include <iostream>
#include <vector>
#include "core.h"
#include "move.h"
#include "shape.h"

//button
class Button {
public:
	//set
	void set_pos(Coord new_pos) {
		pos = new_pos;
	}

	void add_pos(Coord add_pos) {
		pos += add_pos;
	}

	void set_size(Size new_size) {
		size = new_size;
	}

	void set_pos_center(bool center_x = true, bool center_y = false) {
		Size screen = cmd.get_size_screen();
		if (center_x) { pos.x = (screen.width  * 0.5) - (size.width  * 0.5); }
		if (center_y) { pos.y = (screen.height * 0.5) - (size.height * 0.5); }
	}

	void set_border_padding(Size new_padding) {
		border_padding = new_padding;
	}

	void set_text(std::string new_text) {
		text = new_text;
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_color_border(Color new_color) {
		color_border = new_color;
	}

	void set_color_button(Color new_color) {
		color_button = new_color;
	}

	void set_symbol_bg(char ch) {
		char_bg = ch;
	}
	
	//print
	void print() const {
		Coord padding = Coord(border_padding.width, border_padding.height);
		std::string row_button(size.width - padding.x * 2, ' ');
		std::string text_erase = text.substr(0, size.width);
		int length = static_cast<int>(text_erase.size() * 0.5);
		Coord text_pos = Coord(pos.x + (size.width / 2) - length, pos.y + (size.height / 2) - ((size.height % 2) == 0));
		

		cmd.color(color_bg);
		for (int y = 0; y < size.height - padding.y * 2; y++) {
			cmd.gotoxy(pos.x + padding.x + size.width, pos.y + padding.y + y);
			std::cout << char_bg;
		}

		cmd.color(color_button);
		for (int y = 0; y < size.height - padding.y * 2; y++) {
			cmd.gotoxy(pos.x + padding.x, pos.y + padding.y + y);
			std::cout << row_button;
		}

		cmd.color(color_button);
		cmd.gotoxy(text_pos);
		std::cout << text_erase;

		cmd.color(color_bg);
	}

	//get
	Coord get_pos() const {
		return pos;
	}

	Size get_size() const {
		return size;
	}

	std::string get_text() const {
		return text;
	}

	Color get_color_button() const {
		return color_button;
	}

	Color get_color_bg() const {
		return color_bg;
	}

	Color get_color_border() const {
		return color_border;
	}

private:
	Size border_padding;
	Coord pos = Coord(0, 0);
	Size size = Size(20, 3);
	Color color_button = Color(0, 15);
	Color color_bg = Color(0, 0);
	Color color_border;
	char char_bg = '.';
	std::string text;
	Console cmd;
};

//menu
class Menu {
public:
	void move(Move& move) {
		move.move();
		int size = static_cast<int>(buttons.size());
		selected_index -= move.now.get_dir_y();
		selected_index %= size;
		if (selected_index < 0) {
			selected_index = size - 1;
		}
	}

	void push_button(const Button& button) {
		buttons.push_back(button);
	}

	int get_selected_index() const {
		return selected_index;
	}

	void set_selected_color(Color color_button) {
		selected_color_button = color_button;
	}

	void print() const {
		Button button_selected = buttons[selected_index];
		button_selected.set_color_button(selected_color_button);
		for (size_t index = 0; index < buttons.size(); index++) {
			if (selected_index != index) {
				buttons[index].print();
			}
		}
		button_selected.print();
	}

	Button& operator[](int index) {
		return buttons[index];
	}

	size_t size() const {
		return buttons.size();
	}

private:
	Color selected_color_button = Color(0, 8);
	int selected_index = 0;
	std::vector<Button> buttons;
};

namespace MakeMenu {
	//make_menu
	std::string center_menu(std::vector<std::string> list_menu, Color color_bg = Color(0, 0), Color color_button = Color(0, 11),
		Color color_selected = Color(0, 12), int pos_y = 5, int size_y = 3, int padding_y = 4, double scale_x = 0.375) {

		Plane plane;
		Move move;
		Console cmd;
		Menu menu;
		Button button;

		menu.set_selected_color(color_selected);
		plane.set_color_bg(color_bg);
		button.set_color_bg(color_bg);
		button.set_color_button(color_button);
		button.set_pos(Coord(0, pos_y));
		Size screen_size = cmd.get_size_screen();
		button.set_size(Size(screen_size.width * scale_x, size_y));
		button.set_pos_center(1, 0);
		for (const auto& button_word : list_menu) {
			button.set_text(button_word);
			menu.push_button(button);
			button.add_pos(Coord(0, padding_y));
		}
		
		plane.set_size(Size(0, 0));
		plane.print_bg();
		menu.print();
		while (true) {
			Size screen_size_now = cmd.get_size_screen();
			if (abs(screen_size_now.width - screen_size.width) >= 5 || screen_size_now.width <= 20) {
				cmd.clear();
				cmd.color(color_bg);
				for (int y = 0; y < screen_size_now.height; y++) {
					cmd.gotoxy(0, y);
					std::cout << '.';
				}

				for (size_t i = 0; i < menu.size(); i++) {
					menu[i].set_size(Size(screen_size_now.width * scale_x, menu[i].get_size().height));
					menu[i].set_pos_center(1, 0);
					int pos_x = menu[i].get_pos().x - 4;
					if (pos_x <= 0) { pos_x = 0; }
					menu[i].set_pos(Coord(pos_x, menu[i].get_pos().y));
				}
				menu.print();
				cmd.sleep(20);
				screen_size = cmd.get_size_screen();
			}

			menu.move(move);
			cmd.sleep(60);
			if (move.now.get_button() != false) {
				menu.print();
			}
			if (move.now.get_enter() || move.now.get_space()) {
				menu.print();
				break;
			}
		}
		int index_menu = menu.get_selected_index();
		return list_menu[index_menu];
	}
}