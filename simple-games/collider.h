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
			Dir slice_border;
			Dir slice_inside;
			Dir slice_outside;
			Dir bounce_inside;
			Dir bounce_outside;
			Dir bounce_border;

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
			collide_inside = inside_x && inside_y;


			//slice_border
			slice_border.y += (player_down  == slice_up)    *  1; // up
			slice_border.y += (player_up    == slice_down)  * -1; // down
			slice_border.x += (player_right == slice_left)  * -1; // left
			slice_border.x += (player_left  == slice_right) *  1; // right

			//slice_outside
			slice_outside.y += (player_down+1  == slice_up)    *  1; // up
			slice_outside.y += (player_up      == slice_down)  * -1; // down
			slice_outside.x += (player_right+1 == slice_left)  * -1; // left
			slice_outside.x += (player_left    == slice_right) *  1; // right

			//slice_inside
			slice_inside.y += (player_up    == slice_up    + 1) *  1; // up
			slice_inside.y += (player_down  == slice_down  - 2) * -1; // down
			slice_inside.x += (player_left  == slice_left  + 1) * -1; // left
			slice_inside.x += (player_right == slice_right - 2) *  1; // right

			//bounce_outside
			bounce_outside.y += (inside_x && (slice_outside.y ==  1)) * -1; // up
			bounce_outside.y += (inside_x && (slice_outside.y == -1)) *  1; // down
			bounce_outside.x += (inside_y && (slice_outside.x == -1)) * -1; // left
			bounce_outside.x += (inside_y && (slice_outside.x ==  1)) *  1; // right

			//bounce_border
			bounce_border.y += (inside_x && (slice_border.y ==  1)) * -1; // up
			bounce_border.y += (inside_x && (slice_border.y == -1)) *  1; // down
			bounce_border.x += (inside_y && (slice_border.x == -1)) * -1; // left
			bounce_border.x += (inside_y && (slice_border.x ==  1)) *  1; // right

			//bounce_inside
			bounce_inside.y += (inside_x && (slice_inside.y ==  1)) *  1; // up
			bounce_inside.y += (inside_x && (slice_inside.y == -1)) * -1; // down
			bounce_inside.x += (inside_y && (slice_inside.x == -1)) *  1; // left
			bounce_inside.x += (inside_y && (slice_inside.x ==  1)) * -1; // right


			//fix angle probleam collision
			if (slice_outside.x == -1 && slice_outside.y == 1) { //left up
				bounce_outside = { -1, -1};
			}
			if (slice_outside.x == -1 && slice_outside.y == -1) { //left down
				bounce_outside = { -1, 1 };
			}
			if (slice_outside.x == 1 && slice_outside.y == 1) { // right up
				bounce_outside = { 1, -1 };
			}
			if (slice_outside.x == 1 && slice_outside.y == -1) { // right down
				bounce_outside = { 1, 1 };
			}

			//bool collide and dir
			if (!collide_inside) {
				dir_bounce = bounce_outside;
				collide_outside = (dir_bounce.x != 0 || dir_bounce.y != 0);
			}
			else {
				dir_bounce = bounce_inside;
				collide_inside = (dir_bounce.x != 0 || dir_bounce.y != 0);
			}

			dir_collide = bounce_border;
			collide_border = (dir_collide.x != 0 || dir_collide.y != 0);

			collide_any = collide_inside || collide_outside || collide_border;
		}

		Dir bounce() const {
			return dir_bounce;
		}

		Dir border() const {
			return dir_collide;
		}

		bool is_collide() const {
			return collide_any;
		}

		bool is_outside() const {
			return collide_outside;
		}

		bool is_border() const {
			return collide_border;
		}

		bool is_inside() const {
			return collide_inside;
		}

	private:
		Coord pos_collision;
		Coord pos_player;
		Size size_collision;
		Size size_player;
		bool collide_inside = false;
		bool collide_outside = false;
		bool collide_border = false;
		bool collide_any = false;
		Dir dir_collide;
		Dir dir_bounce;
	};
public:
	Collision collide;
};