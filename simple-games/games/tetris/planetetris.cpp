#pragma once
#include "collider.cpp"
#include "games/tetris/tetrisblock.cpp"
#include "move.cpp"
#include <utils/console.cpp>

class PlaneTetris : protected Collider
{
public:
	PlaneTetris()
	{
		plane.assign(20, std::string(30, '.'));
	}

	void move(Move& move)
	{
		move.move();
		char button = toupper(move.now.get_button());
		int move_angle = (button == 'E') - (button == 'Q');
		int move_dir_x = move.now.get_dir_x();
		int move_dir_y = move.now.get_dir_y();
		pos_tetris_block.x += move_dir_x;
		pos_tetris_block.y -= move_dir_y;
	}

	void print()
	{
		//tetris block
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
	//collision
	std::vector<std::string> plane;
	std::vector<TetrisBlock> collision_block;

	//move tetris block
	TetrisBlock tetris_block;
	Coord pos_tetris_block;

	Console cmd;
};