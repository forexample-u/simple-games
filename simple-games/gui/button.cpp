#pragma once
#include <iostream>
#include "core.cpp"
#include "utils/console.cpp"

class Button
{
public:
	//set
	void set_pos(Coord new_pos)
	{
		pos = new_pos;
	}

	void add_pos(Coord add_pos)
	{
		pos += add_pos;
	}

	void set_size(Size new_size)
	{
		size = new_size;
	}

	void set_pos_center(bool center_x = true, bool center_y = false)
	{
		Size screen = cmd.get_size_screen();
		if (center_x)
		{
			pos.x = (screen.width * 0.5) - (size.width * 0.5);
		}
		if (center_y)
		{
			pos.y = (screen.height * 0.5) - (size.height * 0.5);
		}
	}

	void set_border_padding(Size new_padding)
	{
		border_padding = new_padding;
	}

	void set_text(std::string new_text)
	{
		text = new_text;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_color_border(Color new_color)
	{
		color_border = new_color;
	}

	void set_color_button(Color new_color)
	{
		color_button = new_color;
	}

	void set_symbol_bg(char new_ch)
	{
		char_bg = new_ch;
	}

	//print
	void print(bool print_bg = true) const
	{
		Coord padding = Coord(border_padding.width, border_padding.height);
		std::string row_button(size.width - padding.x * 2, ' ');
		std::string text_erase = text.substr(0, size.width);
		int length = static_cast<int>(text_erase.size() * 0.5);
		Coord text_pos = Coord(pos.x + (size.width / 2) - length, pos.y + (size.height / 2) - ((size.height % 2) == 0));

		if (print_bg)
		{
			cmd.color(color_bg);
			for (int y = 0; y < size.height - padding.y * 2; y++)
			{
				cmd.gotoxy(pos.x + padding.x + size.width, pos.y + padding.y + y);
				std::cout << char_bg << std::flush;
			}
		}

		cmd.color(color_button);
		for (int y = 0; y < size.height - padding.y * 2; y++)
		{
			cmd.gotoxy(pos.x + padding.x, pos.y + padding.y + y);
			std::cout << row_button << std::flush;
		}

		cmd.color(color_button);
		cmd.gotoxy(text_pos);
		std::cout << text_erase << std::flush;
		cmd.gotoxy(text_pos.x + length + 1, text_pos.y);

		cmd.color(color_bg);
	}

	//get
	Coord get_pos() const
	{
		return pos;
	}

	Size get_size() const
	{
		return size;
	}

	std::string get_text() const
	{
		return text;
	}

	Color get_color_button() const
	{
		return color_button;
	}

	Color get_color_bg() const
	{
		return color_bg;
	}

	Color get_color_border() const
	{
		return color_border;
	}

private:
	Size border_padding;
	Coord pos = Coord(0, 0);
	Size size = Size(20, 3);
	Color color_button = Color(0, 15);
	Color color_bg = Color(0, 0);
	Color color_border;
	char char_bg = '.';
	std::string text;
	Console cmd;
};