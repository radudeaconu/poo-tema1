//
// Created by Owner on 6/1/2024.
//

#include <random>
#include "Entity.h"

#ifndef OOP_WALL_H
#define OOP_WALL_H
class Wall: public Entity{
    //int x, y,
    int x_length, y_length;
    //char symbol;
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen;       // Standard mersenne_twister_engine seeded with rd()

public:
    Wall();
    Wall(int x, int y, char symbol, int x_length, int y_length);
    Wall(const Wall& other);
    std::shared_ptr<Entity> clone() const override{
        return std::make_shared<Wall>(*this);
    }

    void initialize() override;

    int getXLength() const;

    int getYLength() const;
};

#endif //OOP_WALL_H
