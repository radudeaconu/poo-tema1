//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_ENEMY_H
#define OOP_ENEMY_H

#include "Entity.h"
#include <ostream>
#include <random>

class Enemy: public Entity{

    std::random_device rd;
    std::mt19937 gen;

public:
    Enemy();
    Enemy(int x, int y, char symbol);
    Enemy(const Enemy& other);
    std::shared_ptr<Entity> clone() const override{
        return std::make_shared<Enemy>(*this);
    }
    ~Enemy() override;

    void initialize() ;

    void move(int directionX, int directionY);

    int randomMovement();


    friend std::ostream &operator<<(std::ostream &os, const Enemy &enemy);

};

#endif //OOP_ENEMY_H
