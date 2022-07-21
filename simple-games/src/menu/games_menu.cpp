#pragma once
#include "gui/makemenu.cpp"
#include "games/pingpong/pingpong.cpp"
#include "games/breakout/breakout.cpp"
#include "games/flybird/flybird.cpp"
#include "games/2048/_2048.cpp"
#include "games/snake/_snake.cpp"

namespace ListMenu
{
	void main_menu();

	void games_menu()
	{
		Console cmd;
		cmd.resize_small_screen(Size(10, 30));
		std::vector<std::string> list_games{
			"Snake",
			"Ping-pong",
			"Breakout",
			"Flappy-Bird",
			"2048",
			"Back"
		};

		MakeMenu menu;
		std::string choice = menu.center_menu(list_games);

		cmd.color_reset();
		cmd.clear();
		if (choice == "Snake")
		{
			ListGame::_snake();
		}
		if (choice == "Ping-pong")
		{
			ListGame::ping_pong();
		}
		if (choice == "Breakout")
		{
			ListGame::breakout();
		}
		if (choice == "Flappy-Bird")
		{
			ListGame::fly_bird();
		}
		if (choice == "2048")
		{
			ListGame::_2048();
		}
		if (choice == "Back")
		{
			main_menu();
		}
	}
}