#pragma once
#include "Breakout.h"
#include <cmath>
#include <ctime>

namespace ListGame {
	void ping_pong() {
		Plane plane;
		Console cmd;
		Move move;
		Board player;
		Board enemy;
		Ball ball;

		Size screen_size = Size(119, 30);
		Color color_bg = Color(0, 0);
		Color color_ball = Color(15, 15);
		cmd.resize_screen(screen_size);

		//plane
		plane.set_pos(Coord(0, 2));
		plane.set_size(Size(screen_size.width - 5, 25));
		plane.set_symbol_bg(' ');
		plane.set_color_bg(color_bg);
		plane.set_color_border(color_bg);
		plane.set_color_plane(color_bg);

		int plane_up = plane.get_pos().y;
		int plane_down = plane.get_pos().y + plane.get_size().height - 1;
		int plane_left = plane.get_pos().x;
		int plane_right = plane.get_pos().x + plane.get_size().width - 1;

		//player
		player.set_pos(Coord(plane_left + 3, plane_down - player.get_size().height - 6));
		player.set_size(Size(2, 7));
		player.set_step(Coord(0, 3));
		player.set_color_board(Color(11, 11));
		player.set_color_bg(color_bg);

		//enemy
		enemy.set_pos(Coord(plane_right, plane_down - player.get_size().height - 6));
		enemy.set_size(Size(2, 6));
		enemy.set_step(Coord(0, 1));
		enemy.set_color_board(Color(12, 12));
		enemy.set_color_bg(color_bg);

		//ball
		bool print_ball = true;
		ball.set_color_bg(plane.get_color_plane());
		ball.set_dir(Dir(1, -1));
		ball.set_pos(Coord(plane.get_size().width / 2, 4 + rand() % 15));
		ball.set_color_ball(color_ball);
		ball.set_size(Size(2, 1));

		//print plane
		cmd.sleep(200);
		plane.print();
		cmd.color(Color(15, 15));
		std::string row(plane.get_size().width, ' ');
		cmd.gotoxy(plane_left, plane_up);
		std::cout << '.' << row << std::flush;
		cmd.gotoxy(plane_left, plane_down);
		std::cout << '.' << row << std::flush;

		int count_step_move_enemy = 0;
		int step_move_enemy = 10;
		int rand_move_enemy = rand() % 2;

		clock_t rand_move_ms = 1500;
		clock_t clock_old = std::clock();
		clock_t clock_now = std::clock();

		while (true) {
			//enemy move calc
			double dist_ball_enemy = double(ball.get_pos().x) / double(enemy.get_pos().x);
			int pos_enemy = (ball.get_pos().y + (sin(double(clock_now) * 0.01) * rand_move_enemy)) * dist_ball_enemy;
			if (dist_ball_enemy < 0.5) {
				pos_enemy = enemy.get_pos().y;
			}
			if (ball.get_dir().x == -1) {
				count_step_move_enemy += 1;
				if (count_step_move_enemy > step_move_enemy) {
					pos_enemy = enemy.get_pos().y;
				}
			}
			else { count_step_move_enemy = 0; }
			clock_now = std::clock();
			if (clock_now > (clock_old + rand_move_ms)) {
				rand_move_enemy = (rand() % (ball.get_size().height + rand() % 8)) - (rand() % 3);
				clock_old = clock_now;
			}



			enemy.set_pos(Coord(plane_right - 6, pos_enemy));
			Size screen_size = cmd.get_size_screen();
			if (screen_size.width-5 > enemy.get_pos().x) {
				enemy.set_border(plane);
				enemy.print();
			}
			


			player.move(move);
			player.set_border(plane);
			player.print();

			ball.detect_collision(plane.get_pos(), plane.get_size());
			ball.detect_collision(enemy.get_pos(), enemy.get_size());
			ball.detect_collision(plane.get_pos(), plane.get_size());
			ball.detect_collision(player.get_pos(), player.get_size());
			ball.detect_collision(plane.get_pos(), plane.get_size());
			if (screen_size.width - 4 > ball.get_pos().x) {
				print_ball = true;
				ball.set_color_ball(color_ball);
				ball.print();
			}
			else {
				if (print_ball == true) {
					ball.set_color_ball(color_bg);
					ball.print();
					ball.set_color_ball(color_ball);
				}
				print_ball = false;
				ball.add_move();
			}
			cmd.sleep(30);

			if (ball.get_pos().x >= plane_right - 2) { //win
				break;
			}
			if (ball.get_pos().x <= plane_left + 1) { //die
				break;
			}
		}
		cmd.color_reset();
		cmd.clear();
	}
}
