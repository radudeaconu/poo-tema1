//
// Created by Owner on 6/1/2024.
//
#include "Enemy.h"

Enemy::Enemy() : Entity('$'), gen(rd()) {
    std::uniform_int_distribution<> x_dist(1, 60); // Distribution for x coordinates from 1 to 60
    std::uniform_int_distribution<> y_dist(1, 16); // Distribution for y coordinates from 1 to 16
    x = x_dist(gen); // Generate random x coordinate
    y = y_dist(gen); // Generate random y coordinate
}

Enemy::Enemy(int x, int y, char symbol) : Entity(x, y, symbol), /*x(x), y(y), symbol(symbol),*/ gen(rd()) {}

Enemy::Enemy(const Enemy &other) : Entity(other)/*: x{other.x}, y{other.y}, symbol{other.symbol}*/ {}

Enemy::~Enemy() = default;

void Enemy::initialize() {
    std::uniform_int_distribution<> x_dist(1, 60); // Distribution for x coordinates from 1 to 60
    std::uniform_int_distribution<> y_dist(1, 16); // Distribution for y coordinates from 1 to 16
    x = x_dist(gen); // Generate random x coordinate
    y = y_dist(gen); // Generate random y coordinate
}

int Enemy::randomMovement() {
    std::uniform_int_distribution<> dir(-2, 2); // Random direction -1, 0, or 1 for both x and y
    int move = dir(gen);
    if(move % 2 == 0)
        move /= 2;
    return move;
}
void Enemy::move(int directionX, int directionY) {

    x=x+directionX;
    y=y+directionY;
}

std::ostream &operator<<(std::ostream &os, const Enemy &enemy) {
    os << "x: " << enemy.x << " y: " << enemy.y << " symbol: " << enemy.symbol<<"\n";
    return os;
}
