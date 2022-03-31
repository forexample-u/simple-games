#pragma once
#include <iostream>
#include "core.h"
#include "console.h"

class Collider {
private:
	class Collision {
	public:
		void create(Size size_collision, Coord pos_collision, Size size_player, Coord pos_player) {
			this->size_collision = size_collision;
			this->pos_collision = pos_collision;
			this->size_player = size_player;
			this->pos_player = pos_player;

			bool inside_x = (pos_player.x >= pos_collision.x) && (pos_player.x < pos_collision.x + size_collision.width);
			bool inside_y = (pos_player.y >= pos_collision.y) && (pos_player.y < pos_collision.y + size_collision.height);

			collide_inside = (inside_x && inside_y);
			int padding_up = -1, padding_down = 0, padding_left = -1, padding_right = 0;
			if (collide_inside == true) {
				padding_up = 1, padding_down = -2, padding_left = 1, padding_right = -2;
			}

			//border
			Dir slice_bounce;
			if (pos_player.y == pos_collision.y + size_collision.height + padding_down) {
				slice_bounce.y = -1;
			}
			if (pos_player.y == pos_collision.y + padding_up) {
				slice_bounce.y = 1;
			}
			if (pos_player.x == pos_collision.x + size_collision.width + padding_right) {
				slice_bounce.x = -1;
			}
			if (pos_player.x == pos_collision.x + padding_left) {
				slice_bounce.x = 1;
			}
			
			bool left_border  = inside_y && (slice_bounce.x == -1);
			bool right_border = inside_y && (slice_bounce.x ==  1);
			bool up_border    = inside_x && (slice_bounce.y ==  1);
			bool down_border  = inside_x && (slice_bounce.y == -1);

			if (left_border)  { dir_collide.x =  1; }
			if (right_border) { dir_collide.x = -1; }
			if (up_border)    { dir_collide.y = -1; }
			if (down_border)  { dir_collide.y =  1; }
			if (collide_inside) {
				if (left_border)  { dir_collide.x = -1; }
				if (right_border) { dir_collide.x = 1; }
				if (up_border)    { dir_collide.y = 1; }
				if (down_border)  { dir_collide.y = -1; }
			}


			if (down_border && left_border) {
				dir_collide.x = -dir_collide.x;
				dir_collide.y = -dir_collide.y;
			}
			if (up_border && left_border) {
				dir_collide.x = -dir_collide.x;
				dir_collide.y = -dir_collide.y;
			}
			if (up_border && right_border) {
				dir_collide.x = -dir_collide.x;
				dir_collide.y = -dir_collide.y;
			}
			if (down_border && right_border) {
				dir_collide.x = -dir_collide.x;
				dir_collide.y = -dir_collide.y;
			}
		}

		Dir border() const {
			return dir_collide;
		}

		bool is_collide() const {
			return collide_bool;
		}

		bool is_inside() const {
			return collide_inside;
		}

		bool is_outside() const {
			return collide_outside;
		}

	private:
		Coord pos_collision;
		Coord pos_player;
		Size size_collision;
		Size size_player;
		bool collide_inside = false;
		bool collide_outside = false;
		bool collide_bool = false; // <-- rename
		Dir dir_collide;
	};
public:
	Collision collide;
};