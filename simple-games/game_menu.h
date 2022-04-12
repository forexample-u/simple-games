#pragma once
#include "PingPong.h"
#include "Snake.h"
#include "Breakout.h"
#include "interface.h"
#include "FlyBird.h"
#include "2048.h"
#include "main_menu.h"

namespace ListMenu {
	void main_menu();

	void game_menu() {
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
		if (choice == "Snake") {
			ListGame::snake();
		}
		if (choice == "Ping-pong") {
			ListGame::ping_pong();
		}
		if (choice == "Breakout") {
			ListGame::breakout();
		}
		if (choice == "Flappy-Bird") {
			ListGame::flyBird();
		}
		if (choice == "2048") {
			ListGame::_2048();
		}
		if (choice == "Back") {
			ListMenu::main_menu();
		}
	}
}