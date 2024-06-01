//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <ostream>
#include "Entity.h"


class Player: public Entity{

public:

    Player(int x=1, int y=1, char symbol='o');
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player() {}

    // Metoda swap
    friend void swap(Player& first, Player& second);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);
    void move(int directionX, int directionY);
    void reset();
};

#endif //OOP_PLAYER_H
