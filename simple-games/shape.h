#pragma once
#include <iostream>
#include "console.h"
#include "core.h"

//interface for shape
class IShape {
public:
    virtual void set_pos(Coord pos) = 0;
    virtual void set_size(Size size) = 0;
    virtual Coord get_pos() const = 0;
    virtual Size get_size() const = 0;
};

//static print plane
class Plane : public IShape {
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

    void set_bg_padding(Size new_padding) {
        bg_padding = new_padding;
    }

    void set_color_plane(Color new_color) {
        color_plane = new_color;
    }

    void set_color_bg(Color new_color) {
        color_bg = new_color;
    }

    void set_color_border(Color new_color) {
        color_border = new_color;
    }

    void set_symbol_plane(char new_ch) {
        char_plane = new_ch;
    }

    void set_symbol_border(char new_ch) {
        char_border = new_ch;
    }

    void set_symbol_bg(char new_ch) {
        char_bg = new_ch;
    }

    //print
    void print_plane() const {
        Coord padding = Coord(border_padding.width, border_padding.height);
        std::string row_plane(size.width - padding.x * 2, char_plane);
        cmd.color(color_plane);
        for (int y = 0; y < size.height - padding.y * 2; y++) {
            cmd.gotoxy(pos.x + padding.x, pos.y + padding.y + y);
            std::cout << row_plane << std::flush;
        }
        cmd.color(color_bg);
    }

    void print_bg(bool visulize_debug_info = false) const {
        cmd.color(color_bg);
        Size screen = cmd.get_size_screen();
        std::string full;
        std::string left;
        std::string right;
        int full_size = screen.width - bg_padding.width;
        int left_size = pos.x;
        int right_size = (screen.width - (size.width + pos.x) - bg_padding.width);
        bool print_full = full_size > 0;
        bool print_left = left_size > 0;
        bool print_right = right_size > 0;

        if (print_full) {
            full.assign(full_size, ' ');
        }
        
        if (print_left) {
            left.assign(left_size, ' ');
        }
        
        if (print_right) {
            right.assign(right_size, ' ');
        }

        //left
        if (print_left) {
            for (int y = 0; y < size.height; y++) {
                cmd.gotoxy(0, y + pos.y);
                std::cout << left << std::flush;
            }
        }

        //right
        if (print_right) {
            for (int y = 0; y <= size.height; y++) {
                cmd.gotoxy(pos.x + size.width, y + pos.y);
                std::cout << right << std::flush;
            }
        }

        //top
        if (print_full) {
            for (int y = 0; y < pos.y; y++) {
                cmd.gotoxy(0, y);
                std::cout << full << std::flush;
            }
        }

        //down
        if (print_full) {
            for (int y = 0; y < screen.height - (pos.y + size.height) - bg_padding.height; y++) {
                cmd.gotoxy(0, y + pos.y + size.height);
                std::cout << full << std::flush;
            }
        }

        //fix side right
        if (visulize_debug_info == true) {
            cmd.color(Color(15, 0));
        }

        for (int y = 0; y < pos.y; y++) {
            cmd.gotoxy(0, y);
            std::cout << char_bg << std::flush;
        }

        for (int y = 0; y < screen.height - (pos.y + size.height) - bg_padding.height; y++) {
            cmd.gotoxy(0, y + pos.y + size.height);
            std::cout << char_bg << std::flush;
        }

        for (int y = 0; y < size.height; y++) {
            cmd.gotoxy(pos.x + size.width, y + pos.y);
            std::cout << char_bg << std::flush;
        }

        if (visulize_debug_info == true) {
            cmd.color(color_bg);
        }
    }

    void print_border() const {
        Coord padding = Coord(border_padding.width, border_padding.height);
        std::string line(size.width, char_border);
        std::string collum(padding.x, char_border);
        cmd.color(color_border);

        for (int y = 0; y < size.height; y++) {
            cmd.gotoxy(pos.x, y + pos.y);
            std::cout << collum << std::flush;
            cmd.gotoxy(size.width + pos.x - padding.x, y + pos.y);
            std::cout << collum << std::flush;
        }

        for (int y = 0; y < padding.y; y++) {
            cmd.gotoxy(pos.x, pos.y + y);
            std::cout << line << std::flush;
            cmd.gotoxy(pos.x, pos.y + size.height - 1 - y);
            std::cout << line << std::flush;
        }
        cmd.color(color_bg);
    }

    void print(bool background = true) const {
        if (background) { print_bg(); }
        print_border();
        print_plane();
    }

    //get
    Coord get_pos() const {
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
    Coord pos = Coord(0, 0);
    Size size = Size(60, 18);
    Size border_padding = Size(1, 1);
    Size bg_padding = Size(1, 0);

    Color color_plane;
    Color color_bg;
    Color color_border;
    char char_plane = ' ';
    char char_bg = '.';
    char char_border = ' ';
    Console cmd;
};

//static print block
class Block : public IShape {
public:
    //set
    void set_pos(Coord new_pos) {
        pos = new_pos;
    }

    void add_pos(Coord add_pos) {
        pos += add_pos;
    }

    void set_size(Size new_size) {
        size = new_size;
    }

    void set_border_padding(Size new_padding) {
        border_padding = new_padding;
    }

    void set_color_block(Color new_color) {
        color_block = new_color;
    }

    void set_color_bg(Color new_color) {
        color_bg = new_color;
    }

    void set_color_border(Color new_color) {
        color_border = new_color;
    }

    void set_symbol_block(char new_ch) {
        char_block = new_ch;
    }

    void set_symbol_border(char new_ch) {
        char_border = new_ch;
    }

    //print
    void print() const {
        Coord padding = Coord(border_padding.width, border_padding.height);
        //block
        std::string row_block(size.width - padding.x * 2, char_block);
        cmd.color(color_block);
        for (int y = 0; y < size.height - padding.y * 2; y++) {
            cmd.gotoxy(pos.x + padding.x, pos.y + padding.y + y);
            std::cout << row_block << std::flush;
        }

        //border
        std::string line(size.width, char_border);
        std::string collum(padding.x, char_border);
        cmd.color(color_border);
        for (int y = 0; y < size.height; y++) {
            cmd.gotoxy(pos.x, y + pos.y);
            std::cout << collum << std::flush;
            cmd.gotoxy(size.width + pos.x - padding.x, y + pos.y);
            std::cout << collum << std::flush;
        }
        for (int y = 0; y < padding.y; y++) {
            cmd.gotoxy(pos.x, pos.y + y);
            std::cout << line << std::flush;
            cmd.gotoxy(pos.x, pos.y + size.height - 1 - y);
            std::cout << line << std::flush;
        }
        cmd.color(color_bg);
    }

    //get
    Coord get_pos() const {
        return pos;
    }

    Size get_size() const {
        return size;
    }

    Color get_color_block() const {
        return color_block;
    }

    Color get_color_bg() const {
        return color_bg;
    }

    Color get_color_border() const {
        return color_border;
    }

protected:
    Coord pos = Coord(0, 0);
    Size size = Size(2, 2);
    Size border_padding = Size(0, 0);

    Color color_block;
    Color color_bg;
    Color color_border;
    char char_block = ' ';
    char char_border = ' ';
    Console cmd;
};
