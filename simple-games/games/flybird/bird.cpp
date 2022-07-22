#pragma once
#include <iostream>
#include <deque>
#include "utils/console.cpp"
#include "move.cpp"
#include "core.cpp"
#include "shape/plane.cpp"
#include "collider.cpp"
#include "entity/collum.cpp"
#include "birdlevel.cpp"

class Bird : public Collider
{
private:
	bool detect_damage(const Plane& plane)
	{
		//wall
		collide.create(plane, Size(1, 1), pos_bird);
		if (collide.is_outside())
		{
			return true;
		}

		//collums
		for (Collum& collum : collums)
		{
			collide.create(collum.get_size(), collum.get_pos(), Size(1, 1), pos_bird);
			if (collide.is_inside() || collide.is_border())
			{
				return true;
			}
		}
		return false;
	}

	void die_condition(const Plane& plane)
	{
		if (detect_damage(plane) == true)
		{
			count_bounce += 1;
		}
		if (count_bounce > bounce)
		{
			die = true;
		}
	}
public:
	void move(Move& move)
	{
		last_pos_bird = pos_bird;
		move.move();
		int space = move.now.get_space();
		int dir = move.now.get_dir_y();
		if (space || (dir == 1))
		{
			jump();
			cmd.sleep(10);
		}
		if (count_step_fly > step_fly)
		{
			pos_bird.y += 1;
		}
		count_step_fly += 1;
	}

	void jump()
	{
		last_pos_bird = pos_bird;
		pos_bird.y -= 7;
		count_step_fly = 0;
	}

	//set
	void set_pos(Coord new_pos)
	{
		pos_bird = new_pos;
	}

	void set_start_pos(const Plane& plane)
	{
		pos_bird.x = plane.get_pos().x + (plane.get_size().width * 0.5);
		pos_bird.y = plane.get_pos().y + (plane.get_size().height * 0.5);
	}

	void set_plane(const Plane& plane)
	{
		die_condition(plane);
	}

	void set_color_bird(Color new_color)
	{
		color_bird = new_color;
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_symbol_bird(char new_ch)
	{
		char_bird = new_ch;
	}

	//print
	void print() const
	{
		//backround
		cmd.color(color_bg);
		cmd.gotoxy(last_pos_bird);
		std::cout << ' ' << std::flush;

		//symbol color
		cmd.color(color_bird);
		cmd.gotoxy(pos_bird);
		std::cout << char_bird << std::flush;

		cmd.color(color_bg);
	}

	//get
	bool is_die() const
	{
		return die;
	}

	void get_collums(BirdLevel level)
	{
		collums = level.get_collums();
	}

private:
	Coord pos_bird;
	Coord last_pos_bird;
	Color color_bird;
	Color color_bg;
	char char_bird = 'o';

	std::deque<Collum> collums;

	int count_step_fly = 0;
	int step_fly = 1;
	int count_bounce = 0;
	int bounce = 0;
	bool die = false;
	Console cmd;
};