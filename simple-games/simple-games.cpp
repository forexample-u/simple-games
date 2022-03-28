#include <iostream>
#include <string>

class Plane {
public:
    void set_size(int width, int height) {
        this->width = width;
        this->height = height;
    }

    void print() {
        std::string row;
        row.assign(width, 'a');
        for (int i = 0; i < height; i++) {
            std::cout << row << '\n';
        }
    }

private:
    int width;
    int height;
};

int main(){
    Plane plane;
    plane.set_size(10, 5);
    plane.print();
}