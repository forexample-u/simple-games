#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>

class Console {
public:
	void sleep(int ms) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	void gotoxy(int x, int y) const {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(x), short(y) });
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

	void color(int font_bit, int bg_bit) const {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((bg_bit % 16) * 16) + (font_bit % 16));
	}

	int get_height() const {
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen);
		return (screen.srWindow.Bottom - screen.srWindow.Top + 1);
	}

	int get_width() const {
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen);
		return (screen.srWindow.Right - screen.srWindow.Left + 1);
	}
};