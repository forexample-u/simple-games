#pragma once
#include <iostream>
#include <deque>
#include "collider.h"
#include "console.h"
#include "move.h"
#include "shape.h"
#include "core.h"

//apple
class Apple;

//snake
class Snake : protected Collider {
private:
    bool detect_damage(const IShape& plane) {
        if (dir.is_zero()) {
            return false;
        }

        //snake self
        for (size_t i = 0; i < pos_all.size() - 1; i++) {
            if (pos_all[i] == pos_head) {
                return true;
            }
        }

        //wall collide
        Snake::collide.create(plane, Size(1, 1), pos_head);
        if (Snake::collide.is_border()) {
            return true;
        }

        return false;
    }

    void die_condition(const IShape& shape) {
        if (detect_damage(shape)) { //if detect damage snake go back 
            pos_head.x -= dir.x;
            pos_head.y += dir.y;
            pos_all.push_front(pos_tail);
            pos_all.pop_back();
            count_bounce += 1;
        }
        else {
            count_bounce = 0;
        }
        die = count_bounce > bounce;
    }

    void win_condition(const IShape& shape) {
        int win_size = (shape.get_size().width - 2) * (shape.get_size().height - 2);
        win = size_snake >= win_size;
    }
public:
    void move(Move& move) {
        move.move();
        Dir move_dir = Dir(move.now.get_dir_x(), move.now.get_dir_y());
        if (!move_dir.is_zero()) {
            if (move_dir.x != 0 && dir.x == 0) {
                dir = move_dir;
            }
            if (move_dir.y != 0 && dir.y == 0) {
                dir = move_dir;
            }
        }
        pos_head.x += dir.x;
        pos_head.y -= dir.y;
        pos_all.push_back(pos_head);
        pos_tail = pos_all.front();
        if (size_snake <= static_cast<int>(pos_all.size())) {
            pos_all.pop_front();
        }
    }

    void eat(Apple& apple);

    //print
    void print() const {
        //snake_tail print
        if ((size_snake >= static_cast<int>(pos_all.size())) || (size_snake == 0)) {
            cmd.color(color_bg);
            for (int y = 0; y < step_snake.y; y++) {
                cmd.gotoxy(pos_tail.x * step_snake.x, pos_tail.y * step_snake.y + y);
                std::cout << std::string(step_snake.x, ' ') << std::flush;
                cmd.gotoxy(pos_tail.x * step_snake.x, pos_tail.y * step_snake.y + y);
            }
        }

        //snake print
        cmd.color(color_snake);
        bool print_all = false;
        if (print_all) { //TODO: make print_all
            for (const auto& pos_snake : pos_all) {
                cmd.gotoxy(pos_snake.x * step_snake.x, pos_snake.y * step_snake.y);
                std::cout << std::string(step_snake.x, char_snake);
            }
            std::cout.flush();
        }
        else { //snake_head print
            for (int y = 0; y < step_snake.y; y++) {
                cmd.gotoxy(pos_head.x * step_snake.x, pos_head.y * step_snake.y + y);
                std::cout << std::string(step_snake.x, '.') << std::flush;
                cmd.gotoxy(pos_head.x * step_snake.x, pos_head.y * step_snake.y + y);
            }
        }
        cmd.color(color_bg);
    }

    //set
    void set_pos(Coord new_pos) {
        pos_head = new_pos;
        pos_all.back() = new_pos;
    }

    void set_plane(const IShape& plane) {
        die_condition(plane);
        win_condition(plane);
    }

    void set_color_snake(Color new_color) {
        color_snake = new_color;
    }

    void set_color_bg(Color new_color) {
        color_bg = new_color;
    }

    void set_symbol_snake(char new_ch) {
        char_snake = new_ch;
    }

    void set_step(Coord new_step) {
        step_snake = new_step;
    }

    //get
    bool is_die() const {
        return die;
    }

    bool is_win() const {
        return win;
    }

    Coord get_step() {
        return step_snake;
    }

    std::deque<Coord> get_all_pos() const {
        return pos_all;
    }
private:
    //inside parameter
    Coord step_snake = Coord(2, 1);
    Coord pos_head;
    Coord pos_tail;
    Dir dir;
    Color color_snake;
    Color color_bg;

    //inside parameter
    std::deque<Coord> pos_all{ Coord(0, 0) };
    int count_bounce = 0;
    char char_snake = ' ';
    bool die = false;
    bool win = false;

    //shop parameter
    int size_snake = 1;
    int add_size = 1;
    int speed = 0;
    int bounce = 4;
    int skin = 0;

    //console
    Console cmd;
};

//apple
class Apple {
public:
    ~Apple() {
        destroy();
    }

    void create(Coord new_pos) {
        pos_apple = new_pos;
        exist_apple = true;
    }

