//
// Created by Owner on 6/1/2024.
//

#include "Wall.h"


Wall::Wall() : Entity('#'), gen(rd()) {initialize();}

Wall::Wall(int x, int y, char symbol, int x_length, int y_length) :Entity(x, y, symbol), x_length(x_length), y_length(y_length), gen(rd()) {}

Wall::Wall(const Wall &other) : Entity(dynamic_cast<const Entity&> (other)), x_length{other.x_length}, y_length{other.y_length} {}

void Wall::initialize() {

    std::uniform_int_distribution<> x_length_dist(1, 10); // Distribution for x_length from 1 to 3
    std::uniform_int_distribution<> y_length_dist(1, 3); // Distribution for y_length from 1 to 10
    x_length = x_length_dist(gen); // Generate random x_length
    y_length = y_length_dist(gen); // Generate random y_length
    std::uniform_int_distribution<> x_dist(1, 60-x_length); // Distribution for x coordinates from 1 to 60
    std::uniform_int_distribution<> y_dist(1, 16-y_length); // Distribution for y coordinates from 1 to 16
    x = x_dist(gen); // Generate random x coordinate within bounds
    y = y_dist(gen); // Generate random y coordinate within bounds
}

int Wall::getXLength() const {
    return x_length;
}

int Wall::getYLength() const {
    return y_length;
}


