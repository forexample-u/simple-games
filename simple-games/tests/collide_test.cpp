#pragma once
#include "core.cpp"
#include "move.cpp"
#include "utils/console.cpp"
#include "entity/ball.cpp"
#include "shape/plane.cpp"

namespace ListTest
{
	void collide_test()
	{
		Console cmd;
		Move move;
		Ball ball;
		cmd.resize_small_screen(Size(120, 30));
		ball.set_color_ball(Color(11, 11));
		srand(time(0));
		if (rand() % 2)
		{
			ball.set_dir(Dir(-1, -1));
		}
		ball.set_size(Size(1 + rand() % 10, 1 + rand() % 3));
		ball.set_pos(Coord(ball.get_size().width + 1 + rand() % 50, 2 + rand() % 6));

		std::vector<Plane> planes;
		Plane plane;
		plane.set_color_border(Color(15, 15));
		plane.set_color_plane(Color(0, 0));
		plane.set_size(Size(118, 29));
		plane.set_pos(Coord(0, 0));
		plane.print_border();
		plane.print_plane();
		planes.push_back(plane);

		plane.set_color_border(Color(12, 12));
		plane.set_size(Size(30, 10));
		plane.set_pos(Coord(15, 11));
		plane.print_border();
		planes.push_back(plane);

		plane.set_color_border(Color(13, 13));
		plane.set_size(Size(20, 13));
		plane.set_pos(Coord(61, 12));
		plane.print_border();
		planes.push_back(plane);

		plane.set_color_border(Color(11, 11));
		plane.set_size(Size(10, 5));
		plane.set_pos(Coord(107, 1));
		plane.print_border();
		planes.push_back(plane);

		while (1)
		{
			ball.print();
			for (const auto& plane_ : planes) {
				ball.collide.create(plane_.get_size(), plane_.get_pos(), ball.get_size(), ball.get_pos());
				if (ball.collide.get_bounce().y != 0)
				{
					ball.set_dir(Dir(ball.get_dir().x, ball.collide.get_bounce().y));
				}
				if (ball.collide.get_bounce().x != 0)
				{
					ball.set_dir(Dir(ball.collide.get_bounce().x, ball.get_dir().y));
				}
			}
			cmd.sleep(60);
			move.move();
			if (move.now.get_button() != false)
			{
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
	}
}