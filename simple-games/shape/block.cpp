#pragma once
#include <iostream>
#include "utils/console.cpp"
#include "core.cpp"
#include "ishape.cpp"

class Block : public IShape
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

	void set_border_padding(Size new_padding)
	{
		border_padding = new_padding;
	}

	void set_color_block(Color new_color)
	{
		color_block = new_color;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_color_border(Color new_color)
	{
		color_border = new_color;
	}

	void set_symbol_block(char new_ch)
	{
		char_block = new_ch;
	}

	void set_symbol_border(char new_ch)
	{
		char_border = new_ch;
	}

	//print
	void print() const
	{
		Coord padding = Coord(border_padding.width, border_padding.height);
		//block
		std::string row_block(size.width - padding.x * 2, char_block);
		cmd.color(color_block);
		for (int y = 0; y < size.height - padding.y * 2; y++)
		{
			cmd.gotoxy(pos.x + padding.x, pos.y + padding.y + y);
			std::cout << row_block << std::flush;
		}

		//border
		std::string line(size.width, char_border);
		std::string collum(padding.x, char_border);
		cmd.color(color_border);
		for (int y = 0; y < size.height; y++)
		{
			cmd.gotoxy(pos.x, y + pos.y);
			std::cout << collum << std::flush;
			cmd.gotoxy(size.width + pos.x - padding.x, y + pos.y);
			std::cout << collum << std::flush;
		}
		for (int y = 0; y < padding.y; y++)
		{
			cmd.gotoxy(pos.x, pos.y + y);
			std::cout << line << std::flush;
			cmd.gotoxy(pos.x, pos.y + size.height - 1 - y);
			std::cout << line << std::flush;
		}
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

	Color get_color_block() const
	{
		return color_block;
	}

	Color get_color_bg() const
	{
		return color_bg;
	}

	Color get_color_border() const
	{
		return color_border;
	}

protected:
	Coord pos = Coord(0, 0);
	Size size = Size(2, 2);
	Size border_padding = Size(0, 0);

	Color color_block;
	Color color_bg;
	Color color_border;
	char char_block = ' ';
	char char_border = ' ';
	Console cmd;
};