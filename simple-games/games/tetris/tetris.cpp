#pragma once
#include "move/keyboardmove.cpp"
#include "games/tetris/planetetris.cpp"

namespace ListGame
{
	void tetris()
	{
		KeyboardMove move;
		PlaneTetris tetris;

		while (true)
		{
			move.detect_button();
			tetris.move(move);
			tetris.print();
		}
	}
}