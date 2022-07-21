#pragma once
#include "apple.cpp"
#include "snake.cpp"

void eat(Snake& snake, Apple& apple)
{
	Coord pos_apple = apple.get_pos();
	snake.get_all_pos();
	if (snake.get_head_pos() == pos_apple)
	{
		apple.destroy();
		snake.add_size_step();
	}
}


namespace ListGame
{
	void _snake()
	{
		Move move;
		Console cmd;
		Plane plane;
		Snake snake;
		Apple apple;

		//resize small resoltion
		cmd.resize_small_screen(Size(120, 30));
		cmd.sleep(100);
		Size screen_now = cmd.get_size_screen();

		//settings:
		Coord step_snake = Coord(2, 1);
		Size size_plane = Size(90, 22);
		Coord pos_plane = Coord((screen_now.width - size_plane.width) / 2, (screen_now.height - size_plane.height) / 2);

		if (screen_now.width >= (size_plane.width * 2 + 10) && screen_now.height >= (size_plane.height * 2 + 5))
		{
			step_snake = Coord(4, 2);
			size_plane = Size(180, 42);
			pos_plane = Coord((screen_now.width - size_plane.width) / 2, (screen_now.height - size_plane.height) / 2);
		}

		int add_sleep = 20;
		int color_bg = 3;
		int color_border = 4;
		int color_plane = 0;
		int color_snake = 15;

		//plane
		plane.set_pos(Coord(pos_plane.x / step_snake.x, pos_plane.y / step_snake.y));
		plane.set_size(Size(size_plane.width / step_snake.x, size_plane.height / step_snake.y));
		plane.set_color_bg(Color(color_bg, color_bg));
		plane.set_color_border(Color(color_border, color_border));
		plane.set_color_plane(Color(color_plane, color_plane));
		plane.set_symbol_border('.');
		plane.set_symbol_plane(' ');

		//snake
		snake.set_pos(Coord(plane.get_pos().x + 1, plane.get_pos().y + 1));
		snake.set_step(step_snake);
		snake.set_color_snake(Color(color_snake, color_snake));
		snake.set_symbol_snake('.');

		//apple
		apple.set_step(step_snake);
		apple.set_symbol_apple(' ');
		apple.set_color_apple(Color(4, 4));
		apple.set_color_bg(Color(color_plane, color_plane));

		//print scale plane
		cmd.sleep(50);
		Plane plane_scale = plane;
		plane_scale.set_pos(Coord(plane.get_pos().x * step_snake.x, plane.get_pos().y * step_snake.y));
		plane_scale.set_size(Size(plane.get_size().width * step_snake.x, plane.get_size().height * step_snake.y));
		plane_scale.set_border_padding(Size(step_snake.x, step_snake.y));
		plane_scale.print();

		while (true)
		{
			snake.move(move);
			snake.set_plane(plane);
			eat(snake, apple);
			snake.print();
			if (move.now.get_dir_x() != 0)
			{
				add_sleep = 65;
			}
			if (move.now.get_dir_y() != 0)
			{
				add_sleep = 60;
			}
			cmd.color(Color(color_bg, color_bg));
			cmd.gotoxy(Coord(0, 0));
			cmd.sleep(add_sleep + 10);
			if (!apple.is_create())
			{
				int random_color = rand() % 3;
				if (random_color == 0)
				{
					apple.set_color_apple(Color(6, 6));
				}
				if (random_color == 1)
				{
					apple.set_color_apple(Color(4, 4));
				}
				if (random_color == 2)
				{
					apple.set_color_apple(Color(2, 2));
				}
				apple.rand_create(plane, snake);
				apple.print();
			}

			if (snake.is_die())
			{
				break;
			}
			if (snake.is_win())
			{
				break;
			}
			if (move.now.get_escape())
			{
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
	}
}