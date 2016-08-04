//
// Created by chili on 2016-08-03.
//

#ifndef CPLUS_POKESNAKE_RENDERER_H
#define CPLUS_POKESNAKE_RENDERER_H


#include "Resources.h"
#include "Game.h"

#define PI 3.14159265

const int WALL_SIZE = 16;
const int START_OFFSET = 440;
const int SEGMENT_OFFSET = 2;

class Renderer {
private:
    int tick = 1;
    Resources *resources;

    void DrawBackground();

    void DrawWalls(Game *game);

    void DrawPlayer(Game *game);

public:
    Renderer(Resources *resources);

    void Gameplay(Game *game);

    void StartView();

    void GameOver(Game *game);

    void DrawPokemons(Game *game);
};


#endif //CPLUS_POKESNAKE_RENDERER_H
