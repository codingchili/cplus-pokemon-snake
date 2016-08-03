//
// Created by chili on 2016-08-03.
//

#ifndef CPLUS_POKESNAKE_RENDERER_H
#define CPLUS_POKESNAKE_RENDERER_H


#include "Resources.h"
#include "Game.h"

class Renderer {
private:
    Resources *resources;

    void DrawBackground();

    void DrawWalls(Game *game);

public:
    Renderer(Resources *resources);

    void render(Game *game);

    void DrawPlayer(Game *game);
};


#endif //CPLUS_POKESNAKE_RENDERER_H
