//
// Created by Owner on 6/1/2024.
//
#include "Player.h"
Player::Player(int x, int y, char symbol) : Entity(x, y, symbol) {}

Player::Player(const Player &other) : Entity(dynamic_cast<const Entity&> (other)) {}

Player &Player::operator=(const Player &other) {
    x = other.x;
    y = other.y;
    symbol = other.symbol;
    return *this;
}

void swap(Player &first, Player &second) {
    using std::swap;
    swap(first.x, second.x);
    swap(first.y, second.y);
    // Swap alte membri dacă există
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "x: " << player.x << " y: " << player.y << " symbol: " << player.symbol<<"\n";
    return os;
}

void Player::move(int directionX, int directionY) {
    x=x+directionX;
    y=y+directionY;
}

void Player::reset() {
    x=1;
    y=1;
}

