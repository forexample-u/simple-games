#pragma once
#include "core.cpp"

class IMove
{
public:
	virtual void detect_button() = 0;
	virtual unsigned char get_button_toupper() const = 0;
	virtual int get_dir_x() const = 0;
	virtual int get_dir_y() const = 0;
};