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

class Keyboard
{
public:
#ifdef _WIN32
	int getch_()
	{
		return _getch();
	}

	int kbhit_()
	{
		return _kbhit();
	}
#endif // Windows
#ifdef __linux__
	int getch_()
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

	int kbhit_()
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