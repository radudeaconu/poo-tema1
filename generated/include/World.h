//
// Created by Owner on 6/1/2024.
//

#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <array>
#include <chrono>
#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Wall.h"
#include "rlutil.h"


char key();

class World{
    Player player;
    std::array<Wall, 15> walls;
    Enemy enemy;
    std::array<std::string, 18> game_map;
    int score=0,lives;
    bool gata= false;

    void initialize(char icon);
    void generate();
public:

    explicit World(char icon);

    World();

    World(const Player &player, const std::array<Wall, 15> &walls, const Enemy &enemy, int score, int lives);

    const Player &getPlayer() const;
    const int& getScore() const;

    friend std::ostream &operator<<(std::ostream &os, const World &world);

    void nextLevel();
    char checkPosition(int x, int y);
    void playerMovement();
    void play();
    void gunMovement();
    void enemyMovement();
};


#endif //OOP_WORLD_H
