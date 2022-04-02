#pragma once
#include <iostream>
#include "core.h"
#include "console.h"

class Collider {
private:
	struct Obj {
		Obj() {}
		Obj(Coord pos, Size size) {
			x = pos.x, y = pos.y;
			width = size.width, height = size.height;
		}
		Obj(Size size, Coord pos) {
			x = pos.x, y = pos.y;
			width = size.width, height = size.height;
		}
		int x;
		int y;
		int width;
		int height;
	};

	class Collision {
	public:
		void create(Size size_collision, Coord pos_collision, Size size_player, Coord pos_player) {
			Obj player = { pos_player, size_player };
			Obj collide = { pos_collision, size_collision };
			Dir slice_inside;
			Dir slice_outside;
			Dir slice_border;
			Dir slice_border_inside;
			Dir slice_border_outside;
			Dir bounce_inside;
			Dir bounce_outside;
			Dir bounce_border;
			Dir bounce_border_inside;
			Dir bounce_border_outside;
			
			int player_right = player.x + player.width - 1;
			int player_left = player.x;
			int player_down = player.y + player.height - 1;
			int player_up = player.y;

			int slice_right = collide.x + collide.width;
			int slice_left = collide.x;
			int slice_down = collide.y + collide.height;
			int slice_up = collide.y;

			//collide_inside
			bool inside_x = (player_right >= slice_left) && (player_left < slice_right);
			bool inside_y = (player_down >= slice_up) && (player_up < slice_down);
			
			//slice_outside
			slice_outside.y += (player_down+1  == slice_up)    *  1; // up
			slice_outside.y += (player_up      == slice_down)  * -1; // down
			slice_outside.x += (player_right+1 == slice_left)  * -1; // left
			slice_outside.x += (player_left    == slice_right) *  1; // right

			//slice_inside
			slice_inside.y += (player_up-1    == slice_up)    *  1; // up
			slice_inside.y += (player_down+2  == slice_down)  * -1; // down
			slice_inside.x += (player_left-1  == slice_left)  * -1; // left
			slice_inside.x += (player_right+2 == slice_right) *  1; // right

			//slice_border
			slice_border.y += (player_down   == slice_up)    *  1; // up
			slice_border.y += (player_up+1   == slice_down)  * -1; // down
			slice_border.x += (player_right  == slice_left)  * -1; // left
			slice_border.x += (player_left+1 == slice_right) *  1; // right

			//slice_border_outside
			slice_border_outside.y += (player_up      == slice_up)    * -1; // up
			slice_border_outside.y += (player_down+1  == slice_down)  *  1; // down
			slice_border_outside.x += (player_left    == slice_left)  *  1; // left
			slice_border_outside.x += (player_right+1 == slice_right) * -1; // right
			
			//slice_border_inside
			slice_border_inside.y += (player_up-1    == slice_up)    *  1; // up
			slice_border_inside.y += (player_down+2  == slice_down)  * -1; // down
			slice_border_inside.x += (player_left-1  == slice_left)  * -1; // left
			slice_border_inside.x += (player_right+2 == slice_right) *  1; // right


			//bounce_outside
			bounce_outside.y += (inside_x && (slice_outside.y == 1))  * -1; // up
			bounce_outside.y += (inside_x && (slice_outside.y == -1)) *  1; // down
			bounce_outside.x += (inside_y && (slice_outside.x == -1)) * -1; // left
			bounce_outside.x += (inside_y && (slice_outside.x == 1))  *  1; // right

			//bounce_inside
			bounce_inside.y += (inside_x && (slice_inside.y ==  1)) *  1; // up
			bounce_inside.y += (inside_x && (slice_inside.y == -1)) * -1; // down
			bounce_inside.x += (inside_y && (slice_inside.x == -1)) *  1; // left
			bounce_inside.x += (inside_y && (slice_inside.x ==  1)) * -1; // right

			//bounce_border
			bounce_border.y += (inside_x && (slice_border.y ==  1)) * -1; // up
			bounce_border.y += (inside_x && (slice_border.y == -1)) *  1; // down
			bounce_border.x += (inside_y && (slice_border.x == -1)) * -1; // left
			bounce_border.x += (inside_y && (slice_border.x ==  1)) *  1; // right

			//bounce_border_outside
			bounce_border_outside.y += (inside_x && (slice_border_outside.y ==  1)) *  1; // up
			bounce_border_outside.y += (inside_x && (slice_border_outside.y == -1)) * -1; // down
			bounce_border_outside.x += (inside_y && (slice_border_outside.x == -1)) *  1; // left
			bounce_border_outside.x += (inside_y && (slice_border_outside.x ==  1)) * -1; // right

			//bounce_border_inside
			bounce_border_inside.y += (inside_x && (slice_border_inside.y ==  1)) * -1; // up
			bounce_border_inside.y += (inside_x && (slice_border_inside.y == -1)) *  1; // down
			bounce_border_inside.x += (inside_y && (slice_border_inside.x == -1)) * -1; // left
			bounce_border_inside.x += (inside_y && (slice_border_inside.x ==  1)) *  1; // right


			//fix angle probleam collision
			if (slice_outside.x == -1 && slice_outside.y == 1) { //left up
				bounce_outside = Dir(-1, -1);
			}
			if (slice_outside.x == -1 && slice_outside.y == -1) { //left down
				bounce_outside = Dir(-1, 1);
			}
			if (slice_outside.x == 1 && slice_outside.y == 1) { // right up
				bounce_outside = Dir(1, -1);
			}
			if (slice_outside.x == 1 && slice_outside.y == -1) { // right down
				bounce_outside = Dir(1, 1);
			}


			//bool collide and dir
			border_inside = false;
			border_outside = false;
			border = false;
			inside = false;
			outside = false;
			any = false;

			dir_collide = bounce_border;
			border = (bounce_border.x != 0 || bounce_border.y != 0); 
			border_inside = (bounce_border_inside.x != 0 || bounce_border_inside.y != 0) && !border;
			border_outside = (bounce_border_outside.x != 0 || bounce_border_outside.y != 0) && !border;

			inside = (inside_x && inside_y) && !border;
			outside = !inside;

			if (inside) {
				dir_bounce = bounce_inside;
				border_inside = (bounce_inside.x != 0 || bounce_inside.y != 0);
			}
			if (outside) {
				dir_bounce = bounce_outside;
				border_outside = (bounce_outside.x != 0 || bounce_outside.y != 0);
			}

			any = inside || border_outside || border;
		}

		void create(const IShape& shape, Size size_player, Coord pos_player) {
			create(shape.get_size(), shape.get_pos(), size_player, pos_player);
		}

		//get 
		Dir get_bounce() const {
			return dir_bounce;
		}

		Dir get_border() const {
			return dir_collide;
		}

		bool is_any() const {
			return any;
		}

		bool is_border() const {
			return border;
		}

		bool is_border_outside() const {
			return border_outside;
		}

		bool is_border_inside() const {
			return border_inside;
		}

		bool is_inside() const {
			return inside;
		}

		bool is_outside() const {
			return outside;
		}

	private:
		bool border_inside = false;
		bool border_outside = false;
		bool border = false;
		bool inside = false;
		bool outside = false;
		bool any = false;
		Dir dir_collide;
		Dir dir_bounce;
	};
public:
	Collision collide;
protected:
	Collision collide_inner;
};