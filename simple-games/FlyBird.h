#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <string>

#include "console.h"
#include "move.h"
#include "core.h"
#include "shape.h"




//collum
class Collum {
public:
	void print() const {
		cmd.color(color_collum);
		int size_vec = static_cast<int>(shape.size());
		for (int i = 0; i < size_vec; i++) {
			cmd.gotoxy(pos_collum.x, pos_collum.y + i);
			std::cout << shape[i];
			std::cout.flush();
		}
		cmd.color(color_bg);
		cmd.gotoxy(pos_collum.x - 1, pos_collum.y);
	}

	void create(Size new_size, Coord new_pos) {
		std::string shape_row(new_size.width, ' ');
		for (int i = 0; i < new_size.height; i++) {
			shape.emplace_back(shape_row);
		}
		size_collum.height = new_size.height;
		find_width();
		
		pos_collum.x = border_plane.width - new_size.width + new_pos.x;
		pos_collum.y = border_plane.height - new_size.height + new_pos.y;
	}

	//set
	void set_pos(Coord new_pos) {
		pos_collum = new_pos;
	}

	void add_pos(Coord add_pos) {
		pos_collum += add_pos;
	}

	void set_color_collum(Color new_color) {
		color_collum = new_color;
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_border(Plane& plane) {
		border_plane = plane.get_size();
	}

	//get
	Coord get_pos() const {
		return pos_collum;
	}

	Size get_size() const {
		return size_collum;
	}

private:
	void find_width() {
		for (const auto& x : shape) {
			int size_arr = static_cast<int>(x.size());
			if (size_arr > size_collum.width) {
				size_collum.width = size_arr;
			}
		}
	}
	std::vector<std::string> shape;
	Coord pos_collum;
	Size border_plane;
	Size size_collum;
	Color color_collum;
	Color color_bg;
	Console cmd;
};

class Level {
public:
	void create_collum(Plane& plane, int min_width = 2, int max_width = 4, int min_height = 2, int max_height = 15) {
		Collum collum;
		collum.set_border(plane);
		int width = min_width + (rand() % (max_width - min_width));
		int height = min_height + (rand() % (max_height - min_height));

		pause_seconds -= 1;
		int rand_index = rand() % 11;
		if (pause_seconds < 0) {
			collum.create(Size(width, height * 0.7), plane.get_pos());
			if (rand_index < 5) {
				collum.set_pos(Coord(collum.get_pos().x, plane.get_pos().y));
			}

			collums.push_back(collum);
			if (rand_index > 6) {
				int height_rand = (plane.get_size().height - height) / 4;
				collum.create(Size(width, height_rand), plane.get_pos());
				collum.set_pos(Coord(collum.get_pos().x, plane.get_pos().y));
				collums.push_back(collum);
				pause_seconds += width;
			}

			pause_seconds += width * 2;
		}
	}

	void print(const Plane& plane) {
		for (Collum& collum : collums) {
			//print backround
			collum.set_color_bg(plane.get_color_plane());
			collum.set_color_collum(plane.get_color_plane());
			collum.print();

			//remove left
			int delete_size = (collum.get_size().width - 2) + plane.get_pos().x + 1;
			if (delete_size > (collum.get_pos().x)) {
				collums.pop_front();
				continue;
			}

			//print collum
			collum.add_pos(Coord(-1, 0));
			collum.set_color_collum(color_collum);
			collum.print();
		}
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_color(Color new_color) {
		color_collum = new_color;
	}

	//get
	Collum get_front() const {
		return collums.front();
	}

	std::deque<Collum> get_collums() const {
		return collums;
	}

private:
	std::deque<Collum> collums;
	Color color_collum;
	Color color_bg;
	int pause_seconds = 0;
};

class Bird : public Collider {
private:
	bool detect_damage(const Plane& plane) {
		//wall
		collide.create(plane, Size(1, 1), pos_bird);
		if (collide.is_outside()) {
			return true;
		}

		//collums
		for (Collum& collum : collums) {
			collide.create(collum.get_size(), collum.get_pos(), Size(1, 1), pos_bird);
			if (collide.is_inside() || collide.is_border()) {
				return true;
			}
		}
		return false;
	}

	void die_condition(const Plane& plane) {
		if (detect_damage(plane) == true) {
			count_bounce += 1;
		}

		if (count_bounce > bounce) {
			die = true;
		}
	}
public:
	void move(Move& move) {
		last_pos_bird = pos_bird;
		move.move();
		int space = move.now.get_space();
		int dir = move.now.get_dir_y();
		if (space || (dir == 1)) {
			jump();
			cmd.sleep(10);
		}
		if (count_step_fly > step_fly) {
			pos_bird.y += 1;
		}
		count_step_fly += 1;
	}

