#pragma once
#include <deque>
#include "shape/ishape.cpp"
#include "move.cpp"
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

		//snake self
		for (size_t i = 0; i < pos_all.size() - 1; i++)
		{
			if (pos_all[i] == pos_head)
			{
				return true;
			}
		}

		//wall collide
		Snake::collide.create(plane, Size(1, 1), pos_head);
		if (Snake::collide.is_border())
		{
			return true;
		}

		return false;
	}

	void die_condition(const IShape& shape)
	{
		if (detect_damage(shape))
		{ //if detect damage snake go back
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
	void move(Move& move)
	{
		move.move();
		Dir move_dir = Dir(move.now.get_dir_x(), move.now.get_dir_y());
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

	//print
	void print() const
	{
		//snake_tail print
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

		//snake print
		cmd.color(color_snake);
		bool print_all = false;
		if (print_all) //TODO: make print_all
		{
			for (const auto& pos_snake : pos_all)
			{
				cmd.gotoxy(pos_snake.x * step_snake.x, pos_snake.y * step_snake.y);
				std::cout << std::string(step_snake.x, char_snake);
			}
			std::cout.flush();
		}
		else //snake_head print
		{
			for (int y = 0; y < step_snake.y; y++)
			{
				cmd.gotoxy(pos_head.x * step_snake.x, pos_head.y * step_snake.y + y);
				std::cout << std::string(step_snake.x, '.') << std::flush;
				cmd.gotoxy(pos_head.x * step_snake.x, pos_head.y * step_snake.y + y);
			}
		}
		cmd.color(Color(color_bg.get_bg(), color_bg.get_bg()));
		cmd.gotoxy(pos_tail.x * step_snake.x, pos_tail.y * step_snake.y);
	}

	//set
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

	//get
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

	//inside parameter
	std::deque<Coord> pos_all{ Coord(0, 0) };
	int count_bounce = 0;
	char char_snake = ' ';
	bool die = false;
	bool win = false;

	//shop parameter
	int size_snake = 1;
	int add_size = 1;
	int speed = 0;
	int bounce = 4;
	int skin = 0;

	//console
	Console cmd;
};