#pragma once
#include "move/imove.cpp"
#include "utils/keyboard.cpp"

class KeyboardMove : public IMove
{
public:
	void detect_button() override
	{
		key = 0;
		if (keyboard.kbhit())
		{
			key = keyboard.getch_toupper();
		}
	}

	unsigned char get_button_toupper() const override
	{
		return key;
	}

	int get_dir_x() const override
	{
		return (key == 'D') - (key == 'A');
	}

	int get_dir_y() const override
	{
		return (key == 'W') - (key == 'S');
	}
private:
	unsigned char key = 0;
	Keyboard keyboard;
};