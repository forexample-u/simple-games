#pragma once
#include "core.cpp"
#include "shape/ishape.cpp"

class Collider
{
private:
	class Collision
	{
	public:
		void create(Size size_collision, Coord pos_collision, Size size_player, Coord pos_player)
		{
			Dir slice_inside;
			Dir slice_outside;
			Dir slice_border;
			Dir bounce_inside;
			Dir bounce_outside;
			Dir bounce_border;

			int player_right = pos_player.x + size_player.width - 1;
			int player_left = pos_player.x;
			int player_down = pos_player.y + size_player.height - 1;
			int player_up = pos_player.y;

			int slice_right = pos_collision.x + size_collision.width;
			int slice_left = pos_collision.x;
			int slice_down = pos_collision.y + size_collision.height;
			int slice_up = pos_collision.y;

			//collide_inside
			bool inside_x = (player_right >= slice_left) && (player_left < slice_right);
			bool inside_y = (player_down >= slice_up) && (player_up < slice_down);

			//slice_outside
			slice_outside.y += (player_down + 1 == slice_up) * 1; // up
			slice_outside.y += (player_up == slice_down) * -1; // down
			slice_outside.x += (player_right + 1 == slice_left) * -1; // left
			slice_outside.x += (player_left == slice_right) * 1; // right

			//slice_inside
			slice_inside.y += (player_up - 1 == slice_up) * 1; // up
			slice_inside.y += (player_down + 2 == slice_down) * -1; // down
			slice_inside.x += (player_left - 1 == slice_left) * -1; // left
			slice_inside.x += (player_right + 2 == slice_right) * 1; // right

			//slice_border
			slice_border.y += (player_down == slice_up || player_up == slice_up) * 1; // up
			slice_border.y += (player_up + 1 == slice_down || player_down + 1 == slice_down) * -1; // down
			slice_border.x += (player_right == slice_left || player_left == slice_left) * -1; // left
			slice_border.x += (player_left + 1 == slice_right || player_right + 1 == slice_right) * 1; // right


			//bounce_outside
			bounce_outside.y += (inside_x && (slice_outside.y == 1)) * -1; // up
			bounce_outside.y += (inside_x && (slice_outside.y == -1)) * 1; // down
			bounce_outside.x += (inside_y && (slice_outside.x == -1)) * -1; // left
			bounce_outside.x += (inside_y && (slice_outside.x == 1)) * 1; // right

			//bounce_inside
			bounce_inside.y += (inside_x && (slice_inside.y == 1)) * 1; // up
			bounce_inside.y += (inside_x && (slice_inside.y == -1)) * -1; // down
			bounce_inside.x += (inside_y && (slice_inside.x == -1)) * 1; // left
			bounce_inside.x += (inside_y && (slice_inside.x == 1)) * -1; // right

			//bounce_border
			bounce_border.y += (inside_x && (slice_border.y == 1)) * -1; // up
			bounce_border.y += (inside_x && (slice_border.y == -1)) * 1; // down
			bounce_border.x += (inside_y && (slice_border.x == -1)) * -1; // left
			bounce_border.x += (inside_y && (slice_border.x == 1)) * 1; // right

			//fix angle probleam collision
			if (slice_outside.x == -1 && slice_outside.y == 1)
			{
				bounce_outside = Dir(-1, -1); // left up
			}
			if (slice_outside.x == -1 && slice_outside.y == -1)
			{
				bounce_outside = Dir(-1, 1); // left down
			}
			if (slice_outside.x == 1 && slice_outside.y == 1)
			{
				bounce_outside = Dir(1, -1); // right up
			}
			if (slice_outside.x == 1 && slice_outside.y == -1)
			{
				bounce_outside = Dir(1, 1); // right down
			}

			//border
			border = ((bounce_border.x != 0) || (bounce_border.y != 0));
			dir_collide = bounce_border;

			//inside
			inside = (inside_x && inside_y) && !border;
			if (inside)
			{
				dir_bounce = bounce_inside;
			}

			//outside
			outside = !(inside_x && inside_y) || border;
			if (outside)
			{
				dir_bounce = bounce_outside;
			}

			//we calc outside for ignore border and currect logic
			bool outside_y = !((player_up >= slice_up) && (player_down < slice_down));
			bool outside_x = !((player_left >= slice_left) && (player_right < slice_right));
			outside = outside_x || outside_y;

			//any
			any = ((dir_bounce.x != 0) || (dir_bounce.y != 0)) || inside;
		}

		void create(const IShape& shape, Size size_player, Coord pos_player)
		{
			create(shape.get_size(), shape.get_pos(), size_player, pos_player);
		}

		void create(Coord pos_collision, Size size_collision, Coord pos_player, Size size_player)
		{
			create(size_collision, pos_collision, size_player, pos_player);
		}

		Dir get_bounce() const
		{
			return dir_bounce;
		}

		Dir get_border() const
		{
			return dir_collide;
		}

		bool is_any() const
		{
			return any;
		}

		bool is_border() const
		{
			return border;
		}

		bool is_inside() const
		{
			return inside;
		}

		bool is_outside() const
		{
			return outside;
		}
	private:
		bool outside = false; //if obj outside
		bool border = false;  //if obj collide border
		bool inside = false;  //if obj inside
		bool any = false;     //if obj collide border or inside
		Dir dir_collide; //dir border collide
		Dir dir_bounce; //dir bounce
	};
public:
	Collision collide;
protected:
	Collision collide_inner;
};