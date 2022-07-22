#pragma once
#include <vector>
#include <string>
#include "core.cpp"

class TetrisBlock
{
public:
	TetrisBlock()
	{
		create_shape(id_shape, id_rotate);
	}

	TetrisBlock(int id_shape)
	{
		create_shape(id_shape, id_rotate);
	}

	//set
	void set_pos(Coord new_pos)
	{
		pos_tetris_block = new_pos;
	}

	void add_pos(Coord new_add)
	{
		pos_tetris_block += new_add;
	}

	void set_shape(int id_shape = 6)
	{
		create_shape(id_shape, id_rotate);
	}

	void set_rotate(int id_rotate = 4)
	{
		if (id_rotate < 0)
		{
			id_rotate = 4;
		}
		create_shape(id_shape, id_rotate);
	}

	void add_rotate(int dir = 1)
	{
		id_rotate += dir;
		if (id_rotate < 0)
		{
			id_rotate = 4;
		}
		create_shape(id_shape, id_rotate);
	}

	//get
	std::vector<std::string>& get_blocks()
	{
		return tetris_block;
	}

	Coord get_pos() const
	{
		return pos_tetris_block;
	}

private:
	void create_shape(int id_shape, int id_rotate)
	{
		this->id_shape = id_shape;
		this->id_rotate = id_rotate;

		char tetris_symbol = 'o'; //symbol shape position
		std::vector<std::string> tetris_shape;

		//box
		if (id_shape == 0)
		{
			tetris_shape = { "oo..", "oo..", "....", "...." };
		}

		//line
		if (id_shape == 1 && (id_rotate % 2) == 0)
		{
			tetris_shape = { "oooo", "....", "....", "...." };
		}
		if (id_shape == 1 && (id_rotate % 2) == 1)
		{
			tetris_shape = { "o...", "o...", "o...", "o..." };
		}

		//shape1
		if (id_shape == 2 && (id_rotate % 4) == 0)
		{
			tetris_shape = { "o...", "oo..", "o...", "...." };
		}
		if (id_shape == 2 && (id_rotate % 4) == 1)
		{
			tetris_shape = { ".o..", "ooo.", "....", "...." };
		}
		if (id_shape == 2 && (id_rotate % 4) == 2)
		{
			tetris_shape = { "..o.", ".oo.", "..o.", "...." };
		}
		if (id_shape == 2 && (id_rotate % 4) == 3)
		{
			tetris_shape = { "ooo.", ".o..", "....", "...." };
		}

		//shape2
		if (id_shape == 3 && (id_rotate % 2) == 0)
		{
			tetris_shape = { "o...", "oo..", ".o..", "...." };
		}
		if (id_shape == 3 && (id_rotate % 2) == 1)
		{
			tetris_shape = { ".oo.", "oo..", "....", "...." };
		}

		//shape2 invert
		if (id_shape == 4 && (id_rotate % 2) == 0)
		{
			tetris_shape = { ".o..", "oo..", "o...", "...." };
		}
		if (id_shape == 4 && (id_rotate % 2) == 1)
		{
			tetris_shape = { "oo..", ".oo.", "....", "...." };
		}

		//shape3
		if (id_shape == 5 && (id_rotate % 4) == 0)
		{
			tetris_shape = { "oo..", "o...", "o...", "...." };
		}
		if (id_shape == 5 && (id_rotate % 4) == 1)
		{
			tetris_shape = { "o...", "ooo.", "....", "...." };
		}
		if (id_shape == 5 && (id_rotate % 4) == 2)
		{
			tetris_shape = { ".o..", ".o..", "oo..", "...." };
		}
		if (id_shape == 5 && (id_rotate % 4) == 3)
		{
			tetris_shape = { "ooo.", "..o.", "....", "...." };
		}

		//shape3 invert
		if (id_shape == 6 && (id_rotate % 4) == 0)
		{
			tetris_shape = { "oo..", ".o..", ".o..", "...." };
		}
		if (id_shape == 6 && (id_rotate % 4) == 1)
		{
			tetris_shape = { "ooo.", "o...", "....", "...." };
		}
		if (id_shape == 6 && (id_rotate % 4) == 2)
		{
			tetris_shape = { "o...", "o...", "oo..", "...." };
		}
		if (id_shape == 6 && (id_rotate % 4) == 3)
		{
			tetris_shape = { "..o.", "ooo.", "....", "...." };
		}

		tetris_block = tetris_shape;
	}

private:
	Coord pos_tetris_block;
	std::vector<std::string> tetris_block;
	int id_shape = 0;
	int id_rotate = 0;
};