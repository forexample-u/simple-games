#pragma once
#include <iostream>
#include <deque>

#include "console.h"
#include "move.h"
#include "shape.h"

//apple
class Apple;

//snake
class Snake {
private:
    bool detect_damage(Plane& plane) {
        //wall
        if (pos_x < plane.get_offset_x() + 1) { return true; }
        if (pos_y < plane.get_offset_y() + 1) { return true; }
        if (pos_x > (plane.get_offset_x() - 1 + plane.get_size_x() - 1)) { return true; }
        if (pos_y > (plane.get_offset_y() - 1 + plane.get_size_y() - 1)) { return true; }

        //snake self
        if (!(dir_x == 0 && dir_y == 0)) {
            for (int i = 0; i < get_size_array() - 1; i++) {
                if (pos_x_vec[i] == pos_x && pos_y_vec[i] == pos_y) {
                    return true;
                }
            }
        }
        return false;
    }

    void die_condition(Plane& plane) {
        if (detect_damage(plane)) {
            die_pos_x = pos_x_vec.back();
            die_pos_y = pos_y_vec.back();
            pos_x -= dir_x;
            pos_y -= dir_y;
            pos_x_vec.pop_back();
            pos_y_vec.pop_back();
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
        int win_size = plane.get_size_x() * plane.get_offset_y();
        win = size_snake > win_size;
    }
public:
    Snake() {
        pos_x_vec.push_back(pos_x);
        pos_y_vec.push_back(pos_y);
    }

    void move(Move& move) {
        move.move();
        int move_dir_x = move.now.get_dir_x();
        int move_dir_y = move.now.get_dir_y();
        if (move_dir_x != 0 || move_dir_y != 0) {
            dir_x = move_dir_x;
            dir_y = move_dir_y;
        }
        pos_x += dir_x;
        pos_y -= dir_y;
        pos_x_vec.push_back(pos_x);
        pos_y_vec.push_back(pos_y);
    }

    void eat(Apple& apple);

    //print
    void print(Plane& plane) {
        die_condition(plane);
        win_condition(plane);

        //backround
        Color plane_color = plane.get_color_plane();
        cmd.color(plane_color.get_font(), plane_color.get_bg());
        if (size_snake < static_cast<int>(pos_x_vec.size())) {
            cmd.gotoxy(pos_x_vec[0], pos_y_vec[0]);
            std::cout << ' ';
            pos_x_vec.pop_front();
            pos_y_vec.pop_front();
        }

        //symbol color
        cmd.color(color_snake.get_font(), color_snake.get_bg());
        for (size_t i = 0; i < pos_x_vec.size(); i++) {
            cmd.gotoxy(pos_x_vec[i], pos_y_vec[i]);
            std::cout << char_snake;
        }
        Color bg_color = plane.get_color_bg();
        cmd.color(bg_color.get_font(), bg_color.get_bg());
    }

    void print_die_step(Color die_color = { 7, 4 }) {
        if (die == true) {
            cmd.gotoxy(die_pos_x, die_pos_y);
            cmd.color(die_color.get_font(), die_color.get_bg());
            std::cout << char_snake;
        }
    }

    //set
    void set_start_pos(const Plane& plane) {
        pos_x_vec.pop_back();
        pos_y_vec.pop_back();
        pos_x = plane.get_offset_x() + 1;
        pos_y = plane.get_offset_y() + 1;
        pos_x_vec.push_back(pos_x);
        pos_y_vec.push_back(pos_y);
    }

    void set_pos_x(int new_x) {
        pos_x = new_x;
    }

    void set_pos_y(int new_y) {
        pos_y = new_y;
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

    std::deque<int> get_all_pos_x() const {
        return pos_x_vec;
    }

    std::deque<int> get_all_pos_y() const {
        return pos_y_vec;
    }

    int get_length_snake() const {
        return size_snake;
    }

    int get_size_array() const {
        return pos_x_vec.size();
    }

private:
    //inside parameter coord
    int dir_x = 0;
    int dir_y = 0;
    int pos_x = 0;
    int pos_y = 0;
    int last_pos_x = 0;
    int last_pos_y = 0;
    int die_pos_x = 0;
    int die_pos_y = 0;

    //inside parameter
    int count_bounce = 0;
    std::deque<int> pos_x_vec;
    std::deque<int> pos_y_vec;
    Color color_snake;
    char char_snake;
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

    Apple(int pos_x, int pos_y, char symbol_apple = '$', int color_apple = 7, int color_backround = 4) {
        create(pos_x, pos_y, symbol_apple, color_apple, color_backround);
    }

    ~Apple() {
        destroy();
    }

    bool is_create() {
        return exist_apple;
    }

    void create(int pos_x, int pos_y, char symbol_apple = '$', int color_apple = 7, int color_backround = 4) {
        this->pos_x = pos_x;
        this->pos_y = pos_y;
        this->symbol_apple = symbol_apple;
        this->color_apple = Color(color_apple, color_backround);
        this->exist_apple = true;
        print();
    }

    void rand_create(Plane& plane, Snake& snake, char symbol_apple = '$', int color_apple = 7, int color_backround = 4) {
        pos_x = (rand() % (plane.get_size_x() - 2)) + plane.get_offset_x() + 1;
        pos_y = (rand() % (plane.get_size_y() - 2)) + plane.get_offset_y() + 1;
        for (int i = 0; i < snake.get_size_array(); i++) {
            if (pos_x == snake.get_all_pos_x()[i]) {
                if (pos_y == snake.get_all_pos_y()[i]) {
                    pos_x = (rand() % (plane.get_size_x() - 2)) + plane.get_offset_x() + 1;
                    pos_y = (rand() % (plane.get_size_y() - 2)) + plane.get_offset_y() + 1;
                    i = 0;
                    continue;
                }
            }
        }
        create(pos_x, pos_y, symbol_apple, color_apple, color_backround);
    }

    void print() {
        cmd.color(color_apple.get_font(), color_apple.get_bg());
        cmd.gotoxy(pos_x, pos_y);
        std::cout << symbol_apple;
        cmd.color_reset();
    }

    void destroy() {
        if (!is_create()) {
            return;
        }
        cmd.gotoxy(pos_x, pos_y);
        std::cout << ' ';
        exist_apple = false;
        cmd.color_reset();
    }

    int get_pos_x() const {
        return pos_x;
    }

    int get_pos_y() const {
        return pos_y;
    }

private:
    bool exist_apple = false;
    char symbol_apple;
    Color color_apple;

    int pos_x;
    int pos_y;
    Console cmd;
};

//metod snake
void Snake::eat(Apple& apple) {
    int pos_x_apple = apple.get_pos_x();
    int pos_y_apple = apple.get_pos_y();
    if ((pos_x == pos_x_apple) && (pos_y == pos_y_apple)) {
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

    plane.set_pos(7, 4);
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
    snake.set_start_pos(plane);
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
    cmd.color(15, 15);
    cmd.pause();
}
