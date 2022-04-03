#pragma once
#include "PingPong.h"
#include "Snake.h"
#include "Breakout.h"
#include "interface.h"

void game_menu() {
	Console cmd;
	std::vector<std::string> list_games {
		"Snake",
		"Ping-pong",
		"Breakout"
	};
	std::string choice = MakeMenu::center_menu(list_games, Color(0, 0), Color(0, 11), Color(0, 12), 5, 3, 4, 0.375);
	
	cmd.color_reset();
	cmd.clear();
	if (choice == "Snake") {
		start_snake();
	}
	if (choice == "Ping-pong") {
		ping_pong();
	}
	if (choice == "Breakout") {
		breakout();
	}
}