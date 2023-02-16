#pragma once
#include <deque>
#include "shape/ishape.cpp"
#include "move/imove.cpp"
#include "utils/console.cpp"
#include "collider.cpp"

class Snake : protected Collider
{
private:
	bool detect_damage(const IShape& plane)
	{
		if (dir.is_zero())
		{
			return false;
		}

		for (size_t i = 0; i < pos_all.size() - 1; i++)
		{
			if (pos_all[i] == pos_head)
			{
				return true;
			}
		}

		Snake::collide.create(plane, Size(1, 1), pos_head);
		return Snake::collide.is_border();
	}

	void die_condition(const IShape& shape)
	{
		if (detect_damage(shape))
		{
			pos_head.x -= dir.x;
			pos_head.y += dir.y;
			pos_all.push_front(pos_tail);
			pos_all.pop_back();
			count_bounce += 1;
		}
		else
		{
			count_bounce = 0;
		}
		die = count_bounce > bounce;
	}

	void win_condition(const IShape& shape)
	{
		int win_size = (shape.get_size().width - 2) * (shape.get_size().height - 2);
		win = size_snake >= win_size;
	}
public:
	void move(const IMove& move)
	{
		Dir move_dir = Dir(move.get_dir_x(), move.get_dir_y());
		if (!move_dir.is_zero())
		{
			if (move_dir.x != 0 && dir.x == 0)
			{
				dir = move_dir;
			}
			if (move_dir.y != 0 && dir.y == 0)
			{
				dir = move_dir;
			}
		}
		pos_head.x += dir.x;
		pos_head.y -= dir.y;
		pos_all.push_back(pos_head);
		pos_tail = pos_all.front();
		if (size_snake <= static_cast<int>(pos_all.size()))
		{
			pos_all.pop_front();
		}
	}

	void print() const
	{
		if ((size_snake >= static_cast<int>(pos_all.size())) || (size_snake == 0))
		{
			cmd.color(color_bg);
			for (int y = 0; y < step_snake.y; y++)
			{
				cmd.gotoxy(pos_tail.x * step_snake.x, pos_tail.y * step_snake.y + y);
				std::cout << std::string(step_snake.x, ' ') << std::flush;
				cmd.gotoxy(pos_tail.x * step_snake.x, pos_tail.y * step_snake.y + y);
			}
		}

		cmd.color(color_snake);
		for (int y = 0; y < step_snake.y; y++)
		{
			cmd.gotoxy(pos_head.x * step_snake.x, pos_head.y * step_snake.y + y);
			std::cout << std::string(step_snake.x, '.') << std::flush;
			cmd.gotoxy(pos_head.x * step_snake.x, pos_head.y * step_snake.y + y);
		}
		cmd.color(Color(color_bg.get_bg(), color_bg.get_bg()));
		cmd.gotoxy(pos_tail.x * step_snake.x, pos_tail.y * step_snake.y);
	}

	void set_pos(Coord new_pos)
	{
		pos_head = new_pos;
		pos_all.back() = new_pos;
	}

	void set_plane(const IShape& plane)
	{
		die_condition(plane);
		win_condition(plane);
	}

	void set_color_snake(Color new_color)
	{
		color_snake = new_color;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_symbol_snake(char new_ch)
	{
		char_snake = new_ch;
	}

	void set_step(Coord new_step)
	{
		step_snake = new_step;
	}

	void add_size_step()
	{
		size_snake += add_size;
	}

	bool is_die() const
	{
		return die;
	}

	bool is_win() const
	{
		return win;
	}

	Coord get_step() const
	{
		return step_snake;
	}

	Coord get_head_pos() const
	{
		return pos_head;
	}

	std::deque<Coord> get_all_pos() const
	{
		return pos_all;
	}
private:
	//inside parameter
	Coord step_snake = Coord(2, 1);
	Coord pos_head;
	Coord pos_tail;
	Dir dir;
	Color color_snake;
	Color color_bg;

	std::deque<Coord> pos_all{ Coord(0, 0) };
	int count_bounce = 0;
	char char_snake = ' ';
	bool die = false;
	bool win = false;

	int size_snake = 1;
	int add_size = 1;
	int speed = 0;
	int bounce = 4;
	int skin = 0;

	Console cmd;
};