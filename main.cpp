#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include "rlutil.h"
//#include <Helper.h>


//char key() {
//    time_t start = time(NULL);
//    while (!kbhit()) {
//        if (time(NULL) - start >= 0.3)
//            return -1;
//    }
//    return getch();
//}

char key() {
    const auto start = std::chrono::steady_clock::now();
    using namespace std::chrono_literals;
    while (!kbhit()) {
        if (std::chrono::steady_clock::now() - start >= 0.3s)
            return -1;
    }
    return getch();
}
class Player{
    int x,y;
    char symbol;

public:
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    char getSymbol() const {
        return symbol;
    }

    Player(): x{1}, y{1}, symbol{'o'} {}
    explicit Player(int x_, int y_, char symbol_='o') : x{x_}, y{y_}, symbol(symbol_) {}
    Player(const Player& other): x{other.x}, y{other.y}, symbol{other.symbol} {}
    Player& operator=(const Player& other){
        x = other.x;
        y = other.y;
        symbol = other.symbol;
        return *this;
    }
    ~Player() {}

    friend std::ostream &operator<<(std::ostream &os, const Player &player) {
        os << "x: " << player.x << " y: " << player.y << " symbol: " << player.symbol<<"\n";
        return os;
    }
    void move(int directionX, int directionY) {
        x=x+directionX;
        y=y+directionY;
    }
    void reset(){
        x=1;
        y=1;
    }
};


class Enemy{
    int x,y;
    char symbol;
    std::random_device rd;
    std::mt19937 gen;
    void initialize(){
        std::uniform_int_distribution<> x_dist(1, 60); // Distribution for x coordinates from 1 to 60
        std::uniform_int_distribution<> y_dist(1, 16); // Distribution for y coordinates from 1 to 16
        x = x_dist(gen); // Generate random x coordinate
        y = y_dist(gen); // Generate random y coordinate
    }

public:
    Enemy(): symbol{'$'}, gen(rd()) {initialize();}
    Enemy(int x, int y, char symbol) : x(x), y(y), symbol(symbol), gen(rd()) {}
    Enemy(const Enemy& other): x{other.x}, y{other.y}, symbol{other.symbol} {}


    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    char getSymbol() const {
        return symbol;
    }

    friend std::ostream &operator<<(std::ostream &os, const Enemy &enemy) {
        os << "x: " << enemy.x << " y: " << enemy.y << " symbol: " << enemy.symbol<<"\n";
        return os;
    }
    friend class World;

};

class Wall{
    int x, y, x_length, y_length;
    char symbol;
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen;       // Standard mersenne_twister_engine seeded with rd()

    void initialize(){

        std::uniform_int_distribution<> x_length_dist(1, 3); // Distribution for x_length from 1 to 3
        std::uniform_int_distribution<> y_length_dist(1, 10); // Distribution for y_length from 1 to 10
        x_length = x_length_dist(gen); // Generate random x_length
        y_length = y_length_dist(gen); // Generate random y_length
        std::uniform_int_distribution<> x_dist(1, 60-x_length); // Distribution for x coordinates from 1 to 60
        std::uniform_int_distribution<> y_dist(1, 16-y_length); // Distribution for y coordinates from 1 to 16
        x = x_dist(gen); // Generate random x coordinate within bounds
        y = y_dist(gen); // Generate random y coordinate within bounds
    }

public:
    Wall(): symbol{'#'}, gen(rd()) {initialize();}
    Wall(int x, int y, int x_length, int y_length, char symbol) : x(x), y(y), x_length(x_length), y_length(y_length), symbol(symbol), gen(rd()) {}
    Wall(const Wall& other): x{other.x}, y{other.y}, x_length{other.x_length}, y_length{other.y_length}, symbol{other.symbol} {}


    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getXLength() const {
        return x_length;
    }

    int getYLength() const {
        return y_length;
    }

    char getSymbol() const {
        return symbol;
    }
    friend class World;

};

class World{
    Player player;
    std::array<Wall, 15> walls;
    Enemy enemy;
    std::array<std::string, 18> game_map;
    int score=0,lives;
    bool gata= false;

