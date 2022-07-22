#pragma once

struct Color
{
	Color() {}
	explicit Color(int new_font, int new_bg)
	{
		font = new_font;
		bg = new_bg;
	}
	int get_font() const
	{
		return font;
	}
	int get_bg() const
	{
		return bg;
	}
private:
	int font = 7;
	int bg = 0;
};

struct Dir
{
	Dir() {}
	explicit Dir(int dir_x, int dir_y)
	{
		x = dir_x;
		y = dir_y;
	}
	bool is_zero()
	{
		return (x == 0 && y == 0);
	}
	int x = 0;
	int y = 0;
};

struct Coord
{
	Coord() {}
	explicit Coord(int new_x, int new_y)
	{
		x = new_x;
		y = new_y;
	}
	Coord operator+=(const Coord& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
	Coord operator-=(const Coord& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}
	bool operator==(const Coord& other) const
	{
		return ((x == other.x) && (y == other.y));
	}
	int x = 0;
	int y = 0;
};

struct Size
{
	Size() {}
	explicit Size(int new_width, int new_height)
	{
		width = new_width;
		height = new_height;
	}
	int width = 0;
	int height = 0;
};