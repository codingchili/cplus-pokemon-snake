//
// Created by chili on 2016-08-03.
//

#include <cstdlib>
#include <ctime>
#include "Game.h"

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
    int tick_seed = (tick / 60) % MAP_SIZE;

    if (x == tick_seed) {
        if (y == 5 || y == 16 || y == 26)
            return WALL;
    }
    return map[x][y];
}

int Game::GetPlayerX() {
    return player->position.x;
}

int Game::GetPlayerY() {
    return player->position.y;
}

void Game::SetPlayerFacing(int direction) {
    if (direction != -1)
        player->direction = direction;
}

Pokemon *Game::GetPokemon(int index) {
    return pokemon[index];
}

void Game::Tick() {
    Move();
    Capture();
    Spawn();
    tick++;
}

void Game::Move() {
    switch (player->direction) {
        case NORTH:
            player->position.y--;
            break;
        case WEST:
            player->position.x--;
            break;
        case SOUTH:
            player->position.y++;
            break;
        case EAST:
            player->position.x++;
            break;
        default:
            break;
    }
    UpdateSegments();
}

void Game::UpdateSegments() {
    // Check the distance from the head to the first segment.
    if (MinimumDistanceEitherAxis(player->position, player->segment[0]->position, TILE_SIZE)) {

        // Right shift on all the segments positions, including head.
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

bool Game::MinimumDistanceEitherAxis(Position p1, Position p2, int maxDistance) {
    return (abs(p1.x - p2.x) >= maxDistance) || (abs(p1.y - p2.y) >= maxDistance);
}

void Game::Capture() {
    for (int i = 0; i < POKEMON_MAX; i++) {

        if (pokemon[i] != nullptr) {
            if (CheckCollison(player->position, pokemon[i]->position, TILE_SIZE)) {
                delete pokemon[i];
                pokemon[i] = nullptr;

                AddSegment();
            }
        }
    }
}

bool Game::CheckCollison(Position object, Position fixed, int size) {
    return abs(object.x - fixed.x) < size && abs(object.y - fixed.y) < size;
}

void Game::AddSegment() {
    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        if (!player->segment[i]->attached) {
            player->segment[i]->attached = true;
            break;
        }
    }
}

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
    return (abs(object.x - x * TILE_SIZE) < TILE_SIZE && abs(object.y - y * TILE_SIZE) < TILE_SIZE);
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



