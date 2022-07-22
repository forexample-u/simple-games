#pragma once
#include "utils/console.cpp"
#include "move.cpp"
#include "core.cpp"
#include "shape/plane.cpp"
#include "birdlevel.cpp"
#include "bird.cpp"

namespace ListGame
{
	void fly_bird()
	{
		Console cmd;
		Move move;
		Bird bird;
		Plane plane;

		Color color_plane = Color(11, 11);
		Color color_bg = Color(0, 0);
		Color color_collum = Color(0, 0);
		Color color_bird = Color(15, 15);

		//plane
		plane.set_size(Size(100, 25));
		plane.set_pos(Coord(0, 0));
		plane.set_color_bg(color_bg);
		plane.set_color_plane(color_plane);
		plane.set_color_border(color_plane);

		//bird
		bird.set_color_bg(plane.get_color_plane());
		bird.set_color_bird(color_bird);

		BirdLevel level;
		level.set_color(color_collum);
		while (true)
		{
			move.move();
			Size screen_size = cmd.get_size_screen();
			if (screen_size.width < 50)
			{
				screen_size.width = 50;
				cmd.resize_screen(screen_size);
			}

			if (screen_size.height < 20)
			{
				screen_size.height = 20;
				cmd.resize_screen(screen_size);
			}

			int padding_height = (screen_size.height / 7) * 2;
			plane.set_size(Size(screen_size.width - 4, screen_size.height - padding_height));
			plane.set_pos(Coord(2, padding_height * 0.5));
			plane.print();

			bird.set_start_pos(plane);
			bird.set_color_bird(Color(15, 15));
			bird.set_plane(plane);

			bird.print();
			cmd.sleep(100);
			if (move.now.get_space() || (move.now.get_dir_y() == 1))
			{
				bird.set_plane(plane);
				bird.print();
				bird.jump();
				break;
			}
		}

		cmd.clear();
		Size screen_size = cmd.get_size_screen();
		int padding_height = ((screen_size.height / 7) * 2);
		plane.set_size(Size(screen_size.width - 2, screen_size.height - padding_height));
		plane.set_pos(Coord(0, padding_height * 0.5));
		plane.print();
		Size size_plane = plane.get_size();
		int max_width = size_plane.width / 15;
		int max_height = size_plane.height / 2 - 2;
		int min_width = size_plane.width / 30 + 1;
		int min_height = size_plane.height / 10;
		while (true)
		{
			level.create_collum(plane, min_width, max_width, min_height, max_height);
			level.print(plane);
			cmd.sleep(((size_plane.width * 0.5) / (size_plane.width / 40 + size_plane.height / 30)) + 15);
			if (bird.is_die())
			{
				bird.set_color_bird(Color(12, 12));
				bird.print();
				break;
			}
			bird.get_collums(level);
			bird.move(move);
			bird.set_plane(plane);
			bird.print();
		}
		cmd.pause();
		cmd.sleep(500);
		cmd.color_reset();
		cmd.clear();
	}
}