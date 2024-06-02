#include <iostream>
#include <chrono>
#include "rlutil.h"
#include "Player.h"
#include "Enemy.h"
#include <World.h>

//char key() {
//    time_t start = time(NULL);
//    while (!kbhit()) {
//        if (time(NULL) - start >= 0.3)
//            return -1;
//    }
//    return getch();
//}


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
    try {
        char icon;

        std::cout << "select (by pressing) the character for your player icon...";
        icon = getch();
        std::cout << "\n\nyou selected: " << icon;
        rlutil::anykey("\n\npress e to continue\n\n");

        World world(/*(char)*/ icon);

        rlutil::cls();

        //World world((char) icon);
        std::cout << world.getPlayer();
        rlutil::anykey();
        //world.initialize();
        std::cout << world;
        world.play();
        rlutil::cls();
        std::cout<<"\n ######      ###    ##     ## ########     #######  ##     ## ######## ######## \n"
                   <<"##    ##    ## ##   ###   ### ##          ##     ## ##     ## ##       ##     ##\n"
                   <<"##         ##   ##  #### #### ##          ##     ## ##     ## ##       ##     ##\n"
                   <<"##   #### ##     ## ## ### ## ######      ##     ## ##     ## ######   ######## \n"
                   <<"##    ##  ######### ##     ## ##          ##     ##  ##   ##  ##       ##   ##  \n"
                   <<"##    ##  ##     ## ##     ## ##          ##     ##   ## ##   ##       ##    ## \n"
                   <<" ######   ##     ## ##     ## ########     #######     ###    ######## ##     ##\n"
                   <<"                                   SCORE: "<<world.getScore()<<"\n";
    }
    catch (NameError& err){
        std::cout<< err.what();
    }

    return 0;
}
