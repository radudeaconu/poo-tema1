//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <iostream>
#include "Entity.h"
#include "Exception.h"

class Gun: public Entity{
    bool isFired = false;

public:
    Gun(int x = 0, int y = 0, char symbol = '-', bool isFired = false);
    Gun(const Gun& other) = default;
    ~Gun() override = default;
    std::shared_ptr<Entity> clone() const override{
        return std::make_shared<Gun>(*this);
    }
    void initialize() override;
    void fire(int _x, int _y);
    bool getIsFired();
    void move();

};


class Player: public Entity{
    Gun gun;

public:

    explicit Player(char symbol);
    Player(int x=1, int y=1, char symbol='o');
    Player(const Player& other);
    Player& operator=(const Player& other);
    ~Player() {}
    std::shared_ptr<Entity> clone() const override{
        return std::make_shared<Player>(*this);
    }

    // Metoda swap
    friend void swap(Player& first, Player& second);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);
    void move(int directionX, int directionY);
    void initialize() override;
    void fire();
    Gun& getGun();
};


#endif //OOP_PLAYER_H