    void initialize(){
        ///score+lives
        score=0;
        lives=3;
        generate();

    }
    void generate(){
        ///map borders
        game_map[0]="##############################################################";
        game_map[17]="##############################################################";
        for( int i=1;i<=16;i++)
            game_map[i]="#                                                            #";
        ///walls
        for(int i=0;i<15;i++){
            walls[i].initialize();
            for(int j=0;j<walls[i].getXLength();j++)
                for(int k=0;k<walls[i].getYLength();k++)
                    game_map[walls[i].getY()+j][walls[i].getX()+k] = walls[i].getSymbol();
        }
        ///add player and enemy
        enemy.initialize();
        game_map[player.getY()][player.getX()] = player.getSymbol();
        game_map[enemy.getY()][enemy.getX()] = enemy.getSymbol();
    }
public:
    World() {initialize();}

    World(const Player &player, const std::array<Wall, 15> &walls, const Enemy &enemy, int score, int lives) : player(
            player), walls(walls), enemy(enemy), score(score), lives(lives) {}

    const Player &getPlayer() const {
        return player;
    }

//    const std::array<Wall, 15> &getWalls() const {
//        return walls;
//    }

    friend std::ostream &operator<<(std::ostream &os, const World &world) {
        os << "score: " << world.score << "\nlives: " << world.lives<< "\ngame_map:\n" << world.game_map[0] << "\n"
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

    void nextLevel(){
        //game_map[player.getY()][player.getX()]=' ';
        player.reset();
        generate();
        score++;
    }
    void movement(){
        game_map[player.getY()][player.getX()] = ' ';
        rlutil::cls();
        //while(kbhit()) {
//            switch (key()) {
//                case 'a': {
//                    if (game_map[player.getY()][player.getX() - 1] == enemy.getSymbol()){
//                        nextLevel();
//                        break;
//                    }
//                    if (game_map[player.getY()][player.getX() - 1] == ' ') {
//                        player.move_left();
//                        //game_map[player.getY()][player.getX()] = ' ';
//                    }
//                    break;
//                }
//                case 'd': {
//                    if (game_map[player.getY()][player.getX() + 1] == enemy.getSymbol()){
//                        nextLevel();
//                        break;
//                    }
//                    if (game_map[player.getY()][player.getX() + 1] == ' ') {
//                        player.move_right();
//                        // game_map[player.getY()][player.getX()] = ' ';
//                    }
//                    break;
//                }
//                case 'w': {
//                    if (game_map[player.getY() - 1][player.getX()] == enemy.getSymbol()){
//                        nextLevel();
//                        break;
//                    }
//                    if (game_map[player.getY() - 1][player.getX()] == ' ')
//                        player.move_up();
//                    break;
//                }
//                case 's': {
//                    if (game_map[player.getY() + 1][player.getX()] == enemy.getSymbol()){
//                        nextLevel();
//                        break;
//                    }
//                    if (game_map[player.getY() + 1][player.getX()] == ' ')
//                        player.move_down();
//                    break;
//                }
//                case 'q': {
//                    gata = true;
//                    break;
//                }
//                case 'e': {
//                    std::cout << "Player information: " << getPlayer() << "\n";
//                    break;
//                }
//                default: {
//                    //std::cout << "invalid input\n";
//                }
//            }
//        //}
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
            case 'q':
                gata = true;
                break;
        }

        int nextX = player.getX() + directionX;
        int nextY = player.getY() + directionY;

        if(game_map[nextY][nextX] == enemy.getSymbol())
            nextLevel();
        else if(game_map[nextY][nextX] == ' ')
            player.move(directionX, directionY);
        game_map[player.getY()][player.getX()] = player.getSymbol();
    }
    void play(){

        while(!gata) {

            movement();

            std::cout<<*this;
        }

    }


};

int main() {

    Player p1;
    Player p2(2,3,'%'),p3(p1);
    p3=p2;
    p2.move(-1,0);
    p2.move(0,1);
    std::cout<<"p2: "<<p2<<"p3: "<<p3;

    Enemy e1;
    Enemy e2(5,4,'^');
    Enemy e3(e1);
    std::cout<<"e2: "<<e2<<"e3: "<<e3;

    rlutil::anykey("press e to continue");

    rlutil::cls();


    World world;
    //world.initialize();
    std::cout<<world;
    world.play();

    return 0;
}
