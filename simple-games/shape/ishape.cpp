#pragma once
#include "core.cpp"

class IShape
{
public:
	virtual void set_pos(Coord pos) = 0;
	virtual void set_size(Size size) = 0;
	virtual Coord get_pos() const = 0;
	virtual Size get_size() const = 0;
};