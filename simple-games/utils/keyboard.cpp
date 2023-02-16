#pragma once
#include <iostream>

#ifdef _WIN32
#include <conio.h> //This is a test!
#endif  // Windows

#ifdef __linux__
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#endif  // Linux

class Keyboard {
public:
	int getch_toupper()
	{
		int button = toupper(this->getch());

		//arrow detect:
#ifdef _WIN32
		if (button == 0 || button == 224)
		{
			unsigned char new_button = this->getch();
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
			unsigned char new_button = this->getch();
			new_button = this->getch();
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
		return button;
	}

#ifdef _WIN32
	int getch()
	{
		return _getch();
	}

	int kbhit()
	{
		return _kbhit();
	}
#endif // Windows
#ifdef __linux__
	int getch()
	{
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

	int kbhit()
	{
		static const int STDIN = 0;
		static bool initialized = false;

		if (!initialized)
		{
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
#endif // Linux
};
