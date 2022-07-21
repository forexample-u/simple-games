#pragma once
#include <iostream>
#include <vector>
#include "core.cpp"
#include "utils/console.cpp"
#include "move.cpp"
#include "shape/plane.cpp"
#include "shape/block.cpp"
#include "collider.cpp"
#include <ctime>
#include "entity/ball.cpp"
#include "entity/board.cpp"

namespace ListGame
{
	void breakout()
	{
		Move move;
		Console cmd;
		Plane plane;

		Ball ball;
		Block block;
		Board player;
		cmd.resize_small_screen(Size(137, 41));
		cmd.sleep(100);
		Size screen = cmd.get_size_screen();

		//settings:
		Size player_size = Size(38, 1);
		Size plane_size = Size(128, 39);
		Coord plane_pos = Coord((screen.width - plane_size.width) / 2, (screen.height - plane_size.height) / 2);
		Size block_count = Size(11, 5);
		Size block_size = Size(8, 2);
		Size block_padding = Size(2, 1);
		Coord player_step = Coord(3, 0);
		Coord block_offset = Coord(10, 2);
		int color_bg = 15;
		int color_plane = 0;
		int color_border = 15;
		int color_ball = 15;


		//color
		plane.set_color_bg(Color(color_bg, color_bg));
		plane.set_color_border(Color(color_border, color_border));
		plane.set_color_plane(Color(color_plane, color_plane));
		ball.set_color_ball(Color(color_ball, color_ball));
		ball.set_color_bg(Color(color_plane, color_plane));
		block.set_color_block(Color(7, 7));
		player.set_color_board(Color(12, 12));
		player.set_color_bg(Color(color_plane, color_plane));

		//calc settings
		block_padding.width += block_size.width;
		block_padding.height += block_size.height;

		//plane
		plane.set_pos(plane_pos);
		plane.set_size(plane_size);

		//player
		player.set_pos(Coord(plane_pos.x + (rand() % (plane_size.width - player_size.width - 1)) + 1, plane_pos.y + plane_size.height - player_size.height - 1));
		player.set_size(player_size);
		player.set_step(player_step);

		//ball
		ball.set_pos(Coord(player.get_pos().x, player.get_pos().y - player_size.height - 2));
		ball.set_size(Size(2, 1));
		ball.set_dir(Dir(1 + (rand() % 2) * -2, -1));

		//blocks
		block.set_size(block_size);
		std::vector<Block> blocks;
		for (int y = 0; y < block_count.height; y++)
		{
			block.set_pos(block_offset);
			block.add_pos(Coord(0, block_padding.height * y));
			block.add_pos(plane_pos);
			for (int x = 0; x < block_count.width; x++)
			{
				blocks.push_back(block);
				block.add_pos(Coord(block_padding.width, 0));
			}
		}

		plane.print();
		for (const auto& block : blocks)
		{
			block.print();
		}

		clock_t clock_old = std::clock();
		clock_t clock_now = std::clock();
		clock_t clock_first = std::clock();
		clock_t speed_add = 2;
		clock_t sleep_ball_ms = ((block_count.width * block_count.height) * speed_add) - 20;
		clock_t first_sleep_ms = 2500;
		while (true)
		{
			player.move(move);
			player.set_border(plane);
			player.print();

			cmd.sleep(30);
			clock_now = std::clock();
			if ((clock_old + sleep_ball_ms < clock_now) && (clock_first + first_sleep_ms < clock_now))
			{
				for (size_t i = 0; i < blocks.size(); i++)
				{
					ball.detect_collision(blocks[i].get_pos(), blocks[i].get_size());
					if (ball.collide.is_any())
					{
						blocks[i].set_color_block(plane.get_color_plane());
						blocks[i].print();
						blocks.erase(blocks.begin() + i);
						if (speed_add + 10 <= sleep_ball_ms)
						{
							sleep_ball_ms -= speed_add;
						}

					}
				}
				ball.detect_collision(player.get_pos(), player.get_size());
				ball.detect_collision(plane.get_pos(), plane.get_size());
				ball.print();
				clock_old = std::clock();
			}
			if (clock_first + first_sleep_ms > clock_now)
			{
				cmd.sleep(100);
			}

			if (ball.get_pos().y >= plane_pos.y + plane_size.height - 2)
			{
				break; // die
			}
			if (blocks.empty())
			{
				break; // win
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