#include "Level.h"
#include "Game.h"


char Level::GetTile(int x, int y, int level, int tick) {
    switch (level) {
        case 1:
            return GetFirstLevel(x, y, tick);
        case 2:
            return GetSecondLevel(x, y, tick);
        case 3:
            return GetThirdLevel(x, y, tick);
        case 4:
            return GetFourthLevel(x, y, tick);
        default:
            return FREE;
    }
}

char Level::GetFirstLevel(int x, int y, int tick) {
    if ((x == 15 && y == 15) || (x == 16 && y == 16) || (x == 15 && y == 16) || (x == 16 && y == 15))
        return WALL;

    return FREE;
}

char Level::GetSecondLevel(int x, int y, int tick) {

    if (x == tick || MAP_SIZE - tick == x) {
        if (y == 8 || y == 24)
            return WALL;
    }
    return FREE;
}

char Level::GetThirdLevel(int x, int y, int tick) {
    if (x == tick || MAP_SIZE - tick == x) {
        if (y == 16)
            return WALL;
    }

    if (y == tick || MAP_SIZE - tick == y) {
        if (x == 16)
            return WALL;
    }

    return FREE;
}

char Level::GetFourthLevel(int x, int y, int tick) {
    if (y == tick && x > 6 && x < 25) {
        return WALL;
    }

    if (MAP_SIZE - tick == y && x > 6 && x < 25) {
        return WALL;
    }

    return FREE;
}
