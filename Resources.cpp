//
// Created by chili on 2016-08-03.
//

#include "Graphics.h"
#include "Resources.h"

const char *FILE_BACKGROUND = "background.bmp";
const char *FILE_WALL = "wall.bmp";
const char *FILE_HEAD = "head.bmp";

Resources::~Resources() {
    FreeBitmap(background);
    FreeBitmap(head);
    FreeBitmap(wall);
}

bool Resources::load() {
    return LoadBitmapFromFile(FILE_BACKGROUND, background) &&
           LoadBitmapFromFile(FILE_HEAD, head) &&
           LoadBitmapFromFile(FILE_WALL, wall);
}
