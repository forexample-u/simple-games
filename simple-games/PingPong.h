#pragma once
#include "Breakout.h"

void ping_pong() {
	Plane plane;
	Console cmd;
	Move move;
	Board player;
	Board enemy;
	Ball ball;

	//plane
	plane.set_pos(Coord(0, 2));
	plane.set_size(Size(cmd.get_size_screen().width-5, 25));
	plane.set_color_bg(Color(0, 0));

	int plane_up = plane.get_pos().y;
	int plane_down = plane.get_pos().y + plane.get_size().height - 1;
	int plane_left = plane.get_pos().x;
	int plane_right = plane.get_pos().x + plane.get_size().width - 1;

	cmd.color(Color(15, 15));
	std::string row(plane.get_size().width, '.');
	cmd.gotoxy(plane.get_pos());
	std::cout << row;
	cmd.gotoxy(plane_left, plane_down);
	std::cout << row;

	//player
	player.set_color_board(Color(11, 11));
	player.set_size(Size(2, 4));
	player.set_step(Coord(0, 2));
	player.set_pos(Coord(12, 9));

	//enemy
	enemy.set_pos(Coord(plane_right, plane_down));
	enemy.set_color_board(Color(12, 12));
	enemy.set_size(Size(2, 4));
	enemy.set_step(Coord(0, 1));

	//ball
	ball.set_color_bg(plane.get_color_plane());
	ball.set_dir(Dir(-1, -1));
	ball.set_pos(Coord(plane.get_size().width/2, 7));
	ball.set_color_ball(Color(15, 15));

	int time = 0;
	while (1) {
		time += 1;
		double mult = double(ball.get_pos().x) / double(plane_right);
		int pos_enemy = (ball.get_pos().y + sin(time) * 6) * mult;

		enemy.set_pos(Coord(plane_right - 6, pos_enemy));
		enemy.border(plane);
		enemy.print();

		player.move(move);
		player.border(plane);
		player.print();
		
		ball.detect_collision(plane.get_pos(), plane.get_size());
		ball.detect_collision(enemy.get_pos(), enemy.get_size());
		ball.detect_collision(player.get_pos(), player.get_size());
		ball.print();
		cmd.sleep(60);

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
