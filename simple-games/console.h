#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#include "core.h"

class Console {
public:
	void sleep(int ms) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	void gotoxy(int x, int y) const {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(x), short(y) });
	}

	void gotoxy(Coord pos) const {
		gotoxy(pos.x, pos.y);
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
		Size size_screen;
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen);
		size_screen.width = (screen.srWindow.Right - screen.srWindow.Left + 1);
		size_screen.height = (screen.srWindow.Bottom - screen.srWindow.Top + 1);
		return size_screen;
	}
};