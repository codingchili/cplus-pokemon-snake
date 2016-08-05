/**
 * @author Robin Duda
 *
 * Snake game logic.
 */

#ifndef CPLUS_POKESNAKE_GAME_H
#define CPLUS_POKESNAKE_GAME_H

const int STATE_START = 1;
const int STATE_GAMEPLAY = 2;
const int STATE_NEXTLEVEL = 3;
const int STATE_GAMEOVER = 4;
const int STATE_GAMEWIN = 5;

const double BASE_SPEED = 0.8;
const double SEGMENT_SPEED_BONUS = 0.025;
const double LEVEL_SPEED_BONUS = 0.15;

const int MAX_LEVEL = 4;
const int HALF_TILE = 8;
const int TILE_SIZE = 16;
const int SPAWN_RATE = 150;
const int POKEMON_MAX = 8;
const int POKEMON_MEW = 1;
const int NORTH = 1;
const int WEST = 2;
const int SOUTH = 3;
const int EAST = 4;
const int PLAYER_MAXLEN = 24;
const int MAP_SIZE = 32;
const char WALL = 'W';
const char FREE = ' ';

struct Position {
    double x;
    double y;
};

struct Segment {
    Position position;
    bool attached;
};

struct Player {
    Position position;
    int direction = SOUTH;
    Segment *segment[PLAYER_MAXLEN];
};

struct Pokemon {
    Position position;
    int type;
};

class Game {
private:
    Pokemon *pokemon[POKEMON_MAX] = {};
    Player *player;
    char map[MAP_SIZE][MAP_SIZE] = {};
    int animationTick = 0;
    int gameplayTick = 0;
    int level = 1;
    bool captured = false;
    int state = STATE_START;

    void Move();

    bool HitSelf();

    bool HitWall();

    void Spawn();

    void UpdateSegments();

    bool Capture();

    void AddSegment();

    bool CheckCollison(Position object, Position fixed, int size);

    bool CheckWallCollision(Position object, int x, int y);

    bool CheckSegmentWallCollision(int x, int y);

    int RandomPosition();

    bool MinimumDistanceEitherAxis(Position p1, Position p2, int maxDistance);

    bool Lost();

    bool Won();

    bool LevelCleared();

    void Reset();

    double GetPlayerSpeed();

public:
    Game();

    ~Game();

    /**
     * Returns the tile type at a given position on the map.
     */
    char GetTile(int x, int y);

    Segment *GetSegment(int index);

    int GetPlayerY();

    int GetPlayerX();

    int GetSegmentCount();

    void SetPlayerFacing(int direction);

    void Update();

    int GetState();

    void End();

    void Start();

    void StartNextLevel();

    Pokemon *GetPokemon(int index);

    int GetLevel();

    int GetTime();

    bool WasCaptured();
};

#endif
