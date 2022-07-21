#pragma once
#include <iostream>
#include <vector>
#include "core.cpp"
#include "utils/console.cpp"
#include "move.cpp"
#include "shape/plane.cpp"
#include "shape/block.cpp"
#include "collider.cpp"
#include <ctime>

class Ball : public Collider
{
public:
	void add_move()
	{
		pos_ball.x += dir_ball.x;
		pos_ball.y += dir_ball.y;
	}

	//print
	void print() const
	{
		std::string row(size_ball.width, char_ball);

		cmd.color(color_bg);
		for (int y = 0; y < size_ball.height; y++)
		{
			cmd.gotoxy(pos_ball.x, pos_ball.y + y);
			std::cout << row << std::flush;
		}

		pos_ball.x += dir_ball.x;
		pos_ball.y += dir_ball.y;

		cmd.color(color_ball);
		for (int y = 0; y < size_ball.height; y++)
		{
			cmd.gotoxy(pos_ball.x, pos_ball.y + y);
			std::cout << row << std::flush;
		}
		cmd.color(color_bg);
		cmd.gotoxy(pos_ball);
	}

	void detect_collision(Coord collision_pos, Size collision_size)
	{
		collide.create(collision_size, collision_pos, size_ball, pos_ball);
		if (collide.get_bounce().x != 0)
		{
			set_dir(Dir(collide.get_bounce().x, dir_ball.y));
		}
		if (collide.get_bounce().y != 0)
		{
			set_dir(Dir(dir_ball.x, collide.get_bounce().y));
		}
	}

	//set
	void set_pos(Coord new_pos)
	{
		pos_ball = new_pos;
	}

	void set_size(Size new_size)
	{
		size_ball = new_size;
	}

	void set_dir(Dir new_dir)
	{
		dir_ball = new_dir;
	}

	void set_color_ball(Color new_color)
	{
		color_ball = new_color;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_symbol_ball(char new_ch)
	{
		char_ball = new_ch;
	}

	//get
	Coord get_pos() const
	{
		return pos_ball;
	}

	Size get_size() const
	{
		return size_ball;
	}

	Dir get_dir() const
	{
		return dir_ball;
	}

private:
	mutable Coord pos_ball;
	Size size_ball = Size(1, 1);
	Dir dir_ball = Dir(1, 1);
	Color color_ball = Color(0, 15);
	Color color_bg;
	char char_ball = ' ';
	Console cmd;
	std::vector<Block> collisions;
};