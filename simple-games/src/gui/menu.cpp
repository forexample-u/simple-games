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

class Menu
{
public:
	void move(Move& move)
	{
		move.move();
		int size = static_cast<int>(buttons.size());
		selected_index -= move.now.get_dir_y();
		selected_index %= size;
		if (selected_index < 0)
		{
			selected_index = size - 1;
		}
	}

	void push_button(const Button& button)
	{
		buttons.push_back(button);
	}

	int get_selected_index() const
	{
		return selected_index;
	}

	void set_selected_color(Color color_button)
	{
		selected_color_button = color_button;
	}

	void print() const
	{
		Button button_selected = buttons[selected_index];
		button_selected.set_color_button(selected_color_button);
		for (size_t index = 0; index < buttons.size(); index++)
		{
			if (selected_index != static_cast<int>(index))
			{
				buttons[index].print();
			}
		}
		button_selected.print();
	}

	Button& operator[](int index)
	{
		return buttons[index];
	}

	size_t size() const
	{
		return buttons.size();
	}

private:
	Color selected_color_button = Color(0, 8);
	int selected_index = 0;
	std::vector<Button> buttons;
};