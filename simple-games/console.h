#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "core.h"

#ifdef _WIN32
#include <Windows.h>
#endif // Windows

#ifdef __linux__
#include <sys/ioctl.h>
#include <unistd.h>
#endif // Linux

class Console {
public:
	~Console() {
		std::cout.flush();
	}

	void sleep(int ms) const {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

	void gotoxy(Coord pos) const {
		gotoxy(pos.x, pos.y);
	}

#ifdef _WIN32
	void gotoxy(int x, int y) const {
		SetConsoleCursorPosition(h, { short(x), short(y) });
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
		color(Color(font_bit, 0));
	}

	void color(Color color) const {
		SetConsoleTextAttribute(h, ((color.get_bg() % 16) * 16) + (color.get_font() % 16));
	}

	void color_reset() const {
		color_font(7);
	}

	Size get_size_screen() const {
		CONSOLE_SCREEN_BUFFER_INFO screen_info;
		GetConsoleScreenBufferInfo(h, &screen_info);
		auto screen = screen_info.srWindow;
		return Size(screen.Right - screen.Left + 1, screen.Bottom - screen.Top + 1);
	}
private:
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
#endif // Windows

#ifdef __linux__
	void gotoxy(int x, int y) const {
		std::cout << "\033[" << (y + 1) << "d\033[" << (x + 1) << "G" << std::flush;
	}

	void resize_screen(Size size) const {
		std::cout << "\033[8;" << size.height << ";" << size.width << "t" << std::flush;
	}

	void pause() const {
		system("bash -c \'read -n 1 -s\'");
	}

	Size get_size_screen() const {
		struct winsize screen;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &screen);
		return Size(screen.ws_col, screen.ws_row);
	}

	void clear() const {
		std::cout << "\033c" << std::flush;
	}

	void color_font(int font_bit) const {
		int font = ansi_color_to_windows_color(font_bit);
		std::cout << "\033[38;5;" << font << "m" << std::flush;
	}

	void color(Color color) const {
		int font = ansi_color_to_windows_color(color.get_font());
		int bg = ansi_color_to_windows_color(color.get_bg());
		std::cout << "\033[38;5;" << font << "m\033[48;5;" << bg << "m";
	}

	void color_reset() const {
		std::cout << "\033[0m" << std::flush;
	}
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
#endif // Linux
};