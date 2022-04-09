#pragma once
#include <iostream>

#ifdef _WIN32
#include <conio.h> //This is a test!
#endif

#ifdef __linux__
#include <unistd.h>
#include <termios.h>
#endif

//detect keyboard
class Keyboard {
public:
#ifdef _WIN32
	int getch_() {
		return _getch();
	}

	int kbhit_() {
		return _kbhit();
	}
#endif
#ifdef __linux__
	int getch_() {
		int ch;
		struct termios old_terminal, new_terminal;
		tcgetattr(STDIN_FILENO, &old_terminal);
		new_terminal = old_terminal;
		new_terminal.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
		return ch;
	}

	int kbhit_() {
		static const int STDIN = 0;
		static bool initialized = false;

		if (!initialized) {
			termios term;
			tcgetattr(STDIN, &term);
			term.c_lflag &= ~ICANON;
			tcsetattr(STDIN, TCSANOW, &term);
			setbuf(stdin, 0);
			initialized = true;
		}

		int bytes_waiting;
		ioctl(STDIN, FIONREAD, &bytes_waiting);
		return bytes_waiting;
	}
#endif
};

//move by detect keyboard
class Move {
private:
	Keyboard key;
	class Time {
	public:
		int get_dir_x() const {
			return dir_x;
		}
		int get_dir_y() const {
			return dir_y;
		}
		bool get_space() const {
			return space;
		}
		bool get_enter() const {
			return enter;
		}
		bool get_escape() const {
			return escape;
		}

		unsigned char get_button() const {
			return button;
		}

	private:
		friend Move;
		int dir_x = 0;
		int dir_y = 0;
		bool space = false;
		bool enter = false;
		bool escape = false;
		unsigned char button = 0;
	};

	enum Dir {
		left = -1,
		right = 1,
		up = 1,
		down = -1,
	};

	bool w = 0, a = 0, s = 0, d = 0;
public:
	Time now;

	void move() {
		now.dir_x = 0;
		now.dir_y = 0;
		now.space = 0;
		now.enter = 0;
		now.escape = 0;
		now.button = 0;

		if (key.kbhit_()) {
			unsigned char button = toupper(key.getch_());
			if (button == 'W') {
				now.dir_y = Dir::up;
			}
			if (button == 'S') {
				now.dir_y = Dir::down;
			}
			if (button == 'A') {
				now.dir_x = Dir::left;
			}
			if (button == 'D') {
				now.dir_x = Dir::right;
			}
			if (button == '\r') {
				now.enter = true;
			}
			if (button == ' ') {
				now.space = true;
			}
			if (button == 27) {
				now.escape = true;
			}
			now.button = button;
		}
	}
};