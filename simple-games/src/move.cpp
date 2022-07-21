#pragma once
#include "utils/keyboard.cpp"

class Move
{
private:
	Keyboard key;
	class Time
	{
	public:
		int get_dir_x() const
		{
			return dir_x;
		}
		int get_dir_y() const
		{
			return dir_y;
		}
		bool get_space() const
		{
			return space;
		}
		bool get_enter() const
		{
			return enter;
		}
		bool get_escape() const
		{
			return escape;
		}
		unsigned char get_button() const
		{
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

	enum Dir
	{
		left = -1,
		right = 1,
		up = 1,
		down = -1,
	};

	bool w = 0, a = 0, s = 0, d = 0;
public:
	Time now;

	void move()
	{
		now.dir_x = 0;
		now.dir_y = 0;
		now.space = 0;
		now.enter = 0;
		now.escape = 0;
		now.button = 0;

		if (key.kbhit_())
		{
			unsigned char button = toupper(key.getch_());

			//arrow detect:
#ifdef _WIN32
			if (button == 0 || button == 224)
			{
				unsigned char new_button = key.getch_();
				if (new_button == 72)
				{
					button = 'W'; // Up
				}
				if (new_button == 80)
				{
					button = 'S'; // Down
				}
				if (new_button == 75)
				{
					button = 'A'; // Left
				}
				if (new_button == 77)
				{
					button = 'D'; // Right
				}
			}
#endif // Windows

#ifdef __linux__
			if (button == '\033')
			{
				unsigned char new_button = key.getch_();
				new_button = key.getch_();
				if (new_button == 'A')
				{
					button = 'W'; // Up
				}
				if (new_button == 'B')
				{
					button = 'S'; // Down
				}
				if (new_button == 'D')
				{
					button = 'A'; // Left
				}
				if (new_button == 'C')
				{
					button = 'D'; // Right
				}
			}
#endif // Linux

			if (button == 'W')
			{
				now.dir_y = Dir::up;
			}
			if (button == 'S')
			{
				now.dir_y = Dir::down;
			}
			if (button == 'A')
			{
				now.dir_x = Dir::left;
			}
			if (button == 'D')
			{
				now.dir_x = Dir::right;
			}
			if (button == '\r' || button == '\n')
			{
				now.enter = true;
			}
			if (button == ' ')
			{
				now.space = true;
			}
			if (button == 27)
			{
				now.escape = true;
			}
			now.button = button;
		}
	}
};