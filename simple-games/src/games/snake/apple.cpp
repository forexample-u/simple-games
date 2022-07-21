#pragma once
#include <deque>
#include "shape/ishape.cpp"
#include "move.cpp"
#include "utils/console.cpp"
#include "collider.cpp"
#include "snake.cpp"

class Apple
{
public:
	~Apple()
	{
		destroy();
	}

	void create(Coord new_pos)
	{
		pos_apple = new_pos;
		exist_apple = true;
	}

	void rand_create(IShape& shape, const Snake& snake)
	{
		pos_apple = snake.get_all_pos()[0];
		bool create_apple = false;
		while (!create_apple)
		{
			create_apple = true;
			for (const auto& pos_snake : snake.get_all_pos())
			{
				if (pos_apple == pos_snake)
				{
					pos_apple.x = (rand() % (shape.get_size().width - 2)) + shape.get_pos().x + 1;
					pos_apple.y = (rand() % (shape.get_size().height - 2)) + shape.get_pos().y + 1;
					create_apple = false;
					break;
				}
			}
		}
		create(pos_apple);
	}
	
	//set
	void set_color_apple(Color new_color)
	{
		color_apple = new_color;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_symbol_apple(char new_ch = '$')
	{
		char_apple = new_ch;
	}

	void set_step(Coord new_step)
	{
		step_apple = new_step;
	}

	//print
	void print() const
	{
		cmd.color(color_apple);
		for (int y = 0; y < step_apple.y; y++)
		{
			cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
			std::cout << std::string(step_apple.x, char_apple) << std::flush;
			cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
		}
	}

	void destroy()
	{
		if (is_create())
		{
			cmd.color(color_bg);
			for (int y = 0; y < step_apple.y; y++)
			{
				cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
				std::cout << std::string(step_apple.x, ' ') << std::flush;
				cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
			}
			exist_apple = false;
		}
	}

	//get
	Coord get_pos() const
	{
		return pos_apple;
	}

	bool is_create() const
	{
		return exist_apple;
	}

private:
	Coord pos_apple;
	Coord step_apple = Coord(2, 1);
	Color color_apple = Color(7, 4);
	Color color_bg;
	bool exist_apple = false;
	char char_apple = '$';
	Console cmd;
};