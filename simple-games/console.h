#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#include "core.h"

#define Ansi_test

class Console {
public:
	void sleep(int ms) const {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	void gotoxy(Coord pos) const {
		gotoxy(pos.x, pos.y);
	}

#ifndef Ansi_test
	void gotoxy(int x, int y) const {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(x), short(y) });
	}

	void resize_screen(Size size) const {
		std::string str_w = std::to_string(size.width);
		std::string str_h = std::to_string(size.height);
		std::string command = "mode " + str_w + "," + str_h;
		system(command.c_str());
	}

	void pause() const {
		system("pause > nul");
	}

	void clear() const {
		system("cls");
	}

	void color_font(int font_bit) const {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (font_bit % 16));
	}

	void color(Color color) const {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((color.get_bg() % 16) * 16) + (color.get_font() % 16));
	}

	void color_reset() const {
		color_font(7);
	}

	Size get_size_screen() const {
		CONSOLE_SCREEN_BUFFER_INFO screen_info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_info);
		auto screen = screen_info.srWindow;
		return Size(screen.Right - screen.Left + 1, screen.Bottom - screen.Top + 1);
	}
#endif
#ifdef Ansi_test
	void gotoxy(int x, int y) const {
		std::cout << "\033[" << (y + 1) << "d\033[" << (x + 1) << "G";
	}

	void resize_screen(Size size) const {
		std::cout << "\033[8;" << size.height << ";" << size.width << "t";
	}

	//TODO:
	//1. pause()
	//2. get_size_screen()
	void pause() const {
		system("pause > nul");
	}
	Size get_size_screen() const {
		CONSOLE_SCREEN_BUFFER_INFO screen_info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen_info);
		auto screen = screen_info.srWindow;
		return Size(screen.Right - screen.Left + 1, screen.Bottom - screen.Top + 1);
	}

	void clear() const {
		std::cout << "\033c";
	}

	void color_font(int font_bit) const {
		int font = ansi_color_to_windows_color(font_bit);
		std::cout << "\033[38;5;" << font << "m";
	}

	void color(Color color) const {
		int font = ansi_color_to_windows_color(color.get_font());
		int bg = ansi_color_to_windows_color(color.get_bg());
		std::cout << "\033[38;5;" << font << "m";
		std::cout << "\033[48;5;" << bg << "m";
	}

	void color_reset() const {
		std::cout << "\033[0m";
	}
#endif
private:
	//ansi color convert to windows color
	int ansi_color_to_windows_color(int color_bit) const {
		int color = color_bit;
		if (color_bit == 1) { color = 4; };
		if (color_bit == 4) { color = 1; };
		if (color_bit == 3) { color = 6; };
		if (color_bit == 6) { color = 3; };
		if (color_bit == 1 + 8) { color = 4 + 8; };
		if (color_bit == 4 + 8) { color = 1 + 8; };
		if (color_bit == 3 + 8) { color = 6 + 8; };
		if (color_bit == 6 + 8) { color = 3 + 8; };
		return color;
	}
};