    void rand_create(IShape& shape, const Snake& snake) {
        pos_apple = snake.get_all_pos()[0];
        bool create_apple = false;
        while (!create_apple) {
            create_apple = true;
            for (const auto& pos_snake : snake.get_all_pos()) {
                if (pos_apple == pos_snake) {
                    pos_apple.x = (rand() % (shape.get_size().width - 2)) + shape.get_pos().x + 1;
                    pos_apple.y = (rand() % (shape.get_size().height - 2)) + shape.get_pos().y + 1;
                    create_apple = false;
                    break;
                }
            }
        }
        create(pos_apple);
    }

    //set
    void set_color_apple(Color new_color) {
        color_apple = new_color;
    }

    void set_color_bg(Color new_color) {
        color_bg = new_color;
    }

    void set_symbol_apple(char new_ch = '$') {
        char_apple = new_ch;
    }

    void set_step(Coord new_step) {
        step_apple = new_step;
    }

    //print
    void print() const {
        cmd.color(color_apple);
        for (int y = 0; y < step_apple.y; y++) {
            cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
            std::cout << std::string(step_apple.x, char_apple) << std::flush;
            cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
        }
    }

    void destroy() {
        if (is_create()) {
            cmd.color(color_bg);
            for (int y = 0; y < step_apple.y; y++) {
                cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
                std::cout << std::string(step_apple.x, ' ') << std::flush;
                cmd.gotoxy(pos_apple.x * step_apple.x, pos_apple.y * step_apple.y + y);
            }
            exist_apple = false;
        }
    }

    //get
    Coord get_pos() const {
        return pos_apple;
    }

    bool is_create() const {
        return exist_apple;
    }

private:
    Coord pos_apple;
    Coord step_apple = Coord(2, 1);
    Color color_apple = Color(7, 4);
    Color color_bg;
    bool exist_apple = false;
    char char_apple = '$';
    Console cmd;
};

//metod snake
void Snake::eat(Apple& apple) {
    Coord pos_apple = apple.get_pos();
    if (pos_head == pos_apple) {
        apple.destroy();
        size_snake += add_size;
    }
}

namespace ListGame {
    void snake() {
        Move move;
        Console cmd;
        Plane plane;
        Snake snake;
        Apple apple;
        cmd.resize_screen(Size(120, 30));

        //settings:
        Coord step_snake = Coord(2, 1);
        Size size_plane = Size(90, 22);
        Coord pos_plane = Coord(7, 4);
        int add_sleep = 20;
        int color_bg = 3;
        int color_border = 4;
        int color_plane = 0;
        int color_snake = 15;

        //plane
        plane.set_pos(Coord(pos_plane.x / step_snake.x, pos_plane.y / step_snake.y));
        plane.set_size(Size(size_plane.width / step_snake.x, size_plane.height / step_snake.y));
        plane.set_color_bg(Color(color_bg, color_bg));
        plane.set_color_border(Color(color_border, color_border));
        plane.set_color_plane(Color(color_plane, color_plane));
        plane.set_symbol_border('.');
        plane.set_symbol_plane(' ');

        //snake
        snake.set_pos(Coord(plane.get_pos().x + 1, plane.get_pos().y + 1));
        snake.set_step(step_snake);
        snake.set_color_snake(Color(color_snake, color_snake));
        snake.set_symbol_snake('.');

        //apple
        apple.set_step(step_snake);
        apple.set_symbol_apple(' ');
        apple.set_color_apple(Color(4, 4));
        apple.set_color_bg(Color(color_plane, color_plane));

        //print scale plane
        cmd.sleep(50);
        Plane plane_scale = plane;
        plane_scale.set_pos(Coord(plane.get_pos().x * step_snake.x, plane.get_pos().y * step_snake.y));
        plane_scale.set_size(Size(plane.get_size().width * step_snake.x, plane.get_size().height * step_snake.y));
        plane_scale.set_border_padding(Size(step_snake.x, step_snake.y));
        plane_scale.print();

        while (true) {
            snake.move(move);
            snake.set_plane(plane);
            snake.eat(apple);
            snake.print();
            if (!apple.is_create()) {
                int random_color = rand() % 3;
                if (random_color == 0) { apple.set_color_apple(Color(6, 6)); }
                if (random_color == 1) { apple.set_color_apple(Color(4, 4)); }
                if (random_color == 2) { apple.set_color_apple(Color(2, 2)); }
                apple.rand_create(plane, snake);
                apple.print();
            }
            if (move.now.get_dir_x() != 0) {
                add_sleep = 50;
            }
            if (move.now.get_dir_y() != 0) {
                add_sleep = 50;
            }
            cmd.sleep(add_sleep + 10);

            //end game
            if (snake.is_die()) {
                break;
            }
            if (snake.is_win()) {
                break;
            }
            if (move.now.get_escape()) {
                break;
            }
        }
        cmd.color_reset();
        cmd.clear();
    }
}
