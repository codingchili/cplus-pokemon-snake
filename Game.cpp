#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Level.h"

Game::Game() {
    srand((unsigned int) time(NULL));
    player = new Player();

    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        player->segment[i] = new Segment();
    }

    // Create a wall around the map.
    for (int i = 0; i < MAP_SIZE; i++) {
        map[i][0] = WALL;
        map[0][i] = WALL;
        map[MAP_SIZE - 1][i] = WALL;
        map[i][MAP_SIZE - 1] = WALL;
    }

    Reset();
}

Game::~Game() {
    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        delete player->segment[i];
    }

    for (int i = 0; i < POKEMON_MAX; i++) {
        if (pokemon[i] != nullptr) {
            delete pokemon[i];
        }
    }
    delete player;
}


/**
 * Handles dynamic tiles that move during the gameplay.
 */
char Game::GetTile(int x, int y) {
    int tick_seed = (animationTick / 60) % MAP_SIZE;
    char dynamic_tile = Level::GetTile(x, y, level, tick_seed);

    return (dynamic_tile == WALL) ? WALL : map[x][y];
}

int Game::GetPlayerX() {
    return (int) player->position.x;
}

int Game::GetPlayerY() {
    return (int) player->position.y;
}

void Game::SetPlayerFacing(int direction) {
    if (direction != -1)
        player->direction = direction;
}

Pokemon *Game::GetPokemon(int index) {
    return pokemon[index];
}

void Game::Update() {
    if (state == STATE_GAMEPLAY) {
        Move();
        captured = Capture();
        Spawn();

        if (Lost())
            state = STATE_GAMEOVER;
        else if (Won()) {
            state = STATE_GAMEWIN;
        } else if (LevelCleared()) {
            state = STATE_NEXTLEVEL;
        }

        gameplayTick++;
        animationTick++;
    }
}

void Game::Reset() {
    animationTick = 1;

    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        player->segment[i]->attached = false;
    }

    for (int i = 0; i < POKEMON_MAX; i++) {
        delete pokemon[i];
        pokemon[i] = nullptr;
    }

    player->direction = SOUTH;
    player->position.x = 365;
    player->position.y = 125;
}

void Game::Move() {
    switch (player->direction) {
        case NORTH:
            player->position.y -= GetPlayerSpeed();
            break;
        case WEST:
            player->position.x -= GetPlayerSpeed();
            break;
        case SOUTH:
            player->position.y += GetPlayerSpeed();
            break;
        case EAST:
            player->position.x += GetPlayerSpeed();
            break;
        default:
            break;
    }
    UpdateSegments();
}

/**
 * Calculates the player speed based on the current level and number of attached segments.
 */
double Game::GetPlayerSpeed() {
    return ((level - 1) * LEVEL_SPEED_BONUS + GetSegmentCount() * SEGMENT_SPEED_BONUS + BASE_SPEED);
}

/**
 * Moves all segments forward whenever the head is one full segment away.
 */
void Game::UpdateSegments() {
    if (MinimumDistanceEitherAxis(player->position, player->segment[0]->position, TILE_SIZE)) {

        // Right shift the positions of all the segments to simulate movement.
        for (int i = PLAYER_MAXLEN - 1; i >= 0; i--) {
            Position *segment = &player->segment[i]->position;
            Position *previous = &player->segment[i - 1]->position;

            if (i == 0) {
                segment->x = GetPlayerX();
                segment->y = GetPlayerY();
            } else {
                segment->x = previous->x;
                segment->y = previous->y;
            }
        }
    }
}

/**
 * Determine if the distance between two points on either axis is greater than the given distance.
 */
bool Game::MinimumDistanceEitherAxis(Position p1, Position p2, int maxDistance) {
    return (abs((int) (p1.x - p2.x)) >= maxDistance) || (abs((int) (p1.y - p2.y)) >= maxDistance);
}

/**
 * Adds a pokemon that collides with the head as a segment.
 */
bool Game::Capture() {
    for (int i = 0; i < POKEMON_MAX; i++) {

        if (pokemon[i] != nullptr) {
            if (CheckCollison(player->position, pokemon[i]->position, TILE_SIZE)) {
                delete pokemon[i];
                pokemon[i] = nullptr;

                AddSegment();
                return true;
            }
        }
    }
    return false;
}

/**
 * Check for a collision between two points using given radius.
 */
bool Game::CheckCollison(Position object, Position fixed, int size) {
    return abs((int) (object.x - fixed.x)) < size && abs((int) (object.y - fixed.y)) < size;
}

void Game::AddSegment() {
    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        if (!player->segment[i]->attached) {
            player->segment[i]->attached = true;
            break;
        }
    }
}

/**
 * Adds a new pokemon in a random position on the map.
 */
void Game::Spawn() {
    if (rand() % SPAWN_RATE == 0) {

        for (int i = 0; i < POKEMON_MAX; i++) {
            if (pokemon[i] == nullptr) {
                Pokemon *spawned = new Pokemon();

                spawned->position.x = RandomPosition();
                spawned->position.y = RandomPosition();
                spawned->type = rand() % 2 + 1;

                pokemon[i] = spawned;
                break;
            }
        }
    }
}

int Game::RandomPosition() {
    return (rand() % (MAP_SIZE - 4) + 2) * TILE_SIZE;
}

bool Game::Lost() {
    return (HitWall() || HitSelf());
}

bool Game::HitWall() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int k = 0; k < MAP_SIZE; k++) {

            if (GetTile(i, k) == WALL) {
                if (CheckWallCollision(player->position, i, k) || CheckSegmentWallCollision(i, k))
                    return true;
            }
        }
    }
    return false;
}

bool Game::CheckWallCollision(Position object, int x, int y) {
    return (abs((int) (object.x - x * TILE_SIZE)) < TILE_SIZE && abs((int) (object.y - y * TILE_SIZE)) < TILE_SIZE);
}

/**
 * Check if any of the segments collides with a wall. (Required only for moving walls!)
 */
bool Game::CheckSegmentWallCollision(int x, int y) {
    for (int n = 0; n < PLAYER_MAXLEN; n++) {
        Segment *segment = player->segment[n];

        if (segment->attached && CheckWallCollision(segment->position, x, y)) {
            return true;
        }
    }
    return false;
}

/**
 * Check if the head has moved into any of its attached segments.
 */
bool Game::HitSelf() {
    for (int i = 1; i < PLAYER_MAXLEN; i++) {
        Segment *segment = player->segment[i];

        if (segment->attached && CheckCollison(segment->position, player->position, HALF_TILE)) {
            return true;
        }
    }
    return false;
}

bool Game::Won() {
    return (LevelCleared() && level == MAX_LEVEL);
}

bool Game::LevelCleared() {
    return (GetSegmentCount() == PLAYER_MAXLEN);
}

int Game::GetSegmentCount() {
    int segments = 0;

    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        if (player->segment[i]->attached) {
            segments++;
        }
    }
    return segments;
}

Segment *Game::GetSegment(int index) {
    return player->segment[index];
}

void Game::End() {
    state = STATE_START;
}

void Game::Start() {
    level = 1;
    gameplayTick = 0;
    Reset();
    state = STATE_GAMEPLAY;
}

void Game::StartNextLevel() {
    state = STATE_GAMEPLAY;
    level++;
    Reset();
}

int Game::GetState() {
    return state;
}

int Game::GetLevel() {
    return level;
}

int Game::GetTime() {
    return gameplayTick;
}

bool Game::WasCaptured() {
    return captured;
}








