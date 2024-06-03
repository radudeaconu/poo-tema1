//
// Created by Owner on 6/1/2024.
//
#include "World.h"

int World::highscore = 0;

void World::initialize(char icon) {
    this->player=Player(icon);
    ///score+lives
    score=0;
    //lives=3;
    enemy.initialize();
    generate();

}

void World::generate() {
    ///map borders
    game_map[0]="HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH";
    game_map[17]="HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH";
    for( int i=1;i<=16;i++)
        game_map[i]="H                                                            H";
    ///walls
    for(int i=0;i<15;i++){
        walls[i].initialize();
        for(int j=0;j<walls[i].getXLength();j++)
            for(int k=0;k<walls[i].getYLength();k++)
                game_map[walls[i].getY()+k][walls[i].getX()+j] = walls[i].getSymbol();
    }
    ///add player and enemy

    game_map[player.getY()][player.getX()] = player.getSymbol();
    game_map[enemy.getY()][enemy.getX()] = enemy.getSymbol();
}

World::World(char icon) {initialize(icon);}

World::World() {initialize('o');}

World::World(const Player &player, const std::array<Wall, 15> &walls, const Enemy &enemy, int score, int lives) : player(
        player), walls(walls), enemy(enemy), score(score), lives(lives) {}

const Player &World::getPlayer() const {
    return player;
}
//const int& World::getScore() const {
//    return score;
//}

std::ostream &operator<<(std::ostream &os, const World &world) {
    os << "\nscore: " << world.score/* << "\nlives: " << world.lives*/<< "\ngame_map:\n" << world.game_map[0] << "\n"
       << world.game_map[1] << "\n"
       << world.game_map[2] << "\n"
       << world.game_map[3] << "\n"
       << world.game_map[4] << "\n"
       << world.game_map[5] << "\n"
       << world.game_map[6] << "\n"
       << world.game_map[7] << "\n"
       << world.game_map[8] << "\n"
       << world.game_map[9] << "\n"
       << world.game_map[10] << "\n"
       << world.game_map[11] << "\n"
       << world.game_map[12] << "\n"
       << world.game_map[13] << "\n"
       << world.game_map[14] << "\n"
       << world.game_map[15] << "\n"
       << world.game_map[16] << "\n"
       << world.game_map[17] << "\n";
    return os;
}

char key() {
    const auto start = std::chrono::steady_clock::now();
    using namespace std::chrono_literals;
    while (!kbhit()) {
        if (std::chrono::steady_clock::now() - start >= 0.3s)
            return -1;
    }
    return getch();
}

void World::nextLevel() {
    //game_map[player.getY()][player.getX()]=' ';
    player.initialize();
    enemy.initialize();
    generate();
    score++;
    if (score > highscore)
        highscore = score;
}

char World::checkPosition(int x, int y) {
    return game_map[y][x];
}

void World::gunMovement() {
    bool clear=true;
    game_map[player.getGun().getY()][player.getGun().getX()] = ' ';
    int X=player.getGun().getX();
    for (int i=1;i<=3;i++){
        switch(checkPosition(X+i,player.getGun().getY())) {
            case '#':
                clear=false;
                game_map[player.getGun().getY()][X+i]=' ';
                break;
            case '$':
                nextLevel();
                break;
            case 'H':
                clear=false;
                break;
            case ' ':
                break;
       }
       if(!clear) break;

    }
    if(clear){
        player.getGun().move();
        game_map[player.getGun().getY()][player.getGun().getX()]=player.getGun().getSymbol();
    }
    else{
        game_map[player.getGun().getY()][player.getGun().getX()]=' ';
        player.getGun().initialize();
    }
}
void World::playerMovement() {
//    if(player.getGun().getIsFired()){
//
//        game_map[player.getGun().getY()][player.getGun().getX()]=player.getGun().getSymbol();
//    }
    game_map[player.getY()][player.getX()] = ' ';

    int directionX = 0, directionY = 0;

    switch(key()) {
        case 'a':
            directionX = -1;
            break;
        case 'd':
            directionX = +1;
            break;
        case 's':
            directionY = +1;
            break;
        case 'w':
            directionY = -1;
            break;
        case 'e':
            try {
                player.fire();
                game_map[player.getGun().getY()][player.getGun().getX()]=player.getGun().getSymbol();
            }
            catch (FireError &err){
                std::cout<<err.what();
            }
            break;
        case 'q':
            gata = true;
            break;
    }

    int nextX = player.getX() + directionX;
    int nextY = player.getY() + directionY;
    switch (checkPosition(nextX,nextY)){
        case '$':
            gata=true;
            break;
        case ' ':
            player.move(directionX, directionY);
            break;
        case '#':
            break;

    }

    game_map[player.getY()][player.getX()] = player.getSymbol();

}
void World::enemyMovement(){
    game_map[enemy.getY()][enemy.getX()] = ' ';
    int moveX = enemy.randomMovement();
    int moveY = enemy.randomMovement();
    if(enemy.getX()+moveX==player.getX() && enemy.getY()+moveY==player.getY())
        gata=true;
    if(checkPosition(enemy.getX() + moveX, enemy.getY() + moveY) == ' '){
        enemy.move(moveX, moveY);
    }
    game_map[enemy.getY()][enemy.getX()] = enemy.getSymbol();
}

void World::game() {

    while(!gata) {
        rlutil::cls();
        if(player.getGun().getIsFired())
            gunMovement();
        playerMovement();
        enemyMovement();
        std::cout<<*this;
    }

}
void World::play(){
    game();
    rlutil::cls();
    std::cout<<"\n ######      ###    ##     ## ########     #######  ##     ## ######## ######## \n"
             <<"##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ##\n"
             <<"##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ##\n"
             <<"##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ######## \n"
             <<"##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ##  \n"
             <<"##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ## \n"
             <<" ######   ##     ## ##     ## ########     #######     ###    ######## ##     ##\n"
             <<"               SCORE: "<<score<<"                               HIGHSCORE:" <<highscore<<"\n";

}

