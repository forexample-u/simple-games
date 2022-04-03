#pragma once
#include "interface.h"
#include "move.h"

enum List_main_menu {
	main_start = 0,
	main_test = 1,
	main_settings = 2,
	main_quit = 3,
};

void main_menu() {
	Plane plane;
	Move move;
	Console cmd;
	Menu menu;
	Button button;
	cmd.resize_screen(Size(120, 30));
	//color
	int color_bg = 0; // 0 3
	int color_button = 11;
	int color_button_selected = 12;
	int color_button_font = 0;
	int color_button_font_selected = 0;
	int padding = 4;

	menu.set_selected_color(Color(color_button_font_selected, color_button_selected));
	button.set_color_button(Color(color_button_font, color_button));

	plane.set_color_bg(Color(color_bg, color_bg));
	button.set_color_bg(Color(color_bg, color_bg));

	button.set_size(Size((cmd.get_size_screen().width) / 3, 3));
	button.set_pos_center(1, 0);
	button.set_pos(Coord(button.get_pos().x, button.get_pos().y + 5));
	
	
	button.set_text("Start");
	menu.push_button(button);
	button.set_text("Test");
	button.add_pos(Coord(0, padding));
	menu.push_button(button);
	button.set_text("Settings");
	button.add_pos(Coord(0, padding));
	menu.push_button(button);
	button.set_text("Quit");
	button.add_pos(Coord(0, padding));
	menu.push_button(button);

	plane.set_size(Size(0, 0));
	plane.print_bg();


	Size screen_size = cmd.get_size_screen();
	menu.print();
	while (1) {
		bool screen_resize = false;
		Size screen_size_now = cmd.get_size_screen();
		if (abs(screen_size_now.width - screen_size.width) >= 5 || screen_size_now.width <= 20) {
			cmd.color(Color(color_bg, color_bg));
			for (size_t i = 0; i < menu.size(); i++) {
				Button button_tmp = menu[i];
				button_tmp.set_symbol_bg(' ');
				button_tmp.set_text("");
				button_tmp.set_color_button(plane.get_color_bg());
				button_tmp.print();
			}
			cmd.clear();
			cmd.color(Color(color_bg, color_bg));
			for (size_t i = 0; i < screen_size_now.height; i++) {
				cmd.gotoxy(0, i);
				std::cout << '.';
			}

			for (size_t i = 0; i < menu.size(); i++) {
				menu[i].set_size(Size((screen_size_now.width)/3, menu[i].get_size().height));
				menu[i].set_pos_center(1, 0);
				int pos_x = menu[i].get_pos().x - 4;
				if (pos_x <= 0) { pos_x = 0; }
				menu[i].set_pos(Coord(pos_x, menu[i].get_pos().y));
			}
			menu.print();
			cmd.sleep(10);
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
	int button_index = menu.get_selected_index();
	cmd.color_reset();
	cmd.clear();
	if (button_index == List_main_menu::main_start) {
		//TODO: start menu
	}
	if (button_index == List_main_menu::main_test) {
		//TODO: test menu
	}
	if (button_index == List_main_menu::main_settings) {
		//TODO: settings menu
	}
	if (button_index == List_main_menu::main_quit) {
		return;
	}
}
