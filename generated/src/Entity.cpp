//
// Created by Owner on 6/1/2024.
//
#include "Entity.h"

int Entity::getX() const {
    return x;
}

int Entity::getY() const {
    return y;
}

char Entity::getSymbol() const {
    return symbol;
}

Entity::Entity(int _x, int _y, char _symbol) : x(_x), y(_y), symbol(_symbol) {}

Entity::Entity(char _symbol) : symbol(_symbol) {}

Entity::Entity(const Entity &other) = default;
