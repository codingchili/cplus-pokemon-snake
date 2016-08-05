#include <cmath>
#include <string>
#include "Renderer.h"

Renderer::Renderer(Game *game, Resources *resources) {
    this->resources = resources;
    this->game = game;
}

void Renderer::Update(int view) {
    BeginGraphics();

    switch (view) {
        case VIEW_START:
            StartView();
            break;
        case VIEW_GAMEPLAY:
            GamePlay();
            break;
        case VIEW_NEXTLEVEL:
            NextLevelView();
            break;
        case VIEW_GAMEOVER:
            GameOver();
            break;
        case VIEW_GAMEWIN:
            GameWin();
            break;
        default:
            StartView();
    }
    tick++;
    EndGraphics();
}

void Renderer::StartView() {
    DrawBitmap(resources->start, 0, 0);
    DrawMenu();
}

void Renderer::DrawMenu() {
    DrawBitmap(resources->startgame,
               (int) (cos(tick % 360 * PI / 180) * 100), START_OFFSET);
}

void Renderer::GamePlay() {
    DrawBackground();
    DrawPokemons();
    DrawWalls();
    DrawPlayer();
    DrawParticles();

    if (game->WasCaptured())
        SpawnParticles();
}

void Renderer::DrawBackground() {
    DrawBitmap(resources->background, 0, 0);
}

void Renderer::DrawWalls() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int k = 0; k < MAP_SIZE; k++) {
            if (game->GetTile(i, k) == WALL) {
                DrawBitmap(resources->wall,
                           i * WALL_SIZE,
                           k * WALL_SIZE);
            }
        }
    }
}

void Renderer::DrawPokemons() {
    for (int i = 0; i < POKEMON_MAX; i++) {
        Pokemon *pokemon = game->GetPokemon(i);

        if (pokemon != nullptr) {
            DrawBitmap(
                    (pokemon->type == POKEMON_MEW) ? resources->mew : resources->pikachu,
                    (int) pokemon->position.x - HALF_TILE,
                    (int) pokemon->position.y - HALF_TILE);
        }
    }
}

void Renderer::DrawPlayer() {
    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        Segment *segment = game->GetSegment(i);

        if (segment->attached) {
            DrawBitmap(resources->segment,
                       (int) (segment->position.x + SEGMENT_OFFSET),
                       (int) (segment->position.y + SEGMENT_OFFSET));
        }
    }
    DrawBitmap(resources->head, game->GetPlayerX(), game->GetPlayerY());
}

void Renderer::DrawParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle *particle = &particles[i];

        if (particle->alive) {
            DrawingTextColor(255, 215, 5);
            DrawString("*", (int) particle->x, (int) particle->y);

            particle->x += cos(particle->direction) * particle->speed;
            particle->y += sin(particle->direction) * particle->speed;

            particle->speed -= PARTICLE_SPEED_DECAY * (PARTICLE_LIFETIME - particle->lifetime);

            if (particle->lifetime <= 0) {
                particle->alive = false;
            }

            particle->lifetime--;
        }
    }
}

void Renderer::SpawnParticles() {
    int to_spawn = 4;

    for (int i = 0; i < MAX_PARTICLES && to_spawn > 0; i++) {
        Particle *particle = &particles[i];

        if (!particle->alive) {

            particle->x = game->GetPlayerX();
            particle->y = game->GetPlayerY(); // +45 is 90 deg?
            particle->direction = (to_spawn * 90 + 45) * PI / 180;
            particle->speed = PARTICLE_SPEED;
            particle->lifetime = PARTICLE_LIFETIME;

            particle->alive = true;
            to_spawn--;
        }
    }
}

void Renderer::NextLevelView() {
    DrawBitmap(resources->nextlevel, 0, 0);

    DrawGameStats();
    DrawGameLevel();

    DrawMenu();
}

void Renderer::GameOver() {
    DrawBitmap(resources->gameover, 0, 0);

    DrawGameStats();
    DrawGameLevel();

    DrawMenu();
}

void Renderer::DrawGameLevel() {
    DrawingTextColor(0, 255, 0);
    DrawString("Level ", 242, 415);
    DrawString(std::to_string(game->GetLevel()).c_str(), 286, 415);
    DrawString("/", 296, 415);
    DrawString(std::to_string(MAX_LEVEL).c_str(), 302, 415);
}

void Renderer::DrawGameStats() {
    DrawingTextColor(0, 255, 0);
    DrawString("Score ", 242, 435);
    DrawString(std::to_string(game->GetSegmentCount()).c_str(), 286, 435);
}

void Renderer::GameWin() {
    DrawBitmap(resources->gamewin, 0, 0);

    DrawingTextColor(0, 255, 0);
    DrawString("Seconds ", 224, 435);
    DrawString(std::to_string(game->GetTime() / RENDER_FPS).c_str(), 296, 435);

    DrawMenu();
}



