//
// Created by chili on 2016-08-03.
//

#include <cmath>
#include <string>
#include "Renderer.h"

Renderer::Renderer(Resources *resources) {
    this->resources = resources;
}

void Renderer::Gameplay(Game *game) {
    BeginGraphics();

    DrawBackground();
    DrawWalls(game);
    DrawPokemons(game);
    DrawPlayer(game);

    EndGraphics();
}

void Renderer::DrawBackground() {
    DrawBitmap(resources->background, 0, 0);
}

void Renderer::DrawWalls(Game *game) {
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

void Renderer::DrawPlayer(Game *game) {
    for (int i = 0; i < PLAYER_MAXLEN; i++) {
        Segment *segment = game->GetSegment(i);

        if (segment->attached) {
            DrawBitmap(resources->segment,
                       segment->position.x + SEGMENT_OFFSET,
                       segment->position.y + SEGMENT_OFFSET);
        }
    }
    DrawBitmap(resources->head, game->GetPlayerX(), game->GetPlayerY());
}

void Renderer::DrawPokemons(Game *game) {
    for (int i = 0; i < POKEMON_MAX; i++) {
        Pokemon *pokemon = game->GetPokemon(i);

        if (pokemon != nullptr) {
            DrawBitmap(
                    (pokemon->type == POKEMON_MEW) ? resources->mew : resources->pikachu,
                    pokemon->position.x,
                    pokemon->position.y);
        }
    }
}

void Renderer::GameOver(Game *game) {
    BeginGraphics();

    DrawBitmap((game->Lost()) ? resources->gameover : resources->gamewin, 0, 0);

    DrawingTextColor(0, 255, 0);
    DrawString("Score ", 242, 425);
    DrawString(std::to_string(game->GetSegmentCount()).c_str(), 282, 425);

    EndGraphics();
}

void Renderer::StartView() {
    BeginGraphics();

    DrawBitmap(resources->start, 0, 0);
    DrawBitmap(resources->startgame,
               (int) (cos(tick % 360 * PI / 180) * 100), START_OFFSET);

    tick++;

    EndGraphics();
}