	void jump() {
		last_pos_bird = pos_bird;
		pos_bird.y -= 7;
		count_step_fly = 0;
	}

	//set
	void set_pos(Coord new_pos) {
		pos_bird = new_pos;
	}

	void set_start_pos(const Plane& plane) {
		pos_bird.x = plane.get_pos().x + (plane.get_size().width * 0.5);
		pos_bird.y = plane.get_pos().y + (plane.get_size().height * 0.5);
	}

	void set_plane(const Plane& plane) {
		die_condition(plane);
	}

	void set_color_bird(Color new_color) {
		color_bird = new_color;
	}

	void set_color_bg(Color new_color) {
		color_bg = new_color;
	}

	void set_symbol_bird(char new_ch) {
		char_bird = new_ch;
	}

	//print
	void print() const {
		//backround
		cmd.color(color_bg);
		cmd.gotoxy(last_pos_bird);
		std::cout << ' ' << std::flush;

		//symbol color
		cmd.color(color_bird);
		cmd.gotoxy(pos_bird);
		std::cout << char_bird << std::flush;

		cmd.color(color_bg);
	}

	//get
	bool is_die() const {
		return die;
	}

	void get_collums(Level level) {
		collums = level.get_collums();
	}

private:
	Coord pos_bird;
	Coord last_pos_bird;
	Color color_bird;
	Color color_bg;
	char char_bird = 'o';

	std::deque<Collum> collums;

	
	int count_step_fly = 0;
	int step_fly = 1;
	int count_bounce = 0;
	int bounce = 0;
	bool die = false;
	Console cmd;
};

void flyBird() {
	Console cmd;
	Move move;
	Bird bird;
	Plane plane;

	Color color_plane = Color(11, 11);
	Color color_bg = Color(0, 0);
	Color color_collum = Color(0, 0);
	Color color_bird = Color(15, 15);

	//plane
	plane.set_size(Size(100, 25));
	plane.set_pos(Coord(0, 0));
	plane.set_color_bg(color_bg);
	plane.set_color_plane(color_plane);
	plane.set_color_border(color_plane);

	//bird
	bird.set_color_bg(plane.get_color_plane());
	bird.set_color_bird(color_bird);

	Level level;
	level.set_color(color_collum);
	while (true) {
		move.move();
		Size screen_size = cmd.get_size_screen();
		if (screen_size.width < 50) {
			screen_size.width = 50;
			cmd.resize_screen(screen_size);
		}

		if (screen_size.height < 20) {
			screen_size.height = 20;
			cmd.resize_screen(screen_size);
		}

		int padding_height = (screen_size.height / 7) * 2;
		plane.set_size(Size(screen_size.width - 4, screen_size.height - padding_height));
		plane.set_pos(Coord(2, padding_height * 0.5));
		plane.print();

		bird.set_start_pos(plane);
		bird.set_color_bird(Color(15, 15));
		bird.set_plane(plane);
		
		bird.print();
		cmd.sleep(100);
		if (move.now.get_space() || (move.now.get_dir_y() == 1)) {
			bird.set_plane(plane);
			bird.print();
			bird.jump();
			break;
		}
	}

	cmd.clear();
	Size screen_size = cmd.get_size_screen();
	int padding_height = ((screen_size.height / 7) * 2);
	plane.set_size(Size(screen_size.width - 2, screen_size.height - padding_height));
	plane.set_pos(Coord(0, padding_height * 0.5));
	plane.print();
	Size size_plane = plane.get_size();
	int max_width  = size_plane.width / 15;
	int max_height = size_plane.height / 2 - 2;
	int min_width  = size_plane.width / 30 + 1;
	int min_height = size_plane.height / 10;
	while(true) {
		level.create_collum(plane, min_width, max_width, min_height, max_height);
		level.print(plane);
		cmd.sleep(((size_plane.width * 0.5) / (size_plane.width / 40 + size_plane.height / 30)) + 15);
		if (bird.is_die()) {
			bird.set_color_bird(Color(12, 12));
			bird.print();
			break;
		}
		bird.get_collums(level);
		bird.move(move);
		bird.set_plane(plane);
		bird.print();
	}
	cmd.pause();
	cmd.sleep(500);
	cmd.color_reset();
	cmd.clear();
}
