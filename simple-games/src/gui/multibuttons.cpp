#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include "core.cpp"
#include "move.cpp"
#include "shape/plane.cpp"
#include "shape/block.cpp"
#include "utils/console.cpp"
#include "gui/button.cpp"

class MultiButtons
{
public:
	void push_back_buttons(const std::deque<Button>& buttons_row)
	{
		buttons.push_back(buttons_row);
	}

	void push_front_buttons(const std::deque<Button>& buttons_row)
	{
		buttons.push_front(buttons_row);
	}

	//set
	void set_pos(Coord new_pos)
	{
		Coord start_pos = buttons[0][0].get_pos();
		for (std::deque<Button>& buttons_row : buttons)
		{
			for (Button& button : buttons_row)
			{
				Coord old_pos = button.get_pos();
				old_pos += new_pos;
				old_pos -= start_pos;
				button.set_pos(old_pos);
			}
		}
	}

	void add_pos(Coord new_add)
	{
		for (std::deque<Button>& buttons : buttons)
		{
			for (Button& button : buttons)
			{
				Coord old_pos = button.get_pos();
				old_pos += new_add;
				button.set_pos(old_pos);
			}
		}
	}

	void set_pos_center(bool center_x = true, bool center_y = false)
	{
		Console cmd;
		Size size_screen = cmd.get_size_screen();
		Coord pos = buttons[0][0].get_pos();
		int center_pos_x = (size_screen.width - get_size_buttons().width);
		int center_pos_y = (size_screen.height - get_size_buttons().height);
		if (center_x)
		{
			set_pos(Coord(center_pos_x / 2, pos.y));
		}
		if (center_y)
		{
			set_pos(Coord(pos.x, center_pos_y / 2));
		}
		if (center_x || center_y)
		{
			set_pos(Coord(center_pos_x / 2, center_pos_y / 2));
		}
	}

	void create(Size count_button, Size size_button, Coord padding = Coord(2, 1), Color button_color = Color(7, 0), Color bg_color = Color(0, 0))
	{
		Button button;
		button.set_color_bg(bg_color);
		button.set_color_button(button_color);
		button.set_size(size_button);
		for (int y = 0; y < count_button.height; y++)
		{
			std::deque<Button> row;
			for (int x = 0; x < count_button.width; x++)
			{
				button.set_pos(Coord((size_button.width + padding.x) * x, (size_button.height + padding.y) * y));
				row.push_back(button);
			}
			buttons.push_back(row);
		}
	}

	//print
	void print(bool print_bg = true) const
	{
		for (const std::deque<Button>& buttons_row : buttons)
		{
			for (const Button& button : buttons_row)
			{
				button.print(print_bg);
			}
		}
	}

	//get
	Size get_size_buttons() const
	{
		Coord pos_start = buttons[0][0].get_pos();

		int max_index_x = buttons[0].size() - 1;
		int pos_end = buttons[0][max_index_x].get_pos().x + buttons[0][max_index_x].get_size().width;
		int size_x = pos_end - pos_start.x;

		int max_index_y = buttons.size() - 1;
		pos_end = buttons[max_index_y][0].get_pos().y + buttons[max_index_y][0].get_size().height;
		int size_y = pos_end - pos_start.y;
		return Size(size_x, size_y);
	}

	size_t size() const
	{
		return buttons.size();
	}

	std::deque<Button>& operator[](int index)
	{
		return buttons[index];
	}

protected:
	std::deque<std::deque<Button>> buttons;
};