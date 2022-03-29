#pragma once

//color
struct Color {
    Color() {}
    Color(int font, int bg) {
        this->font = font;
        this->bg = bg;
    }
    int get_font() const {
        return font;
    }
    int get_bg() const {
        return bg;
    }
private:
    int font = 7;
    int bg = 0;
};

//static print plane
class Plane {
public:
    Plane() {
        width_console = cmd.get_width();
        height_console = cmd.get_height();
    }

    void set_pos(int new_x, int new_y) {
        pos_x = new_x;
        pos_y = new_y;
    }

    void set_size(int new_size_x, int new_size_y) {
        size_x = new_size_x;
        size_y = new_size_y;
    }

    void print_plane() const {
        std::string row_plane(size_x - 2, char_plane);
        cmd.color(color_plane.get_font(), color_plane.get_bg());
        for (int y = 0; y < size_y - 2; y++) {
            cmd.gotoxy(pos_x + 1, y + pos_y + 1);
            std::cout << row_plane;
        }
        cmd.color(color_bg.get_font(), color_bg.get_bg());
    }

    void print_bg(bool visulize_debug_info = false) const {
        cmd.color(color_bg.get_font(), color_bg.get_bg());
        std::string full(width_console - 1, char_bg);
        std::string left(pos_x, char_bg);
        std::string right;
        if ((width_console - (size_x + pos_x) - 1) > 0) {
            right.assign(width_console - (size_x + pos_x) - 1, char_bg);
        }

        //left
        for (int y = 0; y < size_y; y++) {
            cmd.gotoxy(0, y + pos_y);
            std::cout << left;
        }

        //top
        for (int y = 0; y < pos_y; y++) {
            cmd.gotoxy(0, y);
            std::cout << full;
        }

        //right
        for (int y = 0; y <= size_y; y++) {
            cmd.gotoxy(pos_x + size_x, y + pos_y);
            std::cout << right;
        }

        //down
        for (int y = 0; y < height_console - (pos_y + size_y); y++) {
            cmd.gotoxy(0, y + pos_y + size_y);
            std::cout << full;
        }

        //fix side right
        cmd.color(color_bg.get_bg(), color_bg.get_bg());
        if (visulize_debug_info == true) {
            cmd.color(15, 0);
        }

        for (int y = 0; y < pos_y; y++) {
            cmd.gotoxy(0, y);
            std::cout << '.';
        }
        
        for (int y = 0; y < height_console - (pos_y + size_y); y++) {
            cmd.gotoxy(0, y + pos_y + size_y);
            std::cout << '.';
        }

        for (int y = 0; y < size_y; y++) {
            cmd.gotoxy(pos_x + size_x, y + pos_y);
            std::cout << '.';
        }
    }

    void print_border() const {
        std::string line(size_x, char_border);
        cmd.color(color_border.get_font(), color_border.get_bg());

        for (int y = 0; y < size_y; y++) {
            cmd.gotoxy(pos_x, y + pos_y);
            std::cout << char_border;
            cmd.gotoxy(size_x + pos_x - 1, y + pos_y);
            std::cout << char_border;
        }

        cmd.gotoxy(pos_x, pos_y);
        std::cout << line;
        cmd.gotoxy(pos_x, pos_y + size_y - 1);
        std::cout << line;
        cmd.color(color_bg.get_font(), color_bg.get_bg());
    }

    int get_offset_x() const {
        return pos_x;
    }

    int get_offset_y() const {
        return pos_y;
    }

    int get_size_x() const {
        return size_x;
    }

    int get_size_y() const {
        return size_y;
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

private:
    int width_console;
    int height_console;
    int pos_x = 0;
    int pos_y = 0;
    int size_x = 60;
    int size_y = 18;
    Color color_plane;
    Color color_bg;
    Color color_border;
    char char_plane = ' ';
    char char_bg = ' ';
    char char_border = ' ';
    Console cmd;
};

