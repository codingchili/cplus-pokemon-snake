//
// Created by chili on 2016-08-03.
//

#ifndef CPLUS_POKESNAKE_GAME_H
#define CPLUS_POKESNAKE_GAME_H


const int MAP_SIZE = 32;
const char WALL = 'W';

struct Player {
    int x;
    int y;
};

class Game {
public:
    Game();

    ~Game();

    char GetTile(int x, int y);

    int GetPlayerY();

    int GetPlayerX();
};


#endif
