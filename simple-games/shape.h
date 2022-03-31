#pragma once
#include <iostream>
#include "core.h"

//static print block
class Plane {
public:
    //set
    void set_pos(Coord new_pos) {
        pos = new_pos;
    }

    void add_pos(Coord add) {
        pos += add;
    }

    void set_size(Size new_size) {
        size = new_size;
    }

    void set_border_padding(Size new_padding) {
        border_padding = new_padding;
    }

    void set_color_plane(Color color) {
        color_plane = color;
    }

    void set_color_bg(Color color) {
        color_bg = color;
    }

    void set_color_border(Color color) {
        color_border = color;
    }

    void set_symbol_plane(char ch) {
        char_plane = ch;
    }

    void set_symbol_border(char ch) {
        char_border = ch;
    }

    void set_symbol_bg(char ch) {
        char_bg = ch;
    }

    //print
    void print_plane() const {
        Coord padding = { border_padding.width, border_padding.height };
        std::string row_plane(size.width - padding.x * 2, char_plane);
        cmd.color(color_plane);
        for (int y = 0; y < size.height - padding.y * 2; y++) {
            cmd.gotoxy(pos.x + padding.x, pos.y + padding.y + y);
            std::cout << row_plane;
        }
        cmd.color(color_bg);
    }

    void print_bg(bool visulize_debug_info = false) const {
        cmd.color(color_bg);
        Size console = cmd.get_size_screen();
        std::string full(console.width - 1, ' ');
        std::string right;
        std::string left;

        int left_size = pos.x;
        if (left_size > 0) {
            left.assign(left_size, ' ');
        }

        int right_size = (console.width - (size.width + pos.x) - 1);
        if (right_size > 0) {
            right.assign(right_size, ' ');
        }

        //left
        for (int y = 0; y < size.height; y++) {
            cmd.gotoxy(0, y + pos.y);
            std::cout << left;
        }

        //top
        for (int y = 0; y < pos.y; y++) {
            cmd.gotoxy(0, y);
            std::cout << full;
        }

        //right
        for (int y = 0; y <= size.height; y++) {
            cmd.gotoxy(pos.x + size.width, y + pos.y);
            std::cout << right;
        }

        //down
        for (int y = 0; y < console.height - (pos.y + size.height); y++) {
            cmd.gotoxy(0, y + pos.y + size.height);
            std::cout << full;
        }

        //fix side right
        cmd.color(color_bg);
        if (visulize_debug_info == true) {
            cmd.color(Color(15, 0));
        }

        for (int y = 0; y < pos.y; y++) {
            cmd.gotoxy(0, y);
            std::cout << char_bg;
        }

        for (int y = 0; y < console.height - (pos.y + size.height); y++) {
            cmd.gotoxy(0, y + pos.y + size.height);
            std::cout << char_bg;
        }

        for (int y = 0; y < size.height; y++) {
            cmd.gotoxy(pos.x + size.width, y + pos.y);
            std::cout << char_bg;
        }
    }

    void print_border() {
        Coord padding = { border_padding.width, border_padding.height };
        std::string line(size.width, char_border);
        std::string collum(padding.x, char_border);
        cmd.color(color_border);

        for (int y = 0; y < size.height; y++) {
            cmd.gotoxy(pos.x, y + pos.y);
            std::cout << collum;
            cmd.gotoxy(size.width + pos.x - padding.x, y + pos.y);
            std::cout << collum;
        }

        for (int i = 0; i < padding.y; i++) {
            cmd.gotoxy(pos.x, pos.y + i);
            std::cout << line;
            cmd.gotoxy(pos.x, pos.y + size.height - 1 - i);
            std::cout << line;
        }
        cmd.color(color_bg);
    }

    //get
    Coord get_offset() const {
        return pos;
    }

    Size get_size() const {
        return size;
    }

    Color get_color_plane() const {
        return color_plane;
    }

    Color get_color_bg() const {
        return color_bg;
    }

    Color get_color_border() const {
        return color_border;
    }

protected:
    Coord pos = { 0, 0 };
    Size size = { 60, 18 };
    Size border_padding = { 1, 1 };

    Color color_plane;
    Color color_bg;
    Color color_border;
    char char_plane = ' ';
    char char_bg = '.';
    char char_border = ' ';
    Console cmd;
};

