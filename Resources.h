/**
 * @author Robin Duda
 *
 * Handles the loading of resource files.
 */

#ifndef CPLUS_POKESNAKE_RESOURCES_H
#define CPLUS_POKESNAKE_RESOURCES_H

#include "Graphics.h"

class Resources {
private:
    static const int FILE_COUNT = 11;
    const char *FILES[FILE_COUNT] = {"background.bmp", "wall.bmp", "head.bmp", "segment.bmp", "start.bmp",
                                     "start-game.bmp", "gameover.bmp", "gamewin.bmp", "mew.bmp", "pikachu.bmp",
                                     "nextlevel.bmp"};
public:
    Bitmap background;
    Bitmap head;
    Bitmap wall;
    Bitmap segment;
    Bitmap start;
    Bitmap startgame;
    Bitmap gameover;
    Bitmap gamewin;
    Bitmap mew;
    Bitmap pikachu;
    Bitmap nextlevel;

    Bitmap *bitmaps[FILE_COUNT] = {&background, &wall, &head, &segment, &start, &startgame, &gameover, &gamewin, &mew,
                                   &pikachu, &nextlevel};

    ~Resources();

    bool Load();
};

#endif
