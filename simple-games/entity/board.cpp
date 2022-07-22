#pragma once
#include <iostream>
#include "core.cpp"
#include "utils/console.cpp"
#include "move.cpp"
#include "shape/plane.cpp"

class Board
{
public:
	void move(Move& move)
	{
		move.move();
		last_pos_board = pos_board; //save_pos
		dir_board = Dir(0, 0);
		dir_board.x = move.now.get_dir_x();
		dir_board.y = move.now.get_dir_y();
		pos_board.x += dir_board.x * move_step_board.x;
		pos_board.y -= dir_board.y * move_step_board.y;
	}

	void set_border(Coord border_pos, Size border_size)
	{
		int collision_left = border_pos.x + 1;
		int collision_right = border_pos.x + border_size.width - size_board.width - 1;
		int collision_up = border_pos.y + 1;
		int collision_down = border_pos.y + border_size.height - size_board.height - 1;
		if (collision_left > pos_board.x)
		{
			pos_board.x = collision_left;
		}
		if (collision_right < pos_board.x)
		{
			pos_board.x = collision_right;
		}
		if (collision_down < pos_board.y)
		{
			pos_board.y = collision_down;
		}
		if (collision_up > pos_board.y)
		{
			pos_board.y = collision_up;
		}
	}

	void set_border(IShape& shape)
	{
		set_border(shape.get_pos(), shape.get_size());
	}

	//set
	void set_pos(Coord new_pos)
	{
		last_pos_board = pos_board;
		pos_board = new_pos;
	}

	void set_size(Size new_size)
	{
		size_board = new_size;
	}

	void set_step(Coord new_step)
	{
		move_step_board = new_step;
	}

	void set_symbol_board(char new_ch)
	{
		char_board = new_ch;
	}

	void set_color_board(Color new_color)
	{
		color_board = new_color;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	//print
	void print() const
	{
		std::string row(size_board.width, char_board);

		//backround
		if (!(pos_board == last_pos_board))
		{
			cmd.color(color_bg);
			for (int y = 0; y < size_board.height; y++)
			{
				cmd.gotoxy(last_pos_board.x, last_pos_board.y + y);
				std::cout << row;
			}
		}

		//border
		cmd.color(color_board);
		for (int y = 0; y < size_board.height; y++)
		{
			cmd.gotoxy(pos_board.x, pos_board.y + y);
			std::cout << row << std::flush;
		}
		cmd.color(color_bg);
		cmd.gotoxy(pos_board);
	}

	//get
	Coord get_pos() const
	{
		return pos_board;
	}

	Size get_size() const
	{
		return size_board;
	}

private:
	Coord pos_board;
	Coord last_pos_board;
	Size size_board = Size(10, 1);
	Dir dir_board = Dir(1, 0);
	Color color_board = Color(7, 7);
	Coord move_step_board = Coord(3, 0);
	char char_board = ' ';

	Color color_bg;
	Console cmd;
};