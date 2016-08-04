//
// Created by chili on 2016-08-03.
//

#ifndef CPLUS_POKESNAKE_GAME_H
#define CPLUS_POKESNAKE_GAME_H

const int HALF_TILE = 8;
const int TILE_SIZE = 16;
const int SPAWN_RATE = 150;
const int POKEMON_MAX = 8;
const int POKEMON_PIKACHU = 1;
const int POKEMON_MEW = 2;
const int NORTH = 1;
const int WEST = 2;
const int SOUTH = 3;
const int EAST = 4;
const int PLAYER_MAXLEN = 32;
const int MAP_SIZE = 32;
const char WALL = 'W';
const char FREE = ' ';

struct Position {
    int x;
    int y;
};

struct Segment {
    Position position;
    bool attached;

    Segment() {
        attached = false;
    }
};

struct Player {
    Position position;
    int direction = SOUTH;
    Segment *segment[PLAYER_MAXLEN];

    Player() {
        position.x = 365;
        position.y = 125;
    }
};

struct Pokemon {
    Position position;
    int type;
};

class Game {
private:
    Pokemon *pokemon[POKEMON_MAX] = {};
    char map[MAP_SIZE][MAP_SIZE] = {};
    Player *player;
    int tick = 0;

    void Move();

    bool HitSelf();

    bool HitWall();

    void Spawn();

    void UpdateSegments();

    void Capture();

    void AddSegment();

    bool CheckCollison(Position object, Position fixed, int size);

    bool CheckWallCollision(Position object, int x, int y);

    bool CheckSegmentWallCollision(int x, int y);

    int RandomPosition();

    bool MinimumDistanceEitherAxis(Position p1, Position p2, int maxDistance);

public:
    Game();

    ~Game();

    char GetTile(int x, int y);

    Segment *GetSegment(int index);

    int GetPlayerY();

    int GetPlayerX();

    bool Lost();

    bool Won();

    int GetSegmentCount();

    void SetPlayerFacing(int direction);

    void Tick();

    Pokemon *GetPokemon(int index);


};


#endif
