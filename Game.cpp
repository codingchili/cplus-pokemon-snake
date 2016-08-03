//
// Created by chili on 2016-08-03.
//

#include "Game.h"

// todo define the map here, draw walls from the map data.

char map[MAP_SIZE][MAP_SIZE] = {};
Player *player = new Player();

Game::Game() {
    player->x = 6;
    player->y = 6;

    for (int i = 0; i < MAP_SIZE; i++) {
        map[i][0] = WALL;
        map[0][i] = WALL;
        map[MAP_SIZE - 1][i] = WALL;
        map[i][MAP_SIZE - 1] = WALL;
    }
}

Game::~Game() {
    delete player;
}


char Game::GetTile(int x, int y) {
    return map[x][y];
}

int Game::GetPlayerX() {
    return player->x;
}

int Game::GetPlayerY() {
    return player->y;
}