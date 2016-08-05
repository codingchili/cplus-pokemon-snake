/**
 * Handles tiles that moves and changes per level.
 */

#ifndef CPLUS_POKESNAKE_LEVEL_H
#define CPLUS_POKESNAKE_LEVEL_H


class Level {
private:
    static char GetFirstLevel(int x, int y, int tick);

    static char GetSecondLevel(int x, int y, int tick);

    static char GetThirdLevel(int x, int y, int tick);

    static char GetFourthLevel(int x, int y, int tick);

public:
    static char GetTile(int x, int y, int level, int tick_seed);
};


#endif //CPLUS_POKESNAKE_LEVEL_H
