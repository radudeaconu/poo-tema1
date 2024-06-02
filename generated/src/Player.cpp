//
// Created by Owner on 6/1/2024.
//
#include "Player.h"

Player::Player(char symbol) : Entity(1,1, symbol){
    if(symbol == '$' || symbol == '#' || symbol == 'H' || !(isalnum(symbol)))
        throw NameError(symbol);
}

Player::Player(int x, int y, char symbol) : Entity(x, y, symbol) {
    if(symbol == '$' || symbol == '#' || symbol == 'H')
        throw NameError(symbol);
}

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

void Player::initialize() {
    x=1;
    y=1;
    gun.initialize();
}
void Player::fire(){
    gun.fire(x+1, y);
}
Gun& Player::getGun() {
    return gun;
}

Gun::Gun(int x, int y, char symbol, bool isFired): Entity(x, y, symbol), isFired(isFired){}


void Gun::fire(int _x, int _y) {
    if(isFired)
        throw FireError();
    x = _x;
    y = _y;
    isFired = true;
}

bool Gun::getIsFired(){
    return isFired;
}

void Gun::move(){
    x+=3;
}
void Gun::initialize() {
    isFired=false;
    x=0;
    y=0;
}
