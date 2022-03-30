#pragma once
#include <iostream>
#include <deque>
#include "console.h"
#include "move.h"
#include "shape.h"
#include "core.h"

//apple
class Apple;

//snake
class Snake {
private:
    bool detect_damage(Plane& plane) {
        //wall
        if (pos.x < plane.get_offset().x + 1) { return true; }
        if (pos.y < plane.get_offset().y + 1) { return true; }
        if (pos.x > (plane.get_offset().x - 1 + plane.get_size().width - 1)) { return true; }
        if (pos.y > (plane.get_offset().y - 1 + plane.get_size().height - 1)) { return true; }

        //snake self
        if (!(dir_x == 0 && dir_y == 0)) {
            for (int i = 0; i < get_size_array() - 1; i++) {
                if (pos_vec[i] == pos) {
                    return true;
                }
            }
        }
        return false;
    }

    void die_condition(Plane& plane) {
        if (detect_damage(plane)) {
            die_pos = pos_vec.back();
            pos.x -= dir_x;
            pos.y -= dir_y;
            pos_vec.pop_back();
            count_bounce += 1;
        }
        else {
            count_bounce = 0;
        }

        if (count_bounce > bounce) {
            die = true;
        }
    }

    void win_condition(Plane& plane) {
        int win_size = plane.get_size().width * plane.get_offset().y;
        win = size_snake > win_size;
    }
public:
    Snake() {
        pos_vec.push_back(pos);
    }

    void move(Move& move) {
        move.move();
        int move_dir_x = move.now.get_dir_x();
        int move_dir_y = move.now.get_dir_y();
        if (move_dir_x != 0 || move_dir_y != 0) {
            dir_x = move_dir_x;
            dir_y = move_dir_y;
        }
        pos.x += dir_x;
        pos.y -= dir_y;
        pos_vec.push_back(pos);
    }

    void eat(Apple& apple);

    //print
    void print(Plane& plane) {
        die_condition(plane);
        win_condition(plane);

        //backround
        cmd.color(plane.get_color_plane());
        if (size_snake < static_cast<int>(pos_vec.size())) {
            cmd.gotoxy(pos_vec[0]);
            std::cout << ' ';
            pos_vec.pop_front();
        }

        //symbol color
        cmd.color(color_snake);
        for (size_t i = 0; i < pos_vec.size(); i++) {
            cmd.gotoxy(pos_vec[i]);
            std::cout << char_snake;
        }
        cmd.color(plane.get_color_bg());
    }

    void print_die_step(Color die_color = { 7, 4 }) {
        if (die == true) {
            cmd.gotoxy(die_pos);
            cmd.color(die_color);
            std::cout << char_snake;
        }
    }

    void set_pos(Coord new_pos) {
        pos_vec.pop_back();
        pos = new_pos;
        pos_vec.push_back(pos);
    }

    void set_color_snake(Color new_color) {
        color_snake = new_color;
    }

    void set_symbol_snake(char new_ch) {
        char_snake = new_ch;
    }

    //get
    bool is_die() const {
        return die;
    }

    bool is_win() const {
        return win;
    }

    std::deque<Coord> get_all_pos() const {
        return pos_vec;
    }

    int get_length_snake() const {
        return size_snake;
    }

    int get_size_array() const {
        return pos_vec.size();
    }

private:
    //inside parameter coord
    int dir_x = 0;
    int dir_y = 0;
    Coord pos;
    Coord last_pos;
    Coord die_pos;

    //inside parameter
    std::deque<Coord> pos_vec;
    Color color_snake;
    int count_bounce = 0;
    char char_snake = ' ';
    bool die = false;
    bool win = false;

    //shop parameter
    int add_size = 1;
    int size_snake = 2;
    int speed = 0;
    int bounce = 6;
    int skin = 0;

    //console
    Console cmd;
};

//apple
class Apple {
public:
    Apple() {}

    Apple(Plane& plane, Snake& snake, char symbol_apple = '$', int color_apple = 7, int color_backround = 4) {
        rand_create(plane, snake, symbol_apple, color_apple, color_backround);
    }

    Apple(Coord new_pos, char symbol_apple = '$', int color_apple = 7, int color_backround = 4) {
        create(new_pos, symbol_apple, color_apple, color_backround);
    }

    ~Apple() {
        destroy();
    }

    bool is_create() {
        return exist_apple;
    }

    void create(Coord new_pos, char symbol_apple = '$', int color_apple = 7, int color_backround = 4) {
        this->pos = pos;
        this->symbol_apple = symbol_apple;
        this->color_apple = Color(color_apple, color_backround);
        this->exist_apple = true;
        print();
    }

    void rand_create(Plane& plane, Snake& snake, char symbol_apple = '$', int color_apple = 7, int color_backround = 4) {
        pos.x = (rand() % (plane.get_size().width - 2)) + plane.get_offset().x + 1;
        pos.y = (rand() % (plane.get_size().height - 2)) + plane.get_offset().y + 1;
        for (int i = 0; i < snake.get_size_array(); i++) {
            if (pos.x == snake.get_all_pos()[i].x) {
                if (pos.y == snake.get_all_pos()[i].y) {
                    pos.x = (rand() % (plane.get_size().width - 2)) + plane.get_offset().x + 1;
                    pos.y = (rand() % (plane.get_size().height - 2)) + plane.get_offset().y + 1;
                    i = 0;
                    continue;
                }
            }
        }
        create(pos, symbol_apple, color_apple, color_backround);
    }

    void print() {
        cmd.color(color_apple);
        cmd.gotoxy(pos);
        std::cout << symbol_apple;
        cmd.color_reset();
    }

    void destroy() {
        if (!is_create()) {
            return;
        }
        cmd.gotoxy(pos);
        std::cout << ' ';
        exist_apple = false;
        cmd.color_reset();
    }

    Coord get_pos() const {
        return pos;
    }

private:
    bool exist_apple = false;
    char symbol_apple;
    Color color_apple;

    Coord pos;
    Console cmd;
};

//metod snake
void Snake::eat(Apple& apple) {
    Coord pos_apple = apple.get_pos();
    if (pos == pos_apple) {
        apple.destroy();
        size_snake += add_size;
    }
}

void start_snake() {
    Console cmd;
    Plane plane;

    int bg_color = 3;
    int border_color = 4;
    int plane_color = 0;

    plane.set_pos(Coord(7, 4));
    plane.set_color_bg(Color(bg_color, bg_color));
    plane.set_color_plane(Color(plane_color, plane_color));
    plane.set_color_border(Color(border_color, border_color));
    plane.set_symbol_border('.');
    plane.set_symbol_plane(' ');
    plane.print_plane();
    plane.print_border();
    plane.print_bg();

    //snake
    Move move;
    Snake snake;
    Apple apple;
    Coord start_pos = plane.get_offset(); //TODO: Coord + 1
    snake.set_pos(Coord(start_pos.x + 1, start_pos.y + 1));
    snake.set_color_snake(Color(15, 15));
    snake.set_symbol_snake('.');

    int add_sleep = 0;
    while (1) {
        snake.eat(apple);
        if (apple.is_create() == false) {
            apple.rand_create(plane, snake);
            apple.print();
        }
        snake.move(move);
        snake.print(plane);
        if (move.now.get_dir_y() != 0) {
            add_sleep += 8;
        }
        cmd.sleep(10 + add_sleep);

        //end game
        if (snake.is_die() == true) {
            snake.print_die_step();
            break;
        }
        if (snake.is_win() == true) {
            break;
        }
        if (move.now.get_escape()) {
            break;
        }
    }
    cmd.color(Color(15, 15));
    cmd.pause();
}
