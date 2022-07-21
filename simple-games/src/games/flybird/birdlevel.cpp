#pragma once
#include <iostream>
#include <deque>
#include <string>
#include "utils/console.cpp"
#include "move.cpp"
#include "core.cpp"
#include "shape/plane.cpp"
#include "shape/block.cpp"
#include "entity/collum.cpp"

class BirdLevel
{
public:
	void create_collum(Plane& plane, int min_width = 2, int max_width = 4, int min_height = 2, int max_height = 15)
	{
		Collum collum;
		collum.set_border(plane);
		int width = min_width + (rand() % (max_width - min_width));
		int height = min_height + (rand() % (max_height - min_height));

		pause_seconds -= 1;
		int rand_index = rand() % 11;
		if (pause_seconds < 0)
		{
			collum.create(Size(width, height * 0.7), plane.get_pos());
			if (rand_index < 5)
			{
				collum.set_pos(Coord(collum.get_pos().x, plane.get_pos().y));
			}

			collums.push_back(collum);
			if (rand_index > 6)
			{
				int height_rand = (plane.get_size().height - height) / 4;
				collum.create(Size(width, height_rand), plane.get_pos());
				collum.set_pos(Coord(collum.get_pos().x, plane.get_pos().y));
				collums.push_back(collum);
				pause_seconds += width;
			}

			pause_seconds += width * 2;
		}
	}

	void print(const Plane& plane)
	{
		for (Collum& collum : collums)
		{
			//print backround
			collum.set_color_bg(plane.get_color_plane());
			collum.set_color_collum(plane.get_color_plane());
			collum.print();

			//remove left
			int delete_size = (collum.get_size().width - 2) + plane.get_pos().x + 1;
			if (delete_size > (collum.get_pos().x))
			{
				collums.pop_front();
				continue;
			}

			//print collum
			collum.add_pos(Coord(-1, 0));
			collum.set_color_collum(color_collum);
			collum.print();
		}
	}

	void set_color_bg(Color new_color)
	{
		color_bg = new_color;
	}

	void set_color(Color new_color)
	{
		color_collum = new_color;
	}

	//get
	Collum get_front() const
	{
		return collums.front();
	}

	std::deque<Collum> get_collums() const
	{
		return collums;
	}

private:
	std::deque<Collum> collums;
	Color color_collum;
	Color color_bg;
	int pause_seconds = 0;
};