#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "utils/console.cpp"
#include "core.cpp"
#include "shape/plane.cpp"

class Collum
{
public:
	void print() const
	{
		cmd.color(color_collum);
		int size_vec = static_cast<int>(shape.size());
		for (int i = 0; i < size_vec; i++)
		{
			cmd.gotoxy(pos_collum.x, pos_collum.y + i);
			std::cout << shape[i];
			std::cout.flush();
		}
		cmd.color(color_bg);
		cmd.gotoxy(pos_collum.x - 1, pos_collum.y);
	}

	void create(Size new_size, Coord new_pos)
	{
		std::string shape_row(new_size.width, ' ');
		for (int i = 0; i < new_size.height; i++)
		{
			shape.emplace_back(shape_row);
		}
		size_collum.height = new_size.height;
		find_width();

		pos_collum.x = border_plane.width - new_size.width + new_pos.x;
		pos_collum.y = border_plane.height - new_size.height + new_pos.y;
	}

	//set
	void set_pos(Coord new_pos)
	{
		pos_collum = new_pos;
	}

	void add_pos(Coord add_pos)
	{
		pos_collum += add_pos;
	}

	void set_color_collum(Color new_color)
	{
		color_collum = new_color;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_border(Plane& plane)
	{
		border_plane = plane.get_size();
	}

	//get
	Coord get_pos() const
	{
		return pos_collum;
	}

	Size get_size() const
	{
		return size_collum;
	}

private:
	void find_width()
	{
		for (const auto& x : shape)
		{
			int size_arr = static_cast<int>(x.size());
			if (size_arr > size_collum.width)
			{
				size_collum.width = size_arr;
			}
		}
	}
	std::vector<std::string> shape;
	Coord pos_collum;
	Size border_plane;
	Size size_collum;
	Color color_collum;
	Color color_bg;
	Console cmd;
};