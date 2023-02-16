#pragma once
#include "collider.cpp"
#include "games/tetris/tetrisblock.cpp"
#include "move/imove.cpp"
#include <utils/console.cpp>

class PlaneTetris : protected Collider
{
public:
	PlaneTetris()
	{
		plane.assign(20, std::string(30, '.'));
	}

	void move(const IMove& move)
	{
		char button = move.get_button_toupper();
		int move_angle = (button == 'E') - (button == 'Q');
		pos_tetris_block.x += move.get_dir_x();
		pos_tetris_block.y -= move.get_dir_y();
	}

	void print()
	{
		std::vector<std::string> tetris_blocks = tetris_block.get_blocks();
		Coord pos = tetris_block.get_pos();

		for (size_t i = 0; i < tetris_blocks.size(); i++)
		{
			for (size_t j = 0; j < tetris_blocks[i].size(); j++)
			{
				if (tetris_blocks[i][j] == 'o')
				{
					plane[i + pos.y][j + pos.x] = tetris_blocks[i][j];
				}
			}
		}

		for (size_t i = 0; i < plane.size(); i++)
		{
			for (size_t j = 0; j < plane[i].size(); j++)
			{
				std::cout << plane[i][j];
			}
			std::cout << "\n";
		}

		cmd.sleep(100);
		cmd.clear();
	}
private:
	std::vector<std::string> plane;
	std::vector<TetrisBlock> collision_block;

	TetrisBlock tetris_block;
	Coord pos_tetris_block;

	Console cmd;
};