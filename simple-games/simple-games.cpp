#include <iostream>
#include <string>
#include "console.h"
#include "shape.h"

int main(){
	Console cmd;
	Plane plane;
	plane.set_size(40, 10);
	plane.set_pos(50, 2);

	plane.set_color_bg(Color(10, 10));
	plane.set_color_plane(Color(11, 11));
	plane.set_color_border(Color(15, 15));

	plane.set_symbol_plane('.');
	plane.set_symbol_border('.');
	for (int i = 1; i <= 50; i++) {
		cmd.sleep(100);
		plane.set_pos(50 - i, 2);
		plane.print_bg(true);
		plane.print_plane();
		plane.print_border();
	}

	cmd.pause();
}