//
// Created by chili on 2016-08-03.
//

#include "Renderer.h"

Renderer::Renderer(Resources *resources) {
    this->resources = resources;
}

void Renderer::DrawBackground() {
    DrawBitmap(resources->background, 0, 0);
}

void Renderer::DrawWalls(Game *game) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int k = 0; k < MAP_SIZE; k++) {
            if (game->GetTile(i, k) == WALL) {
                DrawBitmap(resources->wall, i * 16, k * 16);
            }
        }
    }
}

void Renderer::DrawPlayer(Game *game) {
    DrawBitmap(resources->head, game->GetPlayerX() * 16, game->GetPlayerY() * 16);
}

void Renderer::render(Game *game) {
    BeginGraphics();

    DrawBackground();
    DrawWalls(game);
    DrawPlayer(game);

    EndGraphics();
}