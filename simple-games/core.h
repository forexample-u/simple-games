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

//coord
struct Coord {
    Coord() {}
    Coord(int new_x, int new_y) {
        this->x = new_x;
        this->y = new_y;
    }

    Coord operator+=(const Coord& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    bool operator==(const Coord& other) {
        return ((x == other.x) && (y == other.y));
    }

    int x = 0;
    int y = 0;
};

//size
struct Size {
    Size() {}
    Size(int new_width, int new_height) {
        this->width = new_width;
        this->height = new_height;
    }
    int width = 0;
    int height = 0;
};

//dir
struct Dir {
    Dir() {}
    Dir(int dir_x, int dir_y) {
        x = dir_x;
        y = dir_y;
    }
    int x;
    int y;
};
