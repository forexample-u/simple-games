#pragma once
#include "console.h"
#include <iostream>
#include <conio.h> //This is a test!

//detect keyboard
class Keyboard {
public:
	int _getch() {
		return _getch();
	}

	int _kbhit() {
		return _kbhit();
	}
};

//move by detect keyboard
class Move {
private:
	Console cmd;
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
	private:
		friend Move;
		int dir_x = 0;
		int dir_y = 0;
		bool space = false;
		bool enter = false;
		bool escape = false;
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
		now.dir_y = 0;
		now.dir_x = 0;
		now.space = 0;
		now.enter = 0;
		now.escape = 0;

		if (key._kbhit()) {
			unsigned char button = toupper(key._getch());
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
		}
	}
};