#pragma once
#include "move.cpp"
#include "games/tetris/planetetris.cpp"

namespace ListGame
{
	void tetris()
	{
		Move move;
		PlaneTetris tetris;

		while (1)
		{
			tetris.move(move);
			tetris.print();
		}
	}
